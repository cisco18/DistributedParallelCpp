#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

struct QueueElem{
  vector<int> tour;
  double cost;
  double bound;
  int length;
  int node;
  friend bool operator>(QueueElem left, QueueElem right) {
    return left.bound > right.bound;
  }
};

void printQueueElem(QueueElem myElem);