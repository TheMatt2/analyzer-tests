/* Printf String Overflow Safe
 *
 * Example of *not* passing a non-null terminated string to printf(),
 * which won't cause a crash.
 */

#include <stdio.h>

char msg[14] = "Hello, world!";

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    printf("%s\n", msg);
    return 0;
}
