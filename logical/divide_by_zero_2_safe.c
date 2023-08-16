/* Divide by Zero 2 Safe
 *
 * Example of *not* dividing by zero, which won't cause a crash.
 *
 * Using argc to decide if an a divide by zero occurs,
 * to see if a warning is produced on the possibility of
 * a crash.
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
    (void) argv;

    if (argc < 2) {
        printf("At least one argument is required\n");
        return 1;
    }

    int x = 113 / (argc - 1);

    printf("x = %d\n", x);
    return 0;
}
