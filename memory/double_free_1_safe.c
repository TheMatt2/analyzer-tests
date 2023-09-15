/* Double Free 1 Safe
 *
 * Example of *not* freeing a pointer twice, which won't cause a crash.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *ptr_a = malloc(sizeof(int));
    if (!ptr_a) {
        perror("malloc");
        return 1;
    }

    int *ptr_b = malloc(sizeof(int));
    if (!ptr_b) {
        free(ptr_a);
        perror("malloc");
        return 1;
    }

    *ptr_a = 10;
    *ptr_b = 42;

    printf("%p = %d\n", (void *) ptr_a, *ptr_a);
    free(ptr_a);
    ptr_a = NULL;

    printf("%p = %d\n", (void *) ptr_b, *ptr_b);

    if (ptr_a) {
       free(ptr_a);
    }

    free(ptr_b);
    return 0;
}
