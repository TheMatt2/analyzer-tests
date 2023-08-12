// example of modifying a string literal

#include <stdio.h>

char *str = "Hello World!";

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    str[6] = '\0'; // now "Hello" instead of "Hello World!"

    printf("%s\n", str);
    return 0;
}