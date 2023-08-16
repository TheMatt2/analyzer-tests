/* Gets Overflow Unsafe
 *
 * Example of *not* using the gets() function, which won't cause a crash.
 *
 * gets() is special in that it really can not be used
 * safely. However, technically it is safe to call gets()
 * if stdin is closed. This is useless, however, and so it shouldn't
 * be surprising that gets() is still detected as unsafe.
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    char buf[1024];

    // close stdin
    if (fclose(stdin)) {
        perror("fclose");
        return 1;
    }

    if (!gets(buf)) {
        perror("gets");
        return 1;
    }

    printf("Input: %s\n", buf);
    return 0;
}
