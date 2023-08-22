/* Use After Free 1 Unsafe
 *
 * Example of freeing a pointer twice, which will cause a crash.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

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

    // show a
    printf("%p = %d\n", (void *) ptr_a, *ptr_a);
    free(ptr_a);

    // show b
    printf("%p = %d\n", (void *) ptr_b, *ptr_b);

    // show a again (after freed; oops)
    printf("%p = %d\n", (void *) ptr_a, *ptr_a);
    free(ptr_b);
    return 0;
}
