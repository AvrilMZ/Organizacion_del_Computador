CC = gcc
CFLAGS = -Wall -Wextra -pedantic
TARGET = ej2

all: clean $(TARGET)

$(TARGET): ej2.o
	$(CC) $(CFLAGS) ej2.o -o $(TARGET)

ej2.o: basico_ej1.c
	$(CC) $(CFLAGS) -c basico_ej1.c -o ej2.o

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean