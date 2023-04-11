# the compiler: gcc for C program, define as g++ for C++

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings

# The build target
all: tsp-mpi tsp-mpi.o

tsp-mpi.o: tsp-mpi.cpp tsp-mpi.h
	mpic++ -g -o tsp-mpi.cpp

tsp-mpi: tsp-mpi.o
	mpic++ -g -o tsp-mpi tsp-mpi.cpp

clean:
	-rm -f tsp-mpi *.o
