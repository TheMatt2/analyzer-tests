/* Divide by Zero 2 Unsafe
 *
 * Example of potentially dividing by zero, which would cause a crash.
 *
 * Using argc to decide if a divide by zero exception occurs,
 * to see if a warning is produced on the possibility of
 * a crash.
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
    (void) argv;

    int x = 113 / (argc - 1);

    printf("x = %d\n", x);
    return 0;
}
