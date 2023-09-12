/* Reallocf Free Safe
 *
 * Example of using reallocf() *not* to double free a pointer,
 * which won't cause a crash.
 */

#include <stdio.h>
#include <stdint.h>

#if defined(__FreeBSD__)
// On BSD reallocf() is defined in bsd/stdlib.h
#include <bsd/stdlib.h>
#elif defined(__APPLE__)
// On MacOS reallocf() is defined in stdlib.h
#include <stdlib.h>
#else
// On Linux, there is no reallocf(), reallocf() is defined in stdlib.h
#include <stdlib.h>

// https://opensource.apple.com/source/Libc/Libc-391/stdlib/FreeBSD/reallocf.c
void *reallocf(void *ptr, size_t size) {
	void *nptr;

	nptr = realloc(ptr, size);
	if (!nptr && ptr)
		free(ptr);

	return nptr;
}
#endif

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    int *ptr1 = malloc(sizeof(int));
    if (!ptr1) {
        perror("malloc");
        return 1;
    }

    *ptr1 = 45;

    printf("%p = %d\n", (void *) ptr1, *ptr1);

    // use max size to force reallocf() to fail
    int *ptr2 = reallocf(ptr1, SIZE_MAX);
    if (!ptr2) {
        perror("reallocf");
        return 1;
    }

    printf("%p = %d\n", (void *) ptr2, *ptr2);
    free(ptr2);

    return 0;
}
