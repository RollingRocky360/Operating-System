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

struct Node {
    Process* proc;
    Node* next;
};


Node* enqueue(Node* head, Process* newp) {
	Node* curr;
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->proc = newp;
    newNode->next = NULL;
     
    if (head == NULL) 
        return newNode;
        
    for (curr=head; curr->next != NULL; curr = curr->next);
    curr->next = newNode;
    
    return head;
}

Node* dequeue(Node* head) {
    if (head == NULL)
        return head;
        
    return head->next;
}    

Process* front(Node* head) {
    if (head == NULL)
        return NULL;
        
    return head->proc;
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
		{1, 5, 6, 0, 0},
		{2, 6, 4, 0, 0},
		{3, 7, 2, 0, 0}
    };
    
    int NO_OF_PROCESSES = 4;
    int CLOCK = 0;
    Node* HEAD = NULL; 
    int running=-1;
    Process* nextProc;
    int processed = 0;
    int processing = 0;
    
    for (CLOCK=0; CLOCK<32000; CLOCK++) {
	    
	    while (processing < NO_OF_PROCESSES && processes[processing].arrivalTime == CLOCK)
			HEAD = enqueue(HEAD, &processes[processing++]);
    
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
		    
	    nextProc = front(HEAD);
	    if (nextProc == NULL) continue;
	    HEAD = dequeue(HEAD);
	    
	    
	    printf("Running Process %d\n", nextProc->id);
	    nextProc->startTime = CLOCK;
	    running = nextProc->processingTime;        
    }
    
    printf("\n\n");
    tablifyProcesses(processes, NO_OF_PROCESSES);

    return 0;
}
