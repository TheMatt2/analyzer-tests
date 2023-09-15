/* Malloc Error Safe
 *
 * Example of correctly checking the result of malloc()
 * is NULL, and exiting if this occurs.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *ptr = malloc(sizeof(int));
    if (!ptr) {
        perror("malloc");
        return 1;
    }

    *ptr = 7;
    printf("%p = %d\n", (void *) ptr, *ptr);

    free(ptr);
    return 0;
}
