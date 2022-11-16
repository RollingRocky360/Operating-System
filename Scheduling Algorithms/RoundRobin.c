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
    int remainingTime;
    int waitTime;
    int lastBroke;
};

struct Node {
    Process* proc;
    Node* next;
};

struct EndNodes {
    Node* head;
    Node* tail;
} e = {NULL, NULL};



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



int enqueue(Process* newp) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->proc = newp;
    newNode->next = NULL;
    
    
    if (e.tail == NULL) {
        e.head = e.tail = newNode;
        return 0;
    }
    
    e.tail->next = newNode;
    e.tail = newNode;
    
    return 1;
}

int dequeue() {
    if (e.head == NULL)
        return 1;
    
    if (e.head == e.tail) {
        e.head = e.tail = NULL;
        return 1;
    }    
    
    e.head = e.head->next; 
    return 0;
}    

Process* front() {
    if (e.head == NULL) return NULL;
    return e.head->proc;
}



int main() {
    
    Process processes[] = {
		{0, 0, 3, 0, 0, -1, 0, 0},
		{1, 1, 6, 0, 0, -1, 0, 1},
		{2, 4, 4, 0, 0, -1, 0, 4},
		{3, 6, 2, 0, 0, -1, 0, 6}
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
	    while (addedToQueue < NO_OF_PROCESSES && processes[addedToQueue].arrivalTime == CLOCK)
			enqueue(&processes[addedToQueue++]);   

		
        // If current process has been using the CPU for <timeSlice> ms
        // add it to the end of the queue and dequeue the next waiting process
		if (ticks == timeSlice) {
            if (running != NULL) {
                running->lastBroke = CLOCK;
                enqueue(running);
            }
            
            running = front();
            if (running != NULL) {
                ticks = 0;
                running->waitTime += CLOCK - running->lastBroke;
                running->startTime = CLOCK;
                if (running->remainingTime == -1)
                    running->remainingTime = running->processingTime;
                dequeue();
            }	
        }


        // If there is some process currently running decrement its remaining time
        // and increment its ticks(CPU util time since the last slice). The remaining
        // time on becoming zero should trigger the removal of the said process from 
        // the system and display its metrics
		if (running != NULL) { 
            ticks++;
		    if (--(running->remainingTime) == 0) {
		        processed++;
		        running->turnAroundTime = CLOCK - running->arrivalTime + 1;
			    printf (
				    "Process %d completed \nRuntime: %d \nTurnaround: %d \nWait time: %d \n\n", 
				    running->id, 
				    running->processingTime, 
				    running->turnAroundTime,
				    running->waitTime
			    );
		        running = NULL;
                ticks = timeSlice;
		    } 
		}

        if (processed == NO_OF_PROCESSES)break;
		
    }
    
    tablifyProcesses(processes, NO_OF_PROCESSES);

    return 0;
}