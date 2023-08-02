// Example of checking if a point is NULL before dereferencing it.

#include <stdio.h>
#include <stdlib.h>

int int_arr[5] = {1, 2, 3};

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    printf("first  %d\n", int_arr[0]);
    printf("second %d\n", int_arr[1]);
    printf("third  %d\n", int_arr[2]);
    printf("forth  %d\n", int_arr[3]);
    printf("fifth  %d\n", int_arr[4]);
    return 0;
}
