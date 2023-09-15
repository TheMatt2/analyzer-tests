/* Malloc Error Unsafe
 *
 * Example of not checking if the result of malloc()
 * is NULL, which can cause a NULL pointer to be dereferenced.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *ptr = malloc(sizeof(int));

    *ptr = 7;
    printf("%p = %d\n", (void *) ptr, *ptr);

    free(ptr);
    return 0;
}
