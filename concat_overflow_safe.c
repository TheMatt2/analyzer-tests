// example of concatenating strings in a way that won't cause a segfault

#include <stdio.h>
#include <string.h>

char str1[] = "Hello There!";
char str2[] = "World!";

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    str1[6] = '\0'; // str1 is now "Hello" instead of "Hello There!"

    printf("%s\n", strcat(str1, str2));
    return 0;
}
