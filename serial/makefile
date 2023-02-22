# the compiler: gcc for C program, define as g++ for C++

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings

# The build target
all: queue.o tsp

queue.o: queue.c
	gcc -c queue.c

tsp: queue.h queue.o tsp.c
	gcc -g -Wall -o tsp queue.o tsp.c

clean:
	-rm -f tsp *.o