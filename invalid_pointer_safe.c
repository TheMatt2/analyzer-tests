// Example of accessing a hard-coded pointer in a "safe" (if useless) manner.

#include <stdio.h>
#include <stdlib.h>

int *ptr = (int *) 0x12345678;

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    int *tmp_ptr = malloc(sizeof(int));
    if (!tmp_ptr) {perror("malloc"); return 1;}

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
