#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

int computeFirstLB();
int computLB();

// Global variables
// priority_queue_t *queueS;

int main(int argc, char *argv[]) {
    int numCities, numRoads;
    FILE* file_handle;
    file_handle = fopen(argv[1], "r");

    if(file_handle == NULL) {
      printf("Error!");
      exit(1);
    }

    fscanf(file_handle,"%d %d", &numCities, &numRoads);
    printf("Number of cities: %d\n", numCities);
    printf("Number of roads: %d\n", numRoads);


    // int val = computeFirstLB();
    fclose(file_handle);
    return 0;
}

// void TSPBB(int distances[][], int numberOfCities,int BestTourCost) {
//     int currentCity = 0;    
//     int tour[100];  //later we need a specific number
//     int lowerBound = computeFirstLB(); //dont know what yet

//     tour[0] = 0;

//     while (queueS->size > 0){
//         // int[] tour,int cost, int bound,int length, int currentCity} = queue_pop(queueS);
//         // if(bound<)
//     }

// }

int computeFirstLB() {
    // int min1=queueS->buffer[0], min2=queueS->buffer[1];
    // for(int i=0; i++; i<queueS->size) {
    //     if(queueS->buffer[i] < min1) {
    //         min2 = min1;
    //         min1 = queueS->buffer[i];
    //     } else if(queueS->buffer[i] < min2) {
    //         min2 = queueS->buffer[i];
    //     }
    // }
    // return min1 + min2;
    return 0;
}

int computeLB() {
    return 0;
}