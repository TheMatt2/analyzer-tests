/* Printf Format Overflow Unsafe
 *
 * Example of passing a user string to printf as the format string,
 * which can cause a crash.
 *
 * A user being able to pass a format string to printf can cause
 * a crash, and read stack memory to stdout.
 */

#include <stdio.h>

int main(int argc, char *argv[]) {

    const char *user_string;

    if (argc >= 2) {
        user_string = argv[1];
    } else {
        user_string = "Hello, world! %s";
    }

    printf(user_string);
    printf("\n");
    return 0;
}
