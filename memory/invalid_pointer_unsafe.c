/* Invalid Pointer Unsafe
 *
 * Example of accessing a hardcoded pointer, which will cause a crash.
 *
 * Example of dereferencing a pointer that is hardcoded into the file.
 * While accessing a hardcoded pointer may be valid in the context
 * of some embedded systems, it is not valid for a standard unix system.
 */

#include <stdio.h>

int *ptr = (int *) 0x12345678;

int main(void) {
    *ptr = 10;

    printf("%p = %d\n", (void *) ptr, *ptr);
    return 0;
}
