// Example of using printf to print a null terminated string

#include <stdio.h>

char msg[14] = "Hello, world!";

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;
    printf("%s\n", msg);
    return 0;
}
