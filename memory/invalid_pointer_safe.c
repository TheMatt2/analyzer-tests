/* Invalid Pointer Safe
 *
 * Example of *not* accessing a hardcoded pointer, which won't cause a crash.
 *
 * Example of dereferencing a pointer that is hardcoded into the file.
 * While accessing a hardcoded pointer may be valid in the context
 * of some embedded systems, it is not valid for a standard unix system.
 */

#include <stdio.h>
#include <stdlib.h>

int *ptr = (int *) 0x12345678;

int main(void) {
    int *tmp_ptr = malloc(sizeof(int));
    if (!tmp_ptr) {
        perror("malloc");
        return 1;
    }

    if (ptr != tmp_ptr) {
        ptr = tmp_ptr;
    }

    *ptr = 10;

    printf("%p = %d\n", (void *) ptr, *ptr);

    if (ptr == tmp_ptr) {
        free(ptr);
    }
    return 0;
}
