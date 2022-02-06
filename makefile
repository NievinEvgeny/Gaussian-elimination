all: matrix.c
		gcc -Wall -o matrix $^
clean:
		rm matrix