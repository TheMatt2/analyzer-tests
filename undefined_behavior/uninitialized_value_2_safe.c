/* Uninitalized Value 2 Safe
 *
 * Example of *not* reading an uninitalized value,
 * which can't cause externally visible undefined
 * behavior.
 */

#include <stdio.h>

int main(int argc, char *argv[]) {

    int y = 42;
    printf("y is %d\n", y);

    switch (argc) {
        case 0:
            ;
            int x = 0;
            printf("x is %d\n", x);
            break;

        case 1:
            x = 2;
            printf("x is %d\n", x);
            break;

        default:
            printf("x is not defined\n");
            break;
    }

    return 0;
}
