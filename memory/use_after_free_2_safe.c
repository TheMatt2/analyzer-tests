/* Use After Free 2 Unsafe
 *
 * Example of *not* freeing a pointer twice, which won't cause a crash.
 *
 * This is a security focused example that shows how a use-after-free
 * is a vulnerability, not just a bug. A use-after-free vulnerability
 * can be exploited by an attack to manipulate the program to do what
 * they want, such as setting the instruction pointer!
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>

#if defined(_MSC_VER)
// On Windows, open() / read() are in io.h
#include <io.h>
// On Windows, read()'s return type is int, not ssize_t
#define ssize_t int
#define S_ISDIR(mode) ((mode) & _S_IFDIR)
#else
// On Linux / MacOS, open() / read() are in unistd.h
#include <unistd.h>
#endif

#define FILENAME    "data.bin"

#define TITLE_SIZE  ((size_t) 16)
#define BODY_SIZE   ((size_t) 16)
#define BODY_NUM    (10)

void normal_greeting(const char *name) {
    printf("Hello %s\n\n", name);
}

void fancy_greeting(const char *name) {
    printf("Salutations %s!\n\n", name);
}

void secret_greeting(const char *name) {
    (void) name;

    static const char msg[] = {
        0x57, 0x64, 0x6e, 0x60, 0x6b, 0x68, 0x63, 0x27, 0x49, 0x6e, 0x6f,
        0x65, 0x78, 0x2d, 0x3e, 0x3f, 0x27, 0x30, 0x18, 0x52, 0x61, 0x61,
        0x7e, 0x78, 0x6a, 0x70, 0x60, 0x7a, 0x68, 0x74, 0x71, 0x71, 0x00,
        0x66, 0x50, 0x42, 0x4a, 0x51, 0x43, 0x43, 0x22, 0x7d, 0x42, 0x4e,
        0x0c, 0x5e, 0x4b, 0x4c, 0x42, 0x54, 0x46, 0x13, 0x59, 0x50, 0x45,
        0x44, 0x59, 0x5e, 0x5f, 0x1b, 0x55, 0x4e, 0x04, 0x1f, 0x13, 0x36,
        0x27, 0x26, 0x30, 0x65, 0x02, 0x35, 0x2d, 0x28, 0x27, 0x38, 0x6c,
        0x65, 0x0f, 0x3d, 0x35, 0x71, 0x1f, 0x32, 0x30, 0x30, 0x76, 0x38,
        0x3e, 0x79, 0x0e, 0x33, 0x35, 0x2e, 0x77};

    for (size_t i = 0; i < sizeof(msg); i++) {
        char c = msg[i] ^ (char) i;
        printf("%c", (int) c);
    }
    printf("\n");
}

struct greeter_ {
    const char *name;
    void (*func)(const char *name);
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

    char *title = NULL;
    char *body[BODY_NUM] = {NULL};
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
    struct greeter_ *greeter = malloc(sizeof(struct greeter_));
    if (!greeter) {
        perror("malloc");
        retval = 1;
        goto exit2;
    }

    // initialize
    if (argc == 3) {
        greeter->name = "Captain Tom";
        greeter->func = &normal_greeting;
    } else {
        greeter->name = "Professor Steve";
        greeter->func = &fancy_greeting;
    }

    // Impossible greeting, that no one can get!
    (void) &secret_greeting;

    // show which function was chosen for debugging
    printf("> Chose (%p)\n", (void *) greeter->func);

    // show name for debugging
    printf("Name: %s\n", greeter->name);

    // setup title
    title = malloc(TITLE_SIZE);
    if (!title) {
        perror("malloc");
        retval = 1;
        goto exit1;
    }

    // read title
    if (read_bytes(fd, title, TITLE_SIZE, filename)) {
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

    // display greeting
    greeter->func(greeter->name);

    // display title
    printf("Title: %.*s\n", (int) TITLE_SIZE, title);

    for (int i = 0; i < BODY_NUM; i++) {
        // stop if a null entry is reached
        if (body[i][0] == '\0') {
            break;
        }

        printf("%03d: %.*s\n", i, (int) BODY_SIZE, body[i]);
    }

exit1:
    // free function
    free(greeter);

    // free title
    free(title);

    // free body
    for (int i = 0; i < BODY_NUM; i++) {
        free(body[i]);
    }
exit2:
    close(fd);
exit3:
    return retval;
}
