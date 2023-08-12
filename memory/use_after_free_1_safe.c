// example of freeing a pointer and then accessing it in a safe manner

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    (void) argc;
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
    ptr_a = NULL;

    printf("%p = %d\n", (void *) ptr_b, *ptr_b);

    if (ptr_a) {
       free(ptr_a);
    }

    free(ptr_b);
    return 0;
}
