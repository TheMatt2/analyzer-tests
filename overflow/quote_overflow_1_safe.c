/* Quote Overflow 1 Safe
 *
 * Example of a string quoting function without a buffer overflow,
 * which won't cause a crash.
 *
 * This string quoting function is meant to represent a more
 * complex string manipulation algorithm that could have
 * a non-obvious buffer overflow.
 *
 * This string quoting function creates a quoted string in a manner
 * such that the output string must have a size set by the equation:
 *
 *  M = (N - 1) * 4 + 3
 *
 * Where M is the size of the output string including the NULL pointer.
 * Where N is the size of the input string include the NULL pointer.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// ssize_t is posix, yet is not defined on Windows
#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#else
#include <sys/types.h>
#endif

char msg[] = "\1\2\3\4";

/* Quote a string
 *
 * Creates a quoted version of the given string, adding
 * quotation marks around the string and escaping any
 * non-printable characters.
 *
 * Returns the number of characters written to buf, or
 * -1 if buf is too small.
 */
ssize_t quote_s(const char *str, size_t str_length,
                char *buf, size_t buf_length);

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    char *buf = malloc(sizeof(msg) * 2);
    if (!buf) {
        perror("malloc");
        return 1;
    }

    ssize_t len = quote_s(msg, sizeof(msg), buf, sizeof(msg) * 2);

    if (len < 0) {
        fprintf(stderr, "error: buffer too small\n");
        free(buf);
        return 1;
    }

    printf("%s\n", buf);
    free(buf);
    return 0;
}

ssize_t quote_s(const char *const str, size_t str_length,
                char *const buf, size_t buf_length) {

    size_t j = 0;

    if (buf_length < 2) {
        // not enough space for quotes
        return -1;
    }

    buf[0] = '"';
    j++;

    for (size_t i = 0; i < str_length; i++) {
        // check there is enough room
        if (j >= buf_length - 1) return -1;

        char c = str[i];

        if (c == '\0') {
            // add trailing quote
            buf[j] = '"';
            j++;
            buf[j] = '\0';
            j++;
            break;
        } else if (isprint(c)) {
            // add normally
            buf[j] = c;
            j++;
        } else {
            // add escaped
            char escape;

            // replace backslash notation (ANSI C89)
            switch (c) {
                case '\a': escape = 'a';  break;
                case '\b': escape = 'b';  break;
                case '\f': escape = 'f';  break;
                case '\n': escape = 'n';  break;
                case '\r': escape = 'r';  break;
                case '\t': escape = 't';  break;
                case '\v': escape = 'v';  break;
                case '\'': escape = '\''; break;
                case '\\': escape = '\\'; break;
                case  '"': escape = '\"'; break;
                default: escape = '\0';
            }

            // bounds check
            const unsigned int escape_length = escape ? 2 : 4;

            if (j + escape_length > buf_length) return -1;

            if (escape != '\0') {
                // add escaped
                buf[j] = '\\';
                j++;
                buf[j] = escape;
                j++;
            } else {
                // other unprintable character, use hex notation
                buf[j] = '\\';
                j++;
                buf[j] = 'x';
                j++;
                snprintf(buf + j, buf_length - j, "%02x", (int) c);
                j++;
                j++;
            }
        }
    }
    return (ssize_t) j;
}
