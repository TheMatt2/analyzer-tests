/* Printf Format Overflow Safe
 *
 * Example of *not* passing a user string to printf as the format string,
 * which won't cause a crash.
 *
 * A user being able to pass a format string to printf can cause
 * a crash, and read stack memory to stdout.
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
    (void) argv;

    const char *user_string;

    if (argc >= 2) {
        user_string = "World, Hello! %s";
    } else {
        user_string = "Hello, world! %s";
    }

    printf(user_string, "42");
    printf("\n");
    return 0;
}
