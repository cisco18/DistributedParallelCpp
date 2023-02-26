#include "tsp.h"

// struct QueueElem queueElem; 

QueueElem initQueueElem(vector<int> tour, int cost, int bound, int lenght, int currentCity) {
    QueueElem elem =  {tour, cost, bound, lenght, currentCity};
    return elem;
}

void printQueueElem(QueueElem myElem) {
    cout << "Tour: ";
    for(int i=0; i<myElem.length; i++) {
        cout << myElem.tour.at(i) << " ";
    }
    cout << endl;
    cout << "Cost: " << myElem.cost << endl;
    cout << "Bound: " << myElem.bound << endl;
}

int main(int argc, char *argv[]) {
    // double exec_time;

    parse_inputs(argc, argv);

    // exec_time = -omp_get_wtime();

    tsp();

    // exec_time += omp_get_wtime();

    // fprintf(stderr, "%.1fs\n", exec_time);
    print_result(); // to the stdout!
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

    maxValue = atoi(argv[2]);
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
        min.first = maxValue;
        min.second = maxValue;
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

    min.first = maxValue;
    min.second = maxValue;
    for (int j=0; j<numCities; j++) {
        cost = distances.at(f).at(j);
        min = compareCost(cost, min);
    }
    if(directCost >= min.second) {
        cf = min.second;
    }else {
        cf = min.first;
    }

    min.first = maxValue;
    min.second = maxValue;
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

char compare_values(void *a, void *b) {
    double num_a = *(double*)a;
    double num_b = *(double*)b;
    return num_a > num_b;
}

void tsp() {
    PriorityQueue<QueueElem> myQueue;
    vector <int> tour = {0};
    QueueElem firstElem = initQueueElem(tour, 0, initialLB(), 1, 0);
    // printQueueElem(firstElem);
    myQueue.push(firstElem);
    myQueue.print(&printQueueElem);
    // while(myQueue.size>0){
    //      myQueue.pop();
    // }
}

void print_result() {
    
    
}