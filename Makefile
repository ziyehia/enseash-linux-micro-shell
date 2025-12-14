CC = gcc
CFLAGS += -Wall -Wextra -g -Iinclude

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
BIN = $(patsubst src/%.c, build/%, $(SRC))

all: $(BIN)

build/%: build/%.o $(filter-out build/%.o,$(OBJ))
	mkdir -p build
	$(CC) $^ -o $@

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

indent:
	indent -linux -i4 -nut -ts2 src/*.c

clean:
	rm -rf build/*

.PHONY: all clean indent

