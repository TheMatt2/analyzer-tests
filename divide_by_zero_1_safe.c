#include <stdio.h>

#define A 10
#define B 10

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    int x = 113;
#if A != B
    int y = x / (B - A);
#else
    int y = x / (B + A);
#endif
    printf("Your number is %d\n", y);
    return 0;
}
