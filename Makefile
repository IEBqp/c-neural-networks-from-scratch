CC = gcc
CFLAGS = -Wall -Wextra -O3 -Iinclude
LDFLAGS = -lm
BIN_DIR = bin

SRCS = $(shell find src -name '*.c')
OBJS = $(SRCS:.c=.o)
TARGET = neural_net

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# To make bin/any_example, look in examples/any_example.c
$(BIN_DIR)/%: examples/%.c $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	
clean:
	rm -f src/*.o $(TARGET)
	rm -rf $(BIN_DIR)
