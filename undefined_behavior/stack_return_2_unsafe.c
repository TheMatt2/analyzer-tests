/* Stack Return 2 Unsafe
 *
 * Example of returning a stack pointer from a function,
 * which will cause a crash.
 *
 * Returning a stack pointer from a function will
 * always result in an invalid pointer.
 *
 * A string literal, on the other-hand, will always have a lifespan
 * of the process.
 */

#include <stdio.h>

char *get_ptr(void) {
    char val[] = "42";
    return val;
}

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    char *ptr = get_ptr();
    printf("%p = %s\n", (void *) ptr, ptr);

    return 0;
}
