/* Memory Leak Safe
 *
 * Example of never freeing a pointer, which will cause a memory leak.
 *
 * While this program will not crash, leaking memory consumes resources
 * that the OS is not guarenteed to reclaim in a timely manner.
 *
 * The exception is memory allocated by alloc, which does not need to
 * be freed.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    int *ptr = alloca(sizeof(int));
    *ptr = 10;

    printf("%p = %d\n", (void *) ptr, *ptr);

    return 0;
}
