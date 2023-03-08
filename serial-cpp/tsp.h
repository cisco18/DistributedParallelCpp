#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

#include "queue.hpp"
#include "element.h"

void parse_inputs(int argc, char *argv[]);
double initialLB();
double calculateLB(int f, int t, double LB);
pair<vector <int>, double> tsp();
void print_result(vector <int> BestTour, double BestTourCost);

// global variables
double BestTourCost;
int numCities, numRoads;
vector <vector <double>> distances;