/* Use After Free Unsafe
 *
 * Example of using a pointer after it has been freed,
 * which will cause a crash.
 *
 * Show an example where the use after free may lead to
 * a security vulnerability.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPS 10
#define MAX_OPS_STR_LENGTH 4
#define MAX_OPS_PUT_LENGTH 4096

// Format a string with given length
#define STR(s) XSTR(s)
#define XSTR(s) #s
#define FMT_STR(length) "%" STR(length) "s"

// Make a linked list of operations to call
struct op_ {
    char *name;
    char *put_str;
    int (*op)(int, int);
    struct op_ *next;
};

// Operations
enum op_type {INVALID = 0, ADD, SUB, MUL, DIV, MOD, XOR, AND, OR, PUT};

int op_add(int a, int b) { return a + b; }
int op_sub(int a, int b) { return a - b; }
int op_mul(int a, int b) { return a * b; }
int op_div(int a, int b) { return a / b; }
int op_mod(int a, int b) { return a % b; }
int op_xor(int a, int b) { return a ^ b; }
int op_and(int a, int b) { return a & b; }
int op_or (int a, int b) { return a | b; }
void op_put(char *str) {printf("%s\n", str);}

const char* op_type_to_str(enum op_type op) {
    switch (op) {
        case ADD: return "ADD";
        case SUB: return "SUB";
        case MUL: return "MUL";
        case DIV: return "DIV";
        case MOD: return "MOD";
        case XOR: return "XOR";
        case AND: return "AND";
        case OR : return "OR";
        case PUT: return "PUT";
        default : return "UNKNOWN";
    }
}

enum op_type str_to_op_type(const char *str) {

    const size_t len = MAX_OPS_STR_LENGTH;

    if      (strncmp(str, "ADD", len) == 0) return ADD;
    else if (strncmp(str, "SUB", len) == 0) return SUB;
    else if (strncmp(str, "MUL", len) == 0) return MUL;
    else if (strncmp(str, "DIV", len) == 0) return DIV;
    else if (strncmp(str, "MOD", len) == 0) return MOD;
    else if (strncmp(str, "XOR", len) == 0) return XOR;
    else if (strncmp(str, "AND", len) == 0) return AND;
    else if (strncmp(str, "OR",  len) == 0) return OR;
    else if (strncmp(str, "PUT", len) == 0) return PUT;
    else                                    return INVALID;
}

int free_ops(struct op_ *op_list) {
    // free values in ops
    struct op_ *op = op_list;

    for (int i = 0; i < MAX_OPS; i++) {
        free(op->put_str);
        op = op->next;
    }
}

int parse_ops(FILE *fd, struct op_ *ops) {

    // Read in operations from file
    // Format: <op> <arg>

    struct op_ *op = ops;
    char name[MAX_OPS_NAME_LENGTH];
    char op_str[MAX_OPS_STR_LENGTH];
    int arg;
    int retval;

    for (int i = 0; i < MAX_OPS; i++) {

        errno = 0;
        retval = fscanf(fd,
            FMT_STR(MAX_OPS_NAME_LENGTH)
            FMT_STR(MAX_OPS_STR_LENGTH)
            ", %d",
            name, op_str, &arg);

        if (errno) {
            perror("fscanf");
            return -1;
        } else if (retval == EOF) {
            // Finished reading operations
            break;
        } else if (retval < 2) {
            // couldn't read any more operations
            fprintf(stderr, "Invalid operations file\n");
            return -1;
        }

        const enum op_type op_type = str_to_op_type(op_str);

        // Find the op function value
        int (*op_func)(int, int);

        switch (op_type) {
        case ADD: op_func = &op_add; break;
        case SUB: op_func = &op_sub; break;
        case MUL: op_func = &op_mul; break;
        case DIV: op_func = &op_div; break;
        case MOD: op_func = &op_mod; break;
        case XOR: op_func = &op_xor; break;
        case AND: op_func = &op_and; break;
        case OR : op_func = &op_or;  break;
        default : op_func = NULL;    break;
        }

        if (!op_func) {
            fprintf(stderr, "Invalid operation: %s\n", op_str);
            return -1;
        }

        // Set value on pointer
        op->name = strndup(name, MAX_OPS_NAME_LENGTH);
        op->op = op_func;

        // Increment operator
        op = op->next;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    // Open file with operations
    FILE *fd = fopen("ops_test.txt", "r");

    // Load operations into linked list

    // Run operations

    // Free operations
    // *oops* didn't null pointers

    // Load operations again (but its blank)

    // Run operations again (it should have been blank...)

    // Free operations again

    return 0;
}
