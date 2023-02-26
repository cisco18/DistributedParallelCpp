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
char compare_values(void *a, void *b);
void tsp();
void print_result();

struct QueueElem{
  vector<int> tour;
  int cost;
  int bound;
  int length;
  int node;
  friend bool operator>(QueueElem left, QueueElem right) { return left.length > right.length; }
};

QueueElem initQueueElem(vector<int> tour, int cost, int bound, int lenght, int currentCity);
void printQueueElem(QueueElem myElem);

// global variables
int maxValue;
int numCities, numRoads;
vector <vector <int>> distances;