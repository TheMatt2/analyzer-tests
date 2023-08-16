/* Stack Return 3 Safe
 *
 * Example of *not* returning a stack pointer from a function,
 * which won't cause a crash.
 *
 * Returning a stack pointer from a function will
 * always result in an invalid pointer.
 *
 * A string literal, on the otherhand, will always have a lifespan
 * of the process.
 */

#include <stdio.h>
#include <stdlib.h>

int *get_ptr(void) {
    int *x = alloca(sizeof(int));
    *x = 0xbeef;

    int *y = malloc(sizeof(int));

    if (x == y) return x;

    return y;
}

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    char *ptr = get_ptr();
    printf("%p = %s\n", (void *) ptr, ptr);

    free(ptr);

    return 0;
}
