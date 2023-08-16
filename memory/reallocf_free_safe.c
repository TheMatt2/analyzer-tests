/* Realloc Free Safe
 *
 * Example of using reallocf() *not* to double free a pointer,
 * which won't cause a crash.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    int *ptr1 = malloc(sizeof(int));
    if (!ptr1) {
        perror("malloc");
        return 1;
    }

    *ptr1 = 45;

    printf("%p = %d\n", (void *) ptr1, *ptr1);

    // use max size to force realloc to fail
    int *ptr2 = reallocf(ptr1, SIZE_MAX);
    if (!ptr2) {
        perror("reallocf");
        return 1;
    }

    printf("%p = %d\n", (void *) ptr2, *ptr2);
    free(ptr2);

    return 0;
}
