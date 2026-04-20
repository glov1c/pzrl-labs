.PHONY: run clean
SOURCES=Stack.cpp StackImplementation.cpp Vector.cpp dllist.cpp main.cpp
OBJECTS=$(SOURCES:.c=.o)


main: $(OBJECTS)
	g++ $(OBJECTS) -o main

%.o: %.cpp
	g++ -c $< -o $@

run: main
	./main

clean:
	rm -f *.o main


