# the compiler: gcc for C program, define as g++ for C++

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings

# The build target
all: tsp tsp.o

tsp.o: tsp.cpp tsp.h
	gcc -c tsp.cpp

tsp: tsp.o
	g++ -g -Wall -o tsp tsp.o

clean:
	-rm -f tsp *.o