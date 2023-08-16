/* Malloc Zero Access Unsafe
 *
 * Example of using a pointer from Malloc with a 0 size,
 * which will cause a crash.
 *
 * Calling malloc() with a zero sized argument is not,
 * itself, an error. However, this is not portable as POSIX
 * allows malloc() to return either a null pointer, or another
 * pointer that it is undefined behavior to access.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    int *ptr = malloc(0);
    if (!ptr) {
        perror("malloc");
        return 1;
    }

    *ptr = 7;
    printf("%p = %d\n", (void *) ptr, *ptr);

    free(ptr);
    return 0;
}
