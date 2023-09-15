/* Printf String Overflow Unsafe
 *
 * Example of passing a non-null terminated string to printf(),
 * which will cause a crash.
 */

#include <stdio.h>

char msg[13] = "Hello, world!";

int main(void) {
    printf("%s\n", msg);
    return 0;
}
