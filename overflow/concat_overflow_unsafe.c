// example of concatenating strings in a way that will cause a segfault

#include <stdio.h>
#include <string.h>

char str1[] = "Hello ";
char str2[] = "World!";

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    printf("%s\n", strcat(str1, str2));
    return 0;
}
