#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

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