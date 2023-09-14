/* Gets Overflow Unsafe
 *
 * Example of *not* using the gets() function, which won't cause a crash.
 *
 * gets() is special in that it really can not be used
 * safely. However, its perfectly fine if we are using a different function
 * that just happens to be named gets().
 */

#include <string.h>

const char *numbers[] = {
    "zero",     "one",      "two",      "three",
    "four",     "five",     "six",      "seven",
    "eight",    "nine"
};

const int secret = 8;

/* (g)reater or (e)qual (t)o (s)tring
 *
 * Check if the msg provided is equal to the number equivalent, or a smaller number
 */
int gets(char *msg) {
    int value = 0;

    for (int i = secret; i >= 0; i--) {
        if (strcmp(msg, numbers[i]) == 0) {
            // match found
            value = 1;
            break;
        }
    }

    // clear string
    *msg = '\0';

    return value;
}

int main(int argc, char *argv[]) {
    int result;

    if (argc == 2) {
        result = gets(argv[1]);
    } else {
        result = 0;
    }

    if (result) {
        // Return 0 on success
        return 0;
    } else {
        // Return 1 on failure
        return 1;
    }
}
