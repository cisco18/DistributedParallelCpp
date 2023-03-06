#include "tsp.h"
#include <omp.h>

int main(int argc, char *argv[]) {
    double exec_time;

    parse_inputs(argc, argv);

    exec_time = -omp_get_wtime();

    pair<vector <int>, double> results = tsp();

    exec_time += omp_get_wtime();

    cout << "Serial execution time: " << exec_time << endl;

    print_result(results.first, results. second); // to the stdout!

    return 0;
}

void parse_inputs(int argc, char *argv[]) {
    string line;
    ifstream myfile (argv[1]);

    int row, col;
    double val;

    if(argc-1 != 2) {
        // cout << "There must be 2 inputs!\n";
        exit(-1);
    }

    if (myfile.is_open()){
        getline(myfile, line);
        sscanf(line.c_str(), "%d %d", &numCities, &numRoads);
    }else
        // cout << "Unable to open file"; 
        exit(-1);
    for(int i=0; i<numCities; i++) {
        vector <double> ones(numCities, -1.0);
        distances.push_back(ones);
    }
    
    if (myfile.is_open()){
        while (getline(myfile, line)) {
            sscanf(line.c_str(), "%d %d %lf", &row, &col, &val);
            distances.at(row).at(col) = val;
            distances.at(col).at(row) = val;
        }
        myfile.close();
    }else 
        cout << "Unable to open file";

    BestTourCost = atof(argv[2]);
}

pair<double, double> compareCost(double cost, pair<double, double> min) {
    if(cost <= min.first) {
        min.second = min.first;
        min.first = cost;
    }else if(cost <= min.second) {
        min.second = cost;
    }
    return min;
}

double initialLB() {
    pair<double, double> min;
    double LB=0;

    for(int i=0; i<numCities; i++) {
        min.first = BestTourCost;
        min.second = BestTourCost;
        for (int j=0; j<numCities; j++) {
            if(distances.at(i).at(j) > 0) {
                min = compareCost(distances.at(i).at(j), min);
            }
        }
        LB += (min.first+min.second)/2;
    }
    return LB;
}

double calculateLB(int f, int t, double LB) {
    double cf, ct;
    pair<double, double> minf, mint;
    double directCost = distances[f][t];

    if(distances[f][t] <= 0) {
        cout << "ERROR";
    }

    minf.first = BestTourCost;
    minf.second = BestTourCost;
    mint.first = BestTourCost;
    mint.second = BestTourCost;
    for (int j=0; j<numCities; j++) {
        if(distances.at(f).at(j) > 0) {
            minf = compareCost(distances.at(f).at(j), minf);
        }
        if(distances.at(t).at(j) > 0) {
            mint = compareCost(distances.at(t).at(j), mint);
        }
    }

    if(directCost >= minf.second) {
        cf = minf.second;
    }else {
        cf = minf.first;
    }

    if(directCost >= mint.second) {
        ct = mint.second;
    }else {
        ct = mint.first;
    }

    return LB + directCost - (cf+ct)/2;
}

int isInNode(int val, QueueElem node) {
    for(int i=0; i<node.length; i++) {
        if(node.tour[i] == val) {
            return 1;
        }
    }
    return 0;
}

pair<vector <int>, double> tsp() {
    PriorityQueue<QueueElem> myQueue;

    vector <int> tour = {0};
    QueueElem firstElem = initQueueElem(tour, 0.0, initialLB(), 1.0, 0.0);

    QueueElem myElem;
    vector <int> BestTour = tour;

    QueueElem newElem;
    double newBound, newCost;
    vector <int> newTour;

    myQueue.push(firstElem);

    while(myQueue.size() > 0){
        // myQueue.print(printQueueElem);
        // cout << endl;
        myElem = myQueue.pop();
        if(myElem.bound >= BestTourCost) {
            return make_pair(BestTour, BestTourCost);
        }
        if(myElem.length == numCities) {
            double dist = distances.at(myElem.node).at(0);
            if(dist > 0) {
                if(myElem.cost + dist <= BestTourCost) {
                    BestTour = myElem.tour;
                    BestTour.push_back(0);
                    BestTourCost = myElem.cost + dist;
                }
            }
        }else {
            for(int v=0; v<numCities; v++) {
                if(v != myElem.node && isInNode(v, myElem) == 0) {
                    double dist = distances.at(myElem.node).at(v);
                    if(dist > 0) {
                        newBound = calculateLB(myElem.node, v, myElem.bound);
                        if(newBound <= BestTourCost) {
                            newTour = myElem.tour;
                            newTour.push_back(v);
                            newElem = initQueueElem(newTour, myElem.cost + dist, newBound, myElem.length+1, v);
                            myQueue.push(newElem);
                        }
                    }
                }
            }
        }
    }
    return make_pair(BestTour, BestTourCost);
}

void print_result(vector <int> BestTour, double BestTourCost) {
    if(BestTour.size() != numCities+1) {
        cout << "NO SOLUTION" << endl;
    } else {
        cout.precision(1);
        cout << fixed << BestTourCost << endl;
        for(int i=0; i<numCities+1; i++) {
            cout << BestTour.at(i) << " ";
        }
        cout << endl;
    }
}