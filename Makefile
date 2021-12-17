all:

test:
	gcc -g ./tests/test.c -o test.out -lm && cd tests && ./test.out