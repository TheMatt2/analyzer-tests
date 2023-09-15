/* Realloc Invalid Safe
 *
 * Example of *not* using realloc() to change the size of a
 * non-heap pointer, which won't cause a crash.
 *
 * Passing a null pointer to realloc() is valid, and
 * will act like malloc().
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *val = NULL;

    int *ptr = realloc(val, sizeof(int) * 4);
    if (!ptr) {
        perror("realloc");
        return 1;
    }

    *ptr = 99;
    printf("%p = %d\n", (void *) ptr, *ptr);
    free(ptr);

    return 0;
}
