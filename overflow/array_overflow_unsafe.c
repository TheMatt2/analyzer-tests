/* Array Overflow Unsafe
 *
 * Example of accessing values outside an array, which will cause a crash.
 */

#include <stdio.h>

int int_arr[] = {1, 2, 3};

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
