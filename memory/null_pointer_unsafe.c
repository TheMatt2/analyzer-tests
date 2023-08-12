// Example of checking if a point is NULL before dereferencing it.

#include <stdio.h>
#include <stdlib.h>

int *ptr = NULL;

int main(int argc, char *argv[]) {
    (void) argv;

    // allocate depending on argc
    if (argc != 1) {
        ptr = malloc(sizeof(int));
        if (!ptr) {perror("malloc"); return 1;}
    }

    *ptr = 10;

    printf("%p = %d\n", (void *) ptr, ptr ? *ptr : -1);

    free(ptr);
    return 0;
}
