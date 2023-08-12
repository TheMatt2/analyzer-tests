CC ?= gcc
CFLAGS += -Wall -Wextra -pedantic -std=c99 -g

# Clang / GCC args for undefined behavior sanitizer
CFLAGS += -O1 -fsanitize=address -fsanitize=undefined -fsanitize-trap=all -fno-optimize-sibling-calls -fno-omit-frame-pointer

# Compile all c files to executables
# https://stackoverflow.com/a/2706067/8524178 (and Copilot?)

SRC_DIR = common_user_error logical memory overflow undefined_behavior

SAFE_SRCS = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*_safe.c))
UNSAFE_SRCS = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*_unsafe.c))

SAFE_PROGS = $(patsubst %.c, %, $(SAFE_SRCS))
UNSAFE_PROGS = $(patsubst %.c, %, $(UNSAFE_SRCS))

PROGS = $(SAFE_PROGS) $(UNSAFE_PROGS)

.PHONY: all
all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: safe unsafe
safe: $(SAFE_PROGS)
	for p in $^; do echo "Running $$p"; ./$$p; done

unsafe: $(UNSAFE_PROGS)
	for p in $^; do echo "Running $$p"; ./$$p; done

.PHONY: clean
clean:
	rm -f $(PROGS)
	rm -rf **/*.dSYM
