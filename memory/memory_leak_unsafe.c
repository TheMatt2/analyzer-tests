/* Memory Leak Unsafe
 *
 * Example of never freeing a pointer, which will cause a memory leak.
 *
 * While this program will not crash, leaking memory consumes resources
 * that the OS is not guaranteed to reclaim in a timely manner.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *ptr = malloc(sizeof(int));
    if (!ptr) {
        perror("malloc");
        return 1;
    }

    *ptr = 10;

    printf("%p = %d\n", (void *) ptr, *ptr);

    return 0;
}
