CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -O0 -ggdb -no-pie
LIBS = -lm

SRC = cachesim.c src/cache.c src/estadisticas.c src/simulador.c
OBJ = $(SRC:.c=.o)

all: cachesim

cachesim: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f $(OBJ) cachesim