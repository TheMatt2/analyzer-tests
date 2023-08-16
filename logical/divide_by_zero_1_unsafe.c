/* Divide by Zero 1 Unsafe
 *
 * Example of dividing by zero, which would cause a crash.
 *
 * Using macro expansion to test if the compiler works out
 * this is going to produce a crash.
 */

#include <stdio.h>

#define A 10
#define B 10

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    int x = 113 / (B - A);

    printf("x = %d\n", x);
    return 0;
}
