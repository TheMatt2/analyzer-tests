#include <stdio.h>

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    char buf[1024];

    // make stdin a file
    if (!freopen("data.txt", "r", stdin)) {
        perror("freopen");
        return 1;
    }

    // read from stdin using scanf
    if (scanf("%s", buf) == EOF) {
        perror("scanf");
        return 1;
    }

    printf("Input: %s\n", buf);
    return 0;
}