all:
	gcc -o pipe_test piping.c -lm

run: all
	./pipe_test
