/* Use After Free 2 Unsafe
 *
 * Example of *not* freeing a pointer twice, which can't cause a crash.
 *
 * This is a security focused example that shows how a use-after-free
 * is a vulnerability, not just a bug. A use-after-free vulnerability
 * can be exploited by an attack to manipulate the program to do what
 * they want, such as setting the instruction pointer!
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define FILENAME "data.bin"

#define PRE_SIZE (size_t) 16
#define BODY_SIZE (size_t) 16
#define BODY_NUM 5

void op_print(void) {
    printf("Hello World\n");
    fflush(stdout);
}

void op_secret(void) {
    const static char secret[] = "\x62\x60\x6c\x62\x6a\x64";

    printf("Authorization Granted\n");
    printf("The password is: ");

    for (size_t i = 0; i < sizeof(secret); i++) {
        char c = secret[i] ^ ((char) i);
        printf("%c", (int) c);
    }

    printf("\n");
}

struct func_op_ {
    char *name;
    void (*func)(void);
};

int open_file(const char *filename, int flags) {
    int fd = open(filename, flags);
    if (fd < 0) {
        // failed to open
        perror(filename);
        goto error2;
    }

    // confirm fd is a normal file
    struct stat path_stat;
    if (fstat(fd, &path_stat)) {
        perror("fstat");
        goto error1;
    }

    // is directory
    if (S_ISDIR(path_stat.st_mode)) {
        fprintf(stderr, "%s: Is a directory\n", filename);
        goto error1;
    }

    return fd;
error1:
    close(fd);
error2:
    return -1;
}

int read_bytes(int fd, void *buf, size_t size, const char *filename) {
    // perform read
    ssize_t bytes_read = read(fd, buf, size);

    // check for errors
    if (bytes_read < 0) {
        perror("read");
        return -1;
    }

    // check underflow
    if ((size_t) bytes_read != size) {
        // get offset to add to error message
        off_t pos = lseek(fd, 0, SEEK_CUR);

        if (pos > 0) {
            // if seek succeeds, subtract to show offset before read
            pos = pos - bytes_read;

            fprintf(stderr, "%s: Read %zd bytes of %zu bytes expected at offset %jd\n",
                filename, bytes_read, size, (intmax_t) pos);
        } else {
            // if lseek fails, and returns -1, ignore and show message
            // without offset
            fprintf(stderr, "%s: Read %zd bytes of %zu bytes\n",
                filename, bytes_read, size);
        }
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    int retval = 0;

    uint8_t *preamble = NULL;
    uint8_t *body[BODY_NUM] = {NULL};
    const char *filename;

    if (argc == 2) {
        filename = argv[1];
    } else {
        filename = FILENAME;
    }

    // open input file
    int fd = open_file(filename, O_RDONLY);
    if (fd < 0) {
        retval = 1;
        goto exit3;
    }

    // create function
    struct func_op_ *func_op = malloc(sizeof(struct func_op_));
    if (!func_op) {
        perror("malloc");
        retval = 1;
        goto exit2;
    }

    // initialize
    func_op->name = "hello";
    func_op->func = &op_print;

    // run function
    printf("> %s (%p)\n", func_op->name, func_op->func);
    func_op->func();

    // free function
    free(func_op);

    // setup preamble
    preamble = malloc(PRE_SIZE);
    if (!preamble) {
        perror("malloc");
        retval = 1;
        goto exit1;
    }

    // read preamble
    if (read_bytes(fd, preamble, PRE_SIZE, filename)) {
        retval = 1;
        goto exit1;
    }

    // setup body
    for (int i = 0; i < BODY_NUM; i++) {
        body[i] = malloc(BODY_SIZE);
        if (!body[i]) {
            perror("malloc");
            retval = 1;
            goto exit1;
        }
    }

    // read body
    for (int i = 0; i < BODY_NUM; i++) {
        if (read_bytes(fd, body[i], BODY_SIZE, filename)) {
            retval = 1;
            goto exit1;
        }
    }

    // run function again
    printf("> %s (%p)\n", func_op->name, func_op->func);
    func_op->func();

exit1:
    // free preamble
    free(preamble);

    // free body
    for (int i = 0; i < BODY_NUM; i++) {
        free(body[i]);
    }
exit2:
    close(fd);
exit3:
    return retval;
}
