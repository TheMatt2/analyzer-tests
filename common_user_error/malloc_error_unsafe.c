// example of not checking malloc result, and therefore pointer maybe null

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    int *ptr = malloc(sizeof(int));

    *ptr = 7;
    printf("%p = %d\n", (void *) ptr, *ptr);

    free(ptr);
    return 0;
}
