// Simply check to see if a
// repeatable use-after-free can be made

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    int *others[10] = {NULL};

    int *a = malloc(sizeof(int));
    if (!a) {
        perror("malloc");
        return 1;
    }

    *a = 42;

    printf("a = %d\n", *a);
    free(a);

    for (int i = 0; i < 10; i++) {
        others[i] = malloc(sizeof(int));
        if (!others[i]) {
            perror("malloc");
            goto exit;
        }

        *others[i] = 3 * i + 1;
    }

    for (int i = 0; i < 10; i++) {
        printf("others[%d] = %d\n", i, *others[i]);
    }

    printf("a = %d\n", *a);

exit:
    for (int i = 0; i < 10; i++) {
        free(others[i]);
    }
    return 0;
}
