CC ?= gcc
CFLAGS += -Wall -Wextra -Werror -pedantic -std=c99 -O2 -g

# Clang / GCC args for undefined behavior sanitizer
CFLAGS += --analyze -fsanitize=address -fsanitize=undefined -fsanitize-trap=all

# Compile all c files to executables
# https://stackoverflow.com/a/2706067/8524178 (and Copilot?)

SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c, %, $(SRCS))

.PHONY: all
all: $(patsubst %.c, %, $(wildcard *.c))

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
