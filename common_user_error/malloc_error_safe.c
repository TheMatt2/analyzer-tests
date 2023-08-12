// example of checking malloc result
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

    *ptr = 7;
    printf("%p = %d\n", (void *) ptr, *ptr);

    free(ptr);
    return 0;
}
