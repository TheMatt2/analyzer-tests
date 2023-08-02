// Example of accessing a hard-coded pointer in a "safe" manner.

#include <stdio.h>
#include <stdlib.h>

int *ptr = (int *) 0x12345678;

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    *ptr = 10;

    printf("%p = %d\n", (void *) ptr, *ptr);
    return 0;
}
