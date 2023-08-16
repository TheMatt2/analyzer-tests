/* Null Pointer Safe
 *
 * Example of *not* accessing a null pointer, which won't cause a crash.
 *
 * Example of dereferencing a null pointer.
 * The pointer may be a null pointer, depending on argc, but is
 * never accessed if it is null.
 */

#include <stdio.h>
#include <stdlib.h>

int *ptr = NULL;

int main(int argc, char *argv[]) {
    (void) argv;

    // allocate depending on argc
    if (argc != 1) {
        ptr = malloc(sizeof(int));
        if (!ptr) {
            perror("malloc");
            return 1;
        }
    }

    if (ptr) {
        *ptr = 10;
    }

    printf("%p = %d\n", (void *) ptr, ptr ? *ptr : -1);

    free(ptr);
    return 0;
}
