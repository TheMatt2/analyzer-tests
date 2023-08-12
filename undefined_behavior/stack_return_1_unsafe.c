// demo of a faulty program that returns a stack pointer

#include <stdio.h>

void *get_ptr(void) {
    int val = 42;
    return (void *) &val;
}

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    void *ptr = get_ptr();
    printf("%p = %d\n", ptr, *((int *) ptr));

    return 0;
}
