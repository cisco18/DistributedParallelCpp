#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

#include "queue.hpp"
#include "element.h"

void parse_inputs(int argc, char *argv[]);
pair<int, int> compareCost(int cost, int min1, int min2);
int initialLB();
int calculateLB(int f, int t, int LB);
// char compare_values(void *a, void *b);
int isInNode(int val, QueueElem node);
pair<vector <int>, int> tsp();
void print_result(vector <int> BestTour, int BestTourCost);

// global variables
int BestTourCost;
int numCities, numRoads;
vector <vector <int>> distances;