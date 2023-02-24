#include "tsp.h"

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
    std::string line;
    std::ifstream myfile (argv[1]);
    int row, col, val;

    // check number of arguments
    if(argc-1 != 2) {
        // printf("There must be 2 inputs!\n");
        exit(-1);
    }

    // get first line of file with number of cities and roads
    getline(myfile, line);
    sscanf(line.c_str(), "%d %d", &numCities, &numRoads);
    std::cout << "Cities: " << numCities << "\nRoads: " << numRoads << "\n";

    // initialize distances matrix
    
    // get the distances between cities
    if (myfile.is_open()){
        while (getline(myfile, line)) {
            sscanf(line.c_str(), "%d %d %d", &row, &col, &val);
        }
        myfile.close();
    }else 
        std::cout << "Unable to open file"; 
}

int initialLB() {
    return 0;
}

int calculateLB(int f, int t, int LB) {
    return 0;
}

char compare_values(void *a, void *b) {
    double num_a = *(double*)a;
    double num_b = *(double*)b;
    return num_a > num_b;
}

void tsp() {

}
void print_result() {

}