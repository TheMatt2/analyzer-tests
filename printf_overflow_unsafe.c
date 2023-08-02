// Example of using printf to print a non-null terminated string,
// which will cause a buffer overflow.

#include <stdio.h>

char msg[13] = "Hello, world!";

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;
    printf("%s\n", msg);
    return 0;
}
