#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// #include "queue.hpp"

void parse_inputs(int argc, char *argv[]);
int initialLB();
int calculateLB(int f, int t, int LB);
char compare_values(void *a, void *b);
void tsp();
void print_result();

// global variables
int maxValue;
int numCities, numRoads;