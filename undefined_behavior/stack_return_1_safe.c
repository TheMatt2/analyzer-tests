// demo of a faulty program that returns a stack pointer

#include <stdio.h>

void *get_ptr(void) {
    char *val = "42"; // c-string as always have a lifespan of process
    return (void *) val;
}

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    void *ptr = get_ptr();
    printf("%p = %c\n", ptr, *((char *) ptr));

    return 0;
}
