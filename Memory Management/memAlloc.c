#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int PARTITIONS[200];
int SIZE;


int getPartitions() {
	int n;
	printf("Number of Partitions: ");
	scanf("%d", &n);
	SIZE = n;
	
	for (int i=0; i<n; i++) {
	    printf("Parition %d: ", i+1);
	    scanf("%d", &PARTITIONS[i]);
	}
	
	return 0;
}


int displayPartitions() {
    for (int i=0; i<SIZE; i++)
        printf("%d ", PARTITIONS[i]);
    
    printf("\n");
    
    return 1;
}


// Worst Fit Allocation

int getIndexWithMaxDiff(int alloc) {
	int maxIndex = -1;
	int maxDiff = 0;
	for (int i=0; i<SIZE; i++) {
	    int diff = PARTITIONS[i] - alloc;
	    if (diff < 0) continue;
	    if (diff > maxDiff) {
	        maxIndex = i;
	        maxDiff = diff;
	    }
	}
	
	return maxIndex;
}

int worstFitAlloc() {
    int n;
    printf("Number of allocation requests: ");
    scanf("%d", &n);
    
    int req;
    for (int i=0; i<n; i++) {
        printf("Allocation request %d: ", i+1);
        scanf("%d", &req);
        
        int ind = getIndexWithMaxDiff(req);
        if (ind < 0) { printf("External Fragmentation for %d required \n", req); continue; }
        else PARTITIONS[ind] -= req;
        
        displayPartitions();
    }
    
    return 1;
}


// Best Fit Allocation

int getIndexWithMinDiff(int alloc) {
	int minIndex = -1;
	int minDiff = 32000;
	for (int i=0; i<SIZE; i++) {
	    int diff = PARTITIONS[i] - alloc;
	    if (diff < 0) continue;
	    if (diff < minDiff) {
	        minIndex = i;
	        minDiff = diff;
	    }
	}
	
	return minIndex;
}

int bestFitAlloc() {
    int n;
    printf("Number of allocation requests: ");
    scanf("%d", &n);
    
    int req;
    for (int i=0; i<n; i++) {
        printf("Allocation request %d: ", i+1);
        scanf("%d", &req);
        
        int ind = getIndexWithMinDiff(req);
        if (ind < 0) { printf("External Fragmentation for %d required \n", req); continue; }
        else PARTITIONS[ind] -= req;
        
        displayPartitions();
    }
    
    return 1;
}


// First Fit Allocation

int firstFitAlloc() {
    int n;
    printf("Number of allocation requests: ");
    scanf("%d", &n);
    
    int req;
    for (int i=0; i<n; i++) {
        printf("Allocation request %d: ", i+1);
        scanf("%d", &req);
        
        int found = false;
        for (int j=0; j<SIZE; j++) {
            if (PARTITIONS[j] >= req) {
                PARTITIONS[j] -= req;
                found = true;
                break;
            }
        }
        
        if (!found) { printf("External Fragmentation: Cannot add %d yet", req); continue; }
        
        displayPartitions();
    }
    
    return 1;
}




int main() {
    
    getPartitions();
    
    char choice;
    printf("1. First Fit \n2. Best Fit \n3. Worst Fit\n Choice: ");
    scanf(" %c", &choice);
    
    switch (choice) {
    	case '1': firstFitAlloc(); break;
    	case '2': bestFitAlloc(); break;
    	case '3': worstFitAlloc(); break;
    	default : printf("Invalid choice"); exit(1);
	}
    
    return 0;
}





