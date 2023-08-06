#include <stdio.h>

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    char buf[1024];

    // close stdin
    if (fclose(stdin)) {perror("fclose"); return 1;}

    if (!gets(buf)) {perror("gets"); return 1;}

    printf("Input: %s\n", buf);
    return 0;
}
