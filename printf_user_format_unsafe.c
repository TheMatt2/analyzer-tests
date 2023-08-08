#include <stdio.h>

int main(int argc, char *argv[]) {

    char *user_string;

    if (argc >= 2) {
        user_string = argv[1];
    } else {
        user_string = "Hello, world! %s";
    }

    printf(user_string);
    printf("\n");
    return 0;
}
