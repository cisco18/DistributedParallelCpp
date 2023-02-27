#include "tsp.h"
#include <omp.h>

int main(int argc, char *argv[]) {
    double exec_time;

    parse_inputs(argc, argv);

    exec_time = -omp_get_wtime();

    pair<vector <int>, int> results = tsp();

    exec_time += omp_get_wtime();

    cout << "Serial execution time: " << exec_time << endl;

    print_result(results.first, results. second); // to the stdout!
}

void parse_inputs(int argc, char *argv[]) {
    string line;
    ifstream myfile (argv[1]);

    int row, col, val;

    // check number of arguments
    if(argc-1 != 2) {
        // printf("There must be 2 inputs!\n");
        exit(-1);
    }

    // get first line of file with number of cities and roads
    if (myfile.is_open()){
        getline(myfile, line);
        sscanf(line.c_str(), "%d %d", &numCities, &numRoads);
    }else
        cout << "Unable to open file"; 
    // cout << "Cities: " << numCities << "\nRoads: " << numRoads << "\n";

    // initialize distances matrix
    for(int i=0; i<numCities; i++) {
        vector <int> ones(numCities, -1);
        distances.push_back(ones);
    }
    
    // get the distances between cities
    if (myfile.is_open()){
        while (getline(myfile, line)) {
            sscanf(line.c_str(), "%d %d %d", &row, &col, &val);
            distances.at(row).at(col) = val;
            distances.at(col).at(row) = val;
        }
        myfile.close();
    }else 
        cout << "Unable to open file";

    // for(int i=0; i<numCities; i++) {
    //     for(int j=0; j<numCities; j++) {
    //         cout << distances.at(i).at(j) << " ";
    //     }
    //     cout << endl;
    // }

    BestTourCost = atoi(argv[2]);
}

pair<int, int> compareCost(int cost, pair<int, int> min) {
    if(cost > 0) {
        if(cost <= min.first) {
            min.second = min.first;
            min.first = cost;
        }else if(cost <= min.second) {
            min.second = cost;
        }
    }
    return min;
}

int initialLB() {
    pair<int, int> min;
    int cost;
    int LB=0;

    for(int i=0; i<numCities; i++) {
        min.first = BestTourCost;
        min.second = BestTourCost;
        for (int j=0; j<numCities; j++) {
            cost = distances.at(i).at(j);
            min = compareCost(cost, min);
        }
        LB += (min.first+min.second)/2;
    }
    return LB;
}

int calculateLB(int f, int t, int LB) {
    int newLB;
    int cf, ct;
    pair<int, int> min;
    int cost;
    int directCost = distances[f][t];

    min.first = BestTourCost;
    min.second = BestTourCost;
    for (int j=0; j<numCities; j++) {
        cost = distances.at(f).at(j);
        min = compareCost(cost, min);
    }
    if(directCost >= min.second) {
        cf = min.second;
    }else {
        cf = min.first;
    }

    min.first = BestTourCost;
    min.second = BestTourCost;
    for (int j=0; j<numCities; j++) {
        cost = distances.at(t).at(j);
        min = compareCost(cost, min);
    }
    if(directCost >= min.second) {
        ct = min.second;
    }else {
        ct = min.first;
    }

    newLB = LB + directCost - (cf+ct)/2;

    return newLB;
}

// char compare_values(void *a, void *b) {
//     double num_a = *(double*)a;
//     double num_b = *(double*)b;
//     return num_a > num_b;
// }

int isInNode(int val, QueueElem node) {
    for(int i=0; i<node.length; i++) {
        if(node.tour[i] == val) {
            return 1;
        }
    }
    return 0;
}

pair<vector <int>, int> tsp() {
    PriorityQueue<QueueElem> myQueue;

    vector <int> tour = {0};
    QueueElem firstElem = initQueueElem(tour, 0, initialLB(), 1, 0);

    QueueElem myElem;
    vector <int> BestTour = tour;

    QueueElem newElem;
    int newBound, newCost;
    vector <int> newTour;

    myQueue.push(firstElem);

    while(myQueue.size() > 0){
        myElem = myQueue.pop();
        printQueueElem(myElem);
        cout << endl;
        if(myElem.bound >= BestTourCost) {
            return make_pair(BestTour, BestTourCost);
        }
        if(myElem.length == numCities) {
            if(myElem.cost + distances.at(myElem.node).at(0) <= BestTourCost) {
                BestTour = myElem.tour;
                BestTour.push_back(0);
                BestTourCost = myElem.cost + distances.at(myElem.node).at(0);
            }
        }else {
            for(int v=0; v<numCities; v++) {
                if(v != myElem.node && isInNode(v, myElem) == 0) {
                    newBound = calculateLB(myElem.node, v, myElem.bound);
                    if(newBound <= BestTourCost) {
                        newTour = myElem.tour;
                        newTour.push_back(v);
                        newCost = myElem.cost + distances.at(myElem.node).at(v);
                        newElem = initQueueElem(newTour, newCost, newBound, myElem.length+1, v);
                        myQueue.push(newElem);
                        // printQueueElem(newElem);
                        // cout << endl;
                    }
                }
            }
        }
    }
    return make_pair(BestTour, BestTourCost);
}

void print_result(vector <int> BestTour, int BestTourCost) {
    cout << "BestTour: ";
    for(int i=0; i<numCities; i++) {
        cout << BestTour.at(i) << " ";
    }
    cout << endl;
    cout << "BestTourCost: " << BestTourCost << endl;
}