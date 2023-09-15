/* Array Overflow Unsafe
 *
 * Example of *not* accessing values outside an array, which will cause a crash.
 *
 * Explicitly initializing the array to a larger size,
 * to test the remaining values are zeros.
 */

#include <stdio.h>

int int_arr[5] = {1, 2, 3};

int main(void) {
    printf("first  %d\n", int_arr[0]);
    printf("second %d\n", int_arr[1]);
    printf("third  %d\n", int_arr[2]);
    printf("forth  %d\n", int_arr[3]);
    printf("fifth  %d\n", int_arr[4]);
    return 0;
}
