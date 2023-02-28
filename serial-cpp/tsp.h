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
pair<double, double> compareCost(double cost, double min1, double min2);
double initialLB();
double calculateLB(int f, int t, double LB);
// char compare_values(void *a, void *b);
int isInNode(int val, QueueElem node);
pair<vector <int>, double> tsp();
void print_result(vector <int> BestTour, double BestTourCost);

// global variables
double BestTourCost;
int numCities, numRoads;
vector <vector <double>> distances;