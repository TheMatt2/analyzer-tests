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
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define FILENAME "data.bin"

#define TITLE_SIZE ((size_t) 16)
#define BODY_SIZE ((size_t) 16)
#define BODY_NUM (10)

void normal_greeting(const char *name) {
    printf("Hello %s\n\n", name);
}

void fancy_greeting(const char *name) {
    printf("Salutations %s!\n\n", name);
}

void secret_greeting(const char *name) {
    const static char pre[] = \
        "\x57\x65\x6c\x63\x6f\x6d\x65\x20\x41\x67\x65\x6e\x74\x20";

    const static char post[] = \
        "\x0a\x40\x77\x77\x6c\x6a\x74\x6e\x72\x68\x7e\x62\x63\x63" \
        "\x2e\x48\x62\x70\x7c\x67\x71\x71\x1c\x43\x70\x7c\x3a\x68" \
        "\x79\x7e\x6c\x7a\x54\x01\x4f\x46\x57\x56\x47\x40\x4d\x09" \
        "\x43\x58\x16\x0d\x7d\x58\x55\x54\x46\x13\x70\x47\x53\x56" \
        "\x55\x4a\x1a\x13\x7d\x4f\x5b\x1f\x0d\x20\x26\x26\x64\x2a" \
        "\x20\x67\x1c\x21\x23\x38\x65";

    for (size_t i = 0; i < sizeof(pre); i++) {
        char c = pre[i] ^ ((char) i);
        printf("%c", (int) c);
    }

    printf("%s", name);

    for (size_t i = 0; i < sizeof(pre); i++) {
        char c = post[i] ^ ((char) i);
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

    // show which function was choosen for debugging
    printf("> Choose (%p)\n", greeter->func);

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
