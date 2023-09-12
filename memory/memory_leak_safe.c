/* Memory Leak Safe
 *
 * Example of never freeing a pointer, which will cause a memory leak.
 *
 * While this program will not crash, leaking memory consumes resources
 * that the OS is not guaranteed to reclaim in a timely manner.
 *
 * The exception is memory allocated by alloca, which does not need to
 * be freed.
 */

#include <stdio.h>

#if defined(_MSC_VER)
// On Windows, _alloca() is in malloc.h
#include <malloc.h>
#define alloca _alloca
#else
// On Linux alloca() is defined in alloca.h
// On MacOS alloca() is defined in alloca.h and stdlib.h
#include <alloca.h>
#endif

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    int *ptr = alloca(sizeof(int));
    *ptr = 10;

    printf("%p = %d\n", (void *) ptr, *ptr);

    return 0;
}
