#include <stdio.h>

int main(int argc, char *argv[]) {

    char *user_string;

    if (argc >= 2) {
        user_string = "World, Hello! %s";
    } else {
        user_string = "Hello, world! %s";
    }

    printf(user_string, "42");
    printf("\n");
    return 0;
}
