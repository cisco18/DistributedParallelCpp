#include "element.h"

QueueElem initQueueElem(vector<int> tour, int cost, int bound, int lenght, int currentCity) {
    QueueElem elem =  {tour, cost, bound, lenght, currentCity};
    return elem;
}

void printQueueElem(QueueElem myElem) {
    cout << "Node: " << myElem.node << endl;
    cout << "Tour: ";
    for(int i=0; i<myElem.length; i++) {
        cout << myElem.tour.at(i) << " ";
    }
    cout << endl;
    cout << "Cost: " << myElem.cost << endl;
    cout << "Bound: " << myElem.bound << endl;
    cout << "Lenght: " << myElem.length << endl;
}