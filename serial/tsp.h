#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#include "queue.h"

void parse_inputs();
void tsp();
void print_result();

// Global variables
int maxValue;
int numCities, numRoads;
int **distances;
// priority_queue_t *queueS;