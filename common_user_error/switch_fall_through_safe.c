/* Switch Fall-Through Safe
 *
 * Example of code flow falling through a switch statement,
 * but the programmer marks the intend for the fall-through to happen.
 *
 * Unlike most of the other tests here, there is nothing wrong
 * with having code flow fall through, except it is a common mistake
 * for programmers to make.
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
    (void) argv;

    int x = argc;

    switch (argc) {
        case 0:
            x += 8;
            // intentional fall-through
        case 1:
            x += 5;
            // intentional fall-through
        case 2:
            x += 3;
            // intentional fall-through
        default:
            x += 2;
            break;
    }

    printf("x = %d\n", x);

    return 0;
}
