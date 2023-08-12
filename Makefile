CC ?= gcc
CFLAGS += -Wall -Wextra -pedantic -std=c99 -g

# Clang / GCC args for undefined behavior sanitizer
CFLAGS += -O1 -fsanitize=address -fsanitize=undefined -fsanitize-trap=all -fno-optimize-sibling-calls -fno-omit-frame-pointer

# Compile all c files to executables
# https://stackoverflow.com/a/2706067/8524178 (and Copilot?)

SRCS = $(wildcard common_user_error/*.c logical/*.c memory/*.c overflow/*.c undefined_behavior/*.c)
PROGS = $(patsubst %.c, %, $(SRCS))

.PHONY: all
all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: safe unsafe
safe: all
	for p in $(wildcard *_safe); do echo "Running $$p"; ./$$p; done

unsafe: all
	for p in $(wildcard *_unsafe); do echo "Running $$p"; ./$$p; done

.PHONY: clean
clean:
	rm -f $(PROGS)
	rm -rf *.dSYM
