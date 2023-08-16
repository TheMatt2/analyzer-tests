/* Scanf Overflow Safe
 *
 * Example of scanf to get user input that can *not* overflow the buffer,
 * which won't cause a crash.
 *
 * Calling scanf with an unbounded %s format string is susceptible to a
 * buffer overflow.
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    char buf[1024];

    // make stdin a file
    if (!freopen("data.txt", "r", stdin)) {
        perror("freopen");
        return 1;
    }

    // Create scanf format string based on the size of buf
    // https://stackoverflow.com/a/1621973/8524178
    char format[32];

    // since format is a known length, there are no possible errors
    // to check for
    snprintf(format, sizeof(format), "%%%zus", sizeof(buf) - 1);

    // read from stdin using scanf
    if (scanf(format, buf) == EOF) {
        perror("scanf");
        return 1;
    }

    printf("Input: %s\n", buf);
    return 0;
}
