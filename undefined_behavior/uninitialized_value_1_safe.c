// example of freeing a pointer and then accessing it in a safe manner

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    int *ptr = malloc(sizeof(int));
    if (!ptr) {
        perror("malloc");
        return 1;
    }

    *ptr = *ptr ^ *ptr;
    printf("%p = %d\n", (void *) ptr, *ptr);

    free(ptr);
    return 0;
}
