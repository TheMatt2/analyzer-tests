// example of modifying a string literal

#include <stdio.h>

char *str1 = "World Hello!";
char str2[] = "Hello World!";

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    char *str;

    if (argc == 1) {
        str = str2;
    } else {
        str = str1;
    }

    if (argc == 1) {
        str[6] = '\0'; // now "Hello" instead of "Hello World!"
    }

    printf("%s\n", str);
    return 0;
}
