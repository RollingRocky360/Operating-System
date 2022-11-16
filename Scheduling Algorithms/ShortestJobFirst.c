#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Process Process;
typedef struct Node Node;


struct Process {
    int id;
    int arrivalTime;
    int processingTime;
    int startTime;
    int turnAroundTime;
};



void enqueue(Process* p, Process* queue[], int* lastPtr) {
	(*lastPtr)++;
	queue[*lastPtr] = p;
	for (int i=*lastPtr; i>0; i--) {
		if (queue[i]->processingTime > queue[i-1]->processingTime) break;
		Process* temp = queue[i];
		queue[i] = queue[i-1];
		queue[i-1] = temp; 
	}
}

void dequeue(Process* queue[], int* lastPtr) {
    for (int i=0; i<(*lastPtr); i++) 
    	queue[i] = queue[i+1];
    if (*lastPtr >= 0) (*lastPtr)--;
}    

Process* front(Process* queue[], int* lastPtr) {
	if (*lastPtr >= 0)
		return queue[0]; 
	return NULL;
}

      
    
void tablifyProcesses(Process processes[], int n) {
	printf("-----------------------------------------------------------------------------------\n");
	printf("id\t ArrivalTime\t BurstTime\t StartTime\t TurnAround\t WaitTime\n");
	printf("-----------------------------------------------------------------------------------\n");
	for (int i=0; i<n; i++) {
		printf (
			"%d\t\t %d\t\t %d\t\t %d\t\t %d\t    %d\n",
			processes[i].id,
			processes[i].arrivalTime,
			processes[i].processingTime,
			processes[i].startTime,
			processes[i].turnAroundTime,
			processes[i].startTime - processes[i].arrivalTime
		);
	}	
}



int main() {
    
    Process processes[] = {
		{0, 0, 3, 0, 0},
		{1, 1, 6, 0, 0},
		{2, 4, 4, 0, 0},
		{3, 6, 2, 0, 0}
    };
    
    int NO_OF_PROCESSES = 4;
    int CLOCK = 0;
    
    Process* buffer[100];
    int last = -1;
    int running = -1;
    Process* nextProc;
    int processed = 0;
    int processing = 0;
    
    for (CLOCK=0; CLOCK<32000; CLOCK++) {
	    while (processing < NO_OF_PROCESSES && processes[processing].arrivalTime == CLOCK)
			enqueue(&processes[processing++], buffer, &last);
    
		if (running > 0) { 
			--running;  
			
            if (running == 0) {
                processed++;
                nextProc->turnAroundTime = CLOCK - nextProc->arrivalTime;
                printf (
                    "Process %d completed \nRuntime: %d \nTurnaround: %d \nWait time: %d \n\n", 
                    nextProc->id, 
                    nextProc->processingTime, 
                    nextProc->turnAroundTime,
                    nextProc->startTime - nextProc->arrivalTime
                );
            }
            else
                continue;
		}
    	
		    
	    if (processed >= NO_OF_PROCESSES) break;    
		    
	    nextProc = front(buffer, &last);
		if (nextProc == NULL) continue;
	    dequeue(buffer, &last);

	    printf("Running Process %d\n", nextProc->id);
	    nextProc->startTime = CLOCK;
	    running = nextProc->processingTime;        
    }
    
    printf("\n\n");
    tablifyProcesses(processes, NO_OF_PROCESSES);

    return 0;
}