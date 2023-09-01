/* Stack Return 1 Unsafe
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

void *get_ptr(void) {
    int val = 42;
    return (void *) &val;
}

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    void *ptr = get_ptr();
    printf("%p = %d\n", ptr, *((int *) ptr));

    return 0;
}
