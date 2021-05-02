CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: tsp

tsp: tsp.o path.o graph.o stack.o
	$(CC) -o tsp tsp.o path.o graph.o stack.o -lm 

tsp.o: tsp.c
	$(CC) $(CFLAGS) -c tsp.c

path.o: path.c
	$(CC) $(CFLAGS) -c path.c

graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -f tsp tsp.o path.o graph.o stack.o

format:
	clang-format -i -style=file tsp.c path.c graph.c stack.c

scan-build: clean
	scan-build make
