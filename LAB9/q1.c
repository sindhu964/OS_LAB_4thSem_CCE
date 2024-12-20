#include<stdio.h>

void firstFit(int blockSize[], int m, int processSize[], int n) 
{ 
    int i, j; 
    // Stores block id of the 
    // block allocated to a process 
    int allocation[n]; 
  
    // Initially no block is assigned to any process 
    for(i = 0; i < n; i++) 
    { 
        allocation[i] = -1; 
    } 
    
    // pick each process and find suitable blocks 
    // according to its size ad assign to it 
    for (i = 0; i < n; i++)        //here, n -> number of processes 
    { 
        for (j = 0; j < m; j++)        //here, m -> number of blocks 
        { 
            if (blockSize[j] >= processSize[i]) 
            { 
                // allocating block j to the ith process 
                allocation[i] = j; 
  
                // Reduce available memory in this block. 
                blockSize[j] -= processSize[i]; 
  
                break;    //go to the next process in the queue 
            } 
        } 
    } 
    printf("\nProcess No.\tProcess Size\tBlock no.\n"); 
    for (int i = 0; i < n; i++) 
    { 
        printf(" %i\t\t\t", i+1); 
        printf("%i\t\t\t\t", processSize[i]); 
        if (allocation[i] != -1) 
            printf("%i", allocation[i] + 1); 
        else
            printf("Not Allocated"); 
        printf("\n"); 
    } 
} 


void bestFit(int blockSize[], int m, int processSize[], int n) 
{ 
    int i, j; 
    // Stores block id of the 
    // block allocated to a process 
    int allocation[n]; 
  
    // Initially no block is assigned to any process 
    for(i = 0; i < n; i++) 
    { 
        allocation[i] = -1; 
    } 
    
    // pick each process and find suitable blocks 
    // according to its size ad assign to it 
    for (i = 0; i < n; i++)        //here, n -> number of processes 
    { 
    	int bestID = -1;
        for (j = 0; j < m; j++)        //here, m -> number of blocks 
        { 
            if (blockSize[j] >= processSize[i]) 
            { 
            	if (bestID == -1)
            		bestID = j;
            	else if (blockSize[bestID] > blockSize[j])
            		bestID = j;
            } 
        } 
        if (bestID != -1){
        	allocation[i] = bestID;
        	
        	blockSize[bestID] -= processSize[i];
        }
        
    } 
    printf("\nProcess No.\tProcess Size\tBlock no.\n"); 
    for (int i = 0; i < n; i++) 
    { 
        printf(" %i\t\t\t", i+1); 
        printf("%i\t\t\t\t", processSize[i]); 
        if (allocation[i] != -1) 
            printf("%i", allocation[i] + 1); 
        else
            printf("Not Allocated"); 
        printf("\n"); 
    } 
} 

int main(){
	int choice,a;
	int blockSize[5];
	int processSize[4];
	printf("Enter array of blocksize: ");
	for(int i=0;i<5;i++){
		scanf("%d",&blockSize[i]);
	}
	printf("Enter array of processsize: ");
	for(int i=0;i<4;i++){
		scanf("%d",&processSize[i]);
	}
	int m = sizeof(blockSize) / sizeof(blockSize[0]);  
    	int n = sizeof(processSize) / sizeof(processSize[0]);
    	
	do{
		printf("1. Best Fit\n");
		printf("2. Worst Fit\n");
		printf("Enter a choice: ");
		scanf("%d",&choice);
		switch(choice){
			case 1: firstFit(blockSize, m, processSize,n);
				break;
			case 2:  bestFit(blockSize, m, processSize, n);
				break;
			default: printf("Enter valid choice!!");
		} 
		printf("Do you want to continue? 0 -> no , 1 -> yes");
		scanf("%d",&a);
	}while(a == 1);
}

