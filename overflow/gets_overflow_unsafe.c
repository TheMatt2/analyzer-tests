/* Gets Overflow Unsafe
 *
 * Example of using the gets() function, which will cause a crash.
 *
 * Use "data.txt" as stdin to prevent the program from waiting
 * for input.
 */

#include <stdio.h>

int main(void) {
    char buf[1024];

    // make stdin a file
    if (!freopen("data.txt", "r", stdin)) {
        perror("freopen");
        return 1;
    }

    if (!gets(buf)) {
        perror("gets");
        return 1;
    }

    printf("Input: %s\n", buf);
    return 0;
}
