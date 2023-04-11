# the compiler: gcc for C program, define as g++ for C++

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
NUM_PROCESSES = 4
FILE = gen10-20.in
VAL = 10
# The build target
all: tsp-mpi tsp-mpi.o

tsp-mpi.o: tsp-mpi.cpp tsp-mpi.h
	mpic++ -c -O3 -fopenmp tsp-mpi.cpp

tsp-mpi: tsp-mpi.o
	mpic++ -g -Wall -O3 -o tsp-mpi -fopenmp tsp-mpi.o

clean:
	-rm -f tsp-mpi *.o

run: 
	mpirun -n $(NUM_PROCESSES) ./tsp-mpi $(FILE) $(VAL)