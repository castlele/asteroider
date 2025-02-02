CC=gcc
CFLAGS=-Wall -std=c99 -Werror -D_DEFAULT_SOURCE

LIBS_DIR=libs
INC=-I/usr/local/include/ -I/src/
LIB=-L/usr/local/lib/ -lraylib -lm

SRC=./src
APP=./build/asteroider

.PHONY: run build clean

run: build
	$(APP)

build: $(SRC)/main.o $(SRC)/asteroid.o
	$(CC) -o $(APP) $^ $(CFLAGS) $(INC) $(LIB)

$(SRC)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $< -g -MMD

clean:
	rm $(SRC)/*.o
	rm $(SRC)/*.d
	rm $(APP)
