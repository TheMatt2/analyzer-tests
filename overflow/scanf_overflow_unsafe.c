/* Scanf Overflow Unsafe
 *
 * Example of scanf to get user input that can overflow the buffer,
 * which will cause a crash.
 *
 * Calling scanf with an unbounded %s format string is susceptible to a
 * buffer overflow.
 */

#include <stdio.h>

int main(void) {
    char buf[1024];

    // make stdin a file
    if (!freopen("data.txt", "r", stdin)) {
        perror("freopen");
        return 1;
    }

    // read from stdin using scanf
    if (scanf("%s", buf) == EOF) {
        perror("scanf");
        return 1;
    }

    printf("Input: %s\n", buf);
    return 0;
}
