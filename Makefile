CFLAGS=-Wall -Wextra -std=c99
all:
	$(CC) -o ascii-generator.out ./src/main.c ./src/img.c ./src/to_text.c -lm
