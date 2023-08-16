/* Realloc Invalid Unsafe
 *
 * Example of using realloc() to change the size of a non-heap pointer,
 * which will cause a crash.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    int val = 45;

    int *ptr = realloc(&val, sizeof(int) * 4);
    if (!ptr) {
        perror("realloc");
        return 1;
    }

    *ptr = 99;
    printf("%p = %d\n", (void *) ptr, *ptr);
    free(ptr);

    return 0;
}
