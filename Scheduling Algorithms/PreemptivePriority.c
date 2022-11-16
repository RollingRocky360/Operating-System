#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Process {
    int id;
    int arrivalTime;
    int processingTime;
    int startTime;
    int turnAroundTime;
    int remainingTime;
    int priority;
    int waitTime;
    int lastBroke;
} Process;

Process* QUEUE[20] = { NULL };
int END = 0;


void tablifyProcesses(Process processes[], int n) {
	printf("-----------------------------------------------------------------------------------\n");
	printf("id\t ArrivalTime\t BurstTime\t StartTime\t TurnAround\t WaitTime\n");
	printf("-----------------------------------------------------------------------------------\n");
	for (int i=0; i<n; i++) {
        Process p = processes[i];
		printf (
			"%d\t\t%d\t\t%d\t\t\%d\t\t%d\t\t%d\n",
			p.id,
			p.arrivalTime,
			p.processingTime,
			p.startTime,
			p.turnAroundTime,
			p.waitTime
		);
	}	
}


void push(Process* newp) {
    QUEUE[END++] = newp;

    int curr = END-1;
    while (curr > 0) {
        Process* treeParent = QUEUE[curr/2];
        if (treeParent->priority > newp->priority) break;

        Process* temp = QUEUE[curr/2];
        QUEUE[curr/2] = QUEUE[curr];
        QUEUE[curr] = temp;

        curr /= 2;
    }
}

int pop() {
    if (QUEUE[0] == NULL) return 1;
    if (END == 1) { QUEUE[0] = NULL; END--; return 1; }

    QUEUE[0] = QUEUE[END-1];
    QUEUE[END-1] = NULL;
    END--;

    int curr = 0;
    while (2*curr+2 <= END) {
        Process* currProc = QUEUE[curr];
        int swap;
        int left = 2*curr + 1, right = left+1;
        if (currProc->priority < QUEUE[left]->priority) swap = left;
        if (right < END && currProc->priority < QUEUE[right]->priority)
            if (QUEUE[right]->priority > QUEUE[swap]->priority) swap = right;
        
        Process* temp = QUEUE[curr];
        QUEUE[curr] = QUEUE[swap];
        QUEUE[swap] = temp;

        curr = swap;
    }

    return 0;
}

Process* getMax() {
    return QUEUE[0];
}


int main() {
    
    Process processes[] = {
		{0, 0, 4, -1, 0, 0, 3, 0, 0},
		{1, 1, 3, -1, 0, 0, 4, 0, 0},
		{2, 2, 3, -1, 0, 0, 6, 0, 0},
		{3, 3, 5, -1, 0, 0, 5, 0, 0}
    };
    
    int NO_OF_PROCESSES = 4;
    int CLOCK = 0;
    int processed = 0;
    int addedToQueue = 0;
    int timeSlice = 2, ticks = 2;

    Process* nextProc;
    Process* running = NULL;
    
    for (CLOCK=0; CLOCK<32000; CLOCK++) {

	    // Add new processes to waiting queue if any arrived at that time
	    while (addedToQueue < NO_OF_PROCESSES && processes[addedToQueue].arrivalTime == CLOCK) {
            Process* newp = &processes[addedToQueue++];
            newp->remainingTime = newp->processingTime;
            newp->lastBroke = newp->arrivalTime-1;
			push(newp);   
        }

		
        if ((running = getMax()) != NULL) {
            if (running->startTime == -1) running->startTime = CLOCK;
            running->waitTime += CLOCK - running->lastBroke - 1;
            running->lastBroke = CLOCK;
            if (--(running->remainingTime) == 0) {
                running->turnAroundTime = CLOCK - running->arrivalTime + 1;
                processed++;
                pop();
            }
        }

        if (processed == NO_OF_PROCESSES) break;
		
    }
    
    tablifyProcesses(processes, NO_OF_PROCESSES);

    return 0;
}