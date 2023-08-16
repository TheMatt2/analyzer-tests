/* Concat Overflow Safe
 *
 * Example of concatenating two strings *not* past the end of their buffer,
 * which won't cause a crash.
 */

#include <stdio.h>
#include <string.h>

char str1[] = "Hello There!";
char str2[] = "World!";

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    str1[6] = '\0'; // str1 is now "Hello" instead of "Hello There!"

    strcat(str1, str2);
    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);
    return 0;
}
