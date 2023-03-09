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
            distances[row][col] = val;
            distances[col][row] = val;
        }
        myfile.close();
    }else 
        cout << "Unable to open file";

    BestTourCost = atof(argv[2]);
}

double initialLB() {
    double min1, min2;
    double LB=0;

    for(int i=0; i<numCities; i++) {
        min1 = BestTourCost;
        min2 = BestTourCost;
        for (int j=0; j<numCities; j++) {
            if(distances[i][j] > 0) {
                if(distances[i][j] <= min1) {
                    min2 = min1;
                    min1 = distances[i][j];
                }else if(distances[i][j] <= min2) {
                    min2 = distances[i][j];
                }
            }
        }
        LB += (min1+min2)/2;
    }
    return LB;
}

double calculateLB(int f, int t, double LB) {
    double cf, ct;
    double minf1=BestTourCost, minf2=BestTourCost, mint1=BestTourCost, mint2=BestTourCost;
    double directCost = distances[f][t];

    if(distances[f][t] <= 0) {
        cout << "ERROR";
        exit(-1);
    }

    for (int j=0; j<numCities; j++) {
        double dist1 = distances[f][j];
        double dist2 = distances[t][j];
        if(dist1 > 0) {
            if(dist1 <= minf1) {
                minf2 = minf1;
                minf1 = dist1;
            }else if(dist1 <= minf2) {
                minf2 = dist1;
            }
        }
        if(dist2 > 0) {
            if(dist2 <= mint1) {
                mint2 = mint1;
                mint1 = dist2;
            }else if(dist2 <= mint2) {
                mint2 = dist2;
            }
        }
    }

    if(directCost >= minf2) {
        cf = minf2;
    }else {
        cf = minf1;
    }

    if(directCost >= mint2) {
        ct = mint2;
    }else {
        ct = mint1;
    }

    return LB + directCost - (cf+ct)/2;
}

pair<vector <int>, double> tsp() {
    PriorityQueue<QueueElem> myQueue;

    vector <int> BestTour = {0};
    BestTour.reserve(numCities+1);

    vector <int> newTour;
    newTour.reserve(numCities+1);

    myQueue.push({{0}, 0.0, initialLB(), 1, 0});
    
    while(myQueue.size() > 0){
        bool visitedCities[numCities] = {false};

        QueueElem myElem = myQueue.pop();
        for (int city : myElem.tour) {
            visitedCities[city] = true;
        }

        if(myElem.bound >= BestTourCost) {
            return make_pair(BestTour, BestTourCost);
        }

        if(myElem.length == numCities) {
            double dist = distances[myElem.node][0];
            if(dist > 0) {
                if(myElem.cost + dist <= BestTourCost) {
                    BestTour = myElem.tour;
                    BestTour.push_back(0);
                    BestTourCost = myElem.cost + dist;
                }
            }
        }else {  
            for(int v=0; v<numCities; v++) {
                double dist = distances[myElem.node][v];
                if(dist>0 && v!=myElem.node && !visitedCities[v]) {
                    double newBound = calculateLB(myElem.node, v, myElem.bound);                       
                    if(newBound <= BestTourCost) {
                        newTour = myElem.tour;
                        newTour.push_back(v);
                        myQueue.push({newTour, myElem.cost + dist, newBound, myElem.length+1, v});
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
            cout << BestTour[i] << " ";
        }
        cout << endl;
    }
}