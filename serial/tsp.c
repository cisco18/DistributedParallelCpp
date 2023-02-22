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
    FILE* fp;
    size_t  line_buffer_size=0;
    char *line_buffer = NULL;
    int row, col, val;

    if(argc-1 != 2) {
        printf("There must be 2 inputs!\n");
        exit(-1);
    }

    maxValue = atoi(argv[2]);
    printf("Maximum accepted value: %d\n", maxValue);

    // open input file
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
      printf("Error: unable to open input file");
      exit(1);
    }

    // read input file
    getline(&line_buffer, &line_buffer_size, fp);
    sscanf(line_buffer, "%d %d", &numCities, &numRoads);
    // printf("Number of cities: %d\n", numCities);
    // printf("Number of roads: %d\n", numRoads);

    // allocate space for the distances
    distances = (int**)malloc(numCities*sizeof(int *));
    for(int i=0; i<numCities; i++) {
        distances[i] = (int*)malloc(numCities*sizeof(int));
    }

    // initialize distances matrix
    for(int i=0; i<numCities; i++) {
        for(int j=0; j<numCities; j++) {
            distances[i][j] = -1;
        }
    }

    // fill distances matrix
    for(int i=0; i<numRoads; i++) {
        getline(&line_buffer, &line_buffer_size, fp);
        sscanf(line_buffer, "%d %d %d", &row, &col, &val);
        // printf("%d %d %d\n", row, col, val);
        distances[row][col] = val;
        distances[col][row] = val;
    }


    free(line_buffer);

    // for(int i=0; i<numCities; i++) {
    //     for(int j=0; j<numCities; j++) {
    //         printf("%d ", distances[i][j]);
    //     }
    //     printf("\n");
    // }

    // close input file
    fclose(fp);
}

void tsp() {
    

    // free allocated space for distances
    for(int i=0; i<numCities; i++) {
        free(distances[i]);
    }
    free(distances);
}

void print_result() {

}