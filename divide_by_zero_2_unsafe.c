#include <stdio.h>

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    int x = 113;
    int y = x / (argc - 1);

    printf("Your number is %d\n", y);
    return 0;
}
