// example of concatenating strings in a way that won't cause a segfault
// string literals declared to a pointer are read-only, so you can't modify them
// https://stackoverflow.com/questions/44294649/if-chars-are-read-only-why-can-i-overwrite-them

#include <stdio.h>

char *str = "Hello World!";

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    str[6] = '\0'; // now "Hello" instead of "Hello World!"

    printf("%s\n", str);
    return 0;
}
