/* Stack Return 3 Unsafe
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
#include <stdlib.h>

int *get_ptr(void) {
    int *val = alloca(sizeof(int));
    *val = 0xbeef;
    return val;
}

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    int *ptr = get_ptr();
    printf("%p = %d\n", (void *) ptr, *ptr);

    return 0;
}
