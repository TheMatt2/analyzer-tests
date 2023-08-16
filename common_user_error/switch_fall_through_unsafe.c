/* Switch Fall-Through Unsafe
 *
 * Example of code flow falling through a switch statement,
 * when the programmer likely intended for each case to have a break.
 *
 * Unlike most of the other tests here, there is nothing wrong
 * with having code flow fall through, except it is a common mistake
 * for programmers to make.
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
    (void) argv;

    int x;

    switch (argc) {
        case 0:
            x = 8;
        case 1:
            x = 5;
        case 2:
            x = 3;
        default:
            x = 2;
            break;
    }

    printf("x = %d\n", x);

    return 0;
}
