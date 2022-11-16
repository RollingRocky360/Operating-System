#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define M 5  // Number of Processes
#define N 4  // Number of Resource types

int allocated[M][N] = {
    {0, 0, 1, 2},
    {1, 0, 0, 0},
    {1, 3, 5, 4},
    {0, 6, 3, 2},
    {0, 0, 1, 4}
};
int maximum[M][N] = {
    {0, 0, 1, 2},
    {1, 7, 5, 0},
    {2, 3, 5, 5},
    {0, 6, 5, 2},
    {0, 6, 5, 6}
};
int need[M][N];
int available[N];
int toBeExecuted[M] = {1, 1, 1, 1, 1};
int totalResources[N] = {3, 14, 12, 12};

int sum() {
    int sum = 0;
    for (int i=0; i<M; i++) sum += toBeExecuted[i];
    return sum;
}

int main() {

    for (int r=0; r<N; r++) {
        int sum = 0;
        for (int p=0; p<M; p++)
            available[r] += allocated[p][r];
    }

    for (int r=0; r<N; r++) {
        available[r] = totalResources[r] - available[r];
    }

    for (int p=0; p<M; p++)
        for (int r=0; r<N; r++) 
            need[p][r] = maximum[p][r] - allocated[p][r];

    while (sum() > 0) {
        bool allocatedAtLeastOne = false;
        for (int p=0; p<M; p++) {
            if (!toBeExecuted[p]) continue;

            bool allPossible = true;
            for (int r=0; r<N; r++) 
                allPossible = allPossible & (need[p][r] <= available[r]);
            
            if (!allPossible) continue;

            for (int r=0; r<N; r++) available[r] += allocated[p][r];
            toBeExecuted[p] = 0;
            allocatedAtLeastOne = true;
        }

        if (!allocatedAtLeastOne) {
            printf("Unsafe \n");
            return 1;
        }
    }

    printf("Safe \n");

    return 0;
}