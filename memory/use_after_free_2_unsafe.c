/* Use After Free 2 Unsafe
 *
 * Example of freeing a pointer twice, which will cause a crash.
 *
 * Intentionally making it difficult for the compiler to see
 * how the pointers are being used.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void sneaky_swap(uintptr_t *a, uintptr_t *b, int method) {
    // swap pointers, in a way that is not obvious to
    // the compiler

    uintptr_t tmp = 85;

    if (method == 1) {
        // xor swap
        tmp = tmp ^ tmp; // zero sneakily
        tmp = tmp ^ *a; // tmp = (orig) a
        *a = *a ^ *b; // a = combined
        tmp = *a ^ tmp; // tmp = (orig) b
        *b = *a ^ tmp; // b = (orig) a
        *a = *a ^ *b; // a = (orig) b
    } else {
        // simple version: compiler can probably see what happening
        tmp = *a;
        *a = *b;
        *b = tmp;
    }
}

void sneaky_no_swap(uintptr_t *a, uintptr_t *b, int method) {
    sneaky_swap(a, b, method);
    sneaky_swap(a, b, method);
}

int main(int argc, char *argv[]) {
    // use argc to determine which method to use for swapping
    (void) argv;

    int *ptr_a = malloc(sizeof(int));
    if (!ptr_a) {
        perror("malloc");
        return 1;
    }

    int *ptr_b = malloc(sizeof(int));
    if (!ptr_b) {
        free(ptr_a);
        perror("malloc");
        return 1;
    }

    *ptr_a = 10;
    *ptr_b = 42;

    printf("%p = %d\n", (void *) ptr_a, *ptr_a);
    free(ptr_a);
    sneaky_no_swap((uintptr_t *) &ptr_a, (uintptr_t *) &ptr_b, argc);

    printf("%p = %d\n", (void *) ptr_a, *ptr_a);
    free(ptr_a);
    return 0;
}
