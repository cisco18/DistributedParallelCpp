#include "tsp-mpi.h"

int main(int argc, char *argv[]) {
    MPI_Status status;
    int pid, p,
    double exec_time;

    MPI_Init (&argc, &argv);

    // get process id
    MPI_Comm_rank (MPI_COMM_WORLD, &pid);
    // get number of processes
    MPI_Comm_size (MPI_COMM_WORLD, &p);

    parse_inputs(argc, argv);

    MPI_Barrier (MPI_COMM_WORLD);
    exec_time = - MPI_Wtime();

    pair<vector <int>, double> results = tsp();

    MPI_Barrier (MPI_COMM_WORLD);
    exec_time += MPI_Wtime();

    cout << "Execution time: " << exec_time << endl;

    print_result(results.first, results. second); // to the stdout!

    MPI_Finalize();
    return 0;
}

void parse_inputs(int argc, char *argv[]) {
    string line;
    ifstream myfile (argv[1]);

    int row, col;
    double val;

    if(argc-1 != 2)
        exit(-1);

    if (myfile.is_open()){
        getline(myfile, line);
        sscanf(line.c_str(), "%d %d", &numCities, &numRoads);
    }else
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
        exit(-1);

    BestTourCost = atof(argv[2]);
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

pair<vector <int>, double> tsp() {
    vector <int> BestTour = {0};
    
    return make_pair(BestTour, BestTourCost);
}