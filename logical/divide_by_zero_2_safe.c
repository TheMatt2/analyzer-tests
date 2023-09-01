/* Divide by Zero 2 Safe
 *
 * Example of *not* dividing by zero, which won't cause a crash.
 *
 * Using argc to decide if a divide occurs,
 * however this logically can not cause a divide by zero.
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
