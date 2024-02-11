CC ?= gcc
CFLAGS += -g -Wall -Wextra -pedantic -std=c99

# Compile all c files to executables
SRC_DIR = common_user_error logical memory overflow undefined_behavior

SAFE_SRCS = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*_safe.c))
UNSAFE_SRCS = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*_unsafe.c))

BUILD_DIR ?= .

SAFE_PROGS = $(addprefix $(BUILD_DIR)/, $(patsubst %.c, %, $(SAFE_SRCS)))
UNSAFE_PROGS = $(addprefix $(BUILD_DIR)/, $(patsubst %.c, %, $(UNSAFE_SRCS)))

PROGS = $(SAFE_PROGS) $(UNSAFE_PROGS)

.PHONY: all
all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: safe
safe: $(SAFE_PROGS)
	for p in $^; do echo "Running $$p"; ./$$p; done

.PHONY: unsafe
unsafe: $(UNSAFE_PROGS)
	for p in $^; do echo "Running $$p"; ./$$p; done

.PHONY: clean
clean:
	rm -f $(PROGS)
	rm -rf **/*.dSYM
