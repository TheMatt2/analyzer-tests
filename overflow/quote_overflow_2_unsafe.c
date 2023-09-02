/* Quote Overflow 2 Unsafe
 *
 * Example of a string quoting function with a buffer overflow,
 * which will cause a crash.
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

// Convert byte to characters \xAB -> 0xAB
#define CHAR_HEX_UPPER(b) ((char) (((b) & 0xf0) >> 4) + '0')
#define CHAR_HEX_LOWER(b) ((char) ((b) & 0x0f) + '0')

char msg[] = "\1\2\3\4";

/* Quote a string
 *
 * Creates a quoted version of the given string, adding
 * quotation marks around the string and escaping any
 * non-printable characters.
 *
 */
void quote_s(const char *str, size_t length, char *buf);

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    char *buf = malloc(sizeof(msg) * 2);
    if (!buf) {
        perror("malloc");
        return 1;
    }

    quote_s(msg, sizeof(msg), buf);

    printf("%s\n", buf);
    free(buf);
    return 0;
}

void quote_s(const char *const str, size_t length, char *const buf) {

    size_t j = 0;

    buf[0] = '"';
    j++;

    for (size_t i = 0; i < length; i++) {
        char c = str[i];

        if (c == '\0') {
            // add trailing quote
            buf[j] = '"';
            j++;
            buf[j] = '\0';
            // j++; // won't be used
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
                default  : escape = '\0';
            }

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
                buf[j] = CHAR_HEX_UPPER(c); // hex of most sig digit
                j++;
                buf[j] = CHAR_HEX_LOWER(c); // hex of least sig digit
                j++;
            }
        }
    }
}
