CC = g++

CFLAGS = -c -Wall

all: run

run:
	$(CC) main.cpp operations/operation.cpp tester/tester.cpp -o run

.PHONY : clean
clean:
	rm -rf *.o run
