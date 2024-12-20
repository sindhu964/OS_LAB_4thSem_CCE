#include<stdio.h>

void bestfit(int blockSize[], int processSize[],int m,int n){
	int allocation[n];
	int i,j;
	for(i=0;i<n;i++){
		allocation[i] = -1;
	}
	int min=1000;
	for(i=0;i<n;i++){
	int min=-1;
	int minimum_size = 1000;
		for(j=0;j<m;j++){
			if(blockSize[j]>processSize[i] && (blockSize[j]-processSize[i])<minimum_size){
				minimum_size = blockSize[j] - processSize[i];
				min = j;
			}
		}
		if(min!=-1){
			allocation[i] = min;
			blockSize[min] -= processSize[i]; 
		}
	}
	for(i=0;i<n;i++){
			printf("process %d is at block %d\n",i,allocation[i]);
	}

}

int main(){
	int m; //number of blocks in the memory 
	int n; //number of processes in the input queue 
	printf("Enter the number of processes: ");
	scanf("%d",&n);
	printf("Enter the number of blocks: ");
	scanf("%d",&m);
	int blockSize[10]   ; //= {100, 500, 200, 300, 600}; 
	int processSize[10]  ; //= {212, 417, 112, 426};
	printf("Enter the array of block sizes: ");
	for(int i=0;i<m;i++){
		scanf("%d",&blockSize[i]);
	}
	printf("Enter the array of process sizes: ");
	for(int i=0;i<n;i++){
		scanf("%d",&processSize[i]);
	}
	bestfit(blockSize, processSize,m, n); 

	return 0 ; 
}
