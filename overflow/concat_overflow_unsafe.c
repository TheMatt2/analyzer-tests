/* Concat Overflow Unsafe
 *
 * Example of concatenating two strings past the end of their buffer,
 * which will cause a crash.
 */

#include <stdio.h>
#include <string.h>

char str1[] = "Hello ";
char str2[] = "World!";

int main(void) {
    strcat(str1, str2);
    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);
    return 0;
}
