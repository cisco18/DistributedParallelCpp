#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#include "queue.h"

void parse_inputs();
int initialLB();
int calculateLB(int f, int t, int LB);
char compare_values(void *a, void *b);
void print_double(FILE* fp, void* num);
void tsp();
void print_result();

// Global variables
int maxValue;
int numCities, numRoads;
int **distances;
// priority_queue_t *queueS;