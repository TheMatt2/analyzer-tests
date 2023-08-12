// demo of a faulty program that returns a stack pointer

#include <stdio.h>

char *get_ptr(void) {
    char val[] = "42"; // c-string as always have a lifespan of process
    return val;
}

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    char *ptr = get_ptr();
    printf("%p = %s\n", (void *) ptr, ptr);

    return 0;
}
