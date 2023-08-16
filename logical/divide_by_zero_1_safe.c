/* Divide by Zero 1 Safe
 *
 * Example of *not* dividing by zero, which won't cause a crash.
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

#if A != B
    int x = 113 / (B - A);
#else
    int x = 113 / (B + A);
#endif

    printf("x = %d\n", x);
    return 0;
}
