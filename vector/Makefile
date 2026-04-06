.PHONY: run clean
CFLAGS=-fsanitize=address -g

all: run

main: main.o Vector.o
	g++ $(CFLAGS) main.o Vector.o -o main

main.o: main.cpp
	g++ -c $(CFLAGS) main.cpp

Vector.o: Vector.cpp
	g++ -c $(CFLAGS) Vector.cpp

run: main
	./main

clean:
	rm -f *.o main
