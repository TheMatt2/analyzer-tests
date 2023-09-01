/* Use After Free 2 Unsafe
 *
 * Example of freeing a pointer twice, which will cause a crash,
 * *or worse*.
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
    (void) name;

    const static char msg[95] = \
        "\x57\x64\x6e\x60\x6b\x68\x63\x27\x49\x6e\x6f\x65\x78\x2d" \
        "\x3e\x3f\x27\x30\x18\x52\x61\x61\x7e\x78\x6a\x70\x60\x7a" \
        "\x68\x74\x71\x71\x00\x66\x50\x42\x4a\x51\x43\x43\x22\x7d" \
        "\x42\x4e\x0c\x5e\x4b\x4c\x42\x54\x46\x13\x59\x50\x45\x44" \
        "\x59\x5e\x5f\x1b\x55\x4e\x04\x1f\x13\x36\x27\x26\x30\x65" \
        "\x02\x35\x2d\x28\x27\x38\x6c\x65\x0f\x3d\x35\x71\x1f\x32" \
        "\x30\x30\x76\x38\x3e\x79\x0e\x33\x35\x2e\x77";

    for (size_t i = 0; i < sizeof(msg); i++) {
        char c = msg[i] ^ ((char) i);
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

    // show which function was chosen for debugging
    printf("> Chose (%p)\n", (void *) greeter->func);

    // show name for debugging
    printf("Name: %s\n", greeter->name);

    // finished with name, deallocate
    free(greeter);

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
