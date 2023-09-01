/* Uninitialized Value 1 Safe
 *
 * Example of *not* reading an uninitialized value,
 * which can't cause externally visible undefined
 * behavior.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    int *ptr = malloc(sizeof(int));
    if (!ptr) {
        perror("malloc");
        return 1;
    }

    *ptr = 27;
    printf("%p = %d\n", (void *) ptr, *ptr);

    free(ptr);
    return 0;
}
