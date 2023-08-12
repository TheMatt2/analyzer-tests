// example of how switch fall through can cause issues
// in a program

#include <stdio.h>

int main(int argc, char *argv[]) {
    (void) argv;

    int x = argc;
    int y = x;

    switch (x) {
        case 0:
            y *= 8;
        case 1:
            y *= 5;
        case 2:
            y *= 3;
        default:
            y *= 2;
            break;
    }

    printf("For x = %d, y = %d\n", x, y);

    return 0;
}
