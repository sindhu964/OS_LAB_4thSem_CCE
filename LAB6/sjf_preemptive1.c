#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define MAX 5
typedef struct
{
    int arrival_time;
    int burst_time;
    int remaining_time;
    int pid;
    //int priority;
    bool completed;
} proc;

int main(){
    int waiting_time[MAX+1];
    int turnaround_time[MAX+1];
    proc process[MAX];
    int time=0;
    int i,j;
	int tot_comp=0;

    for (i = 0; i < MAX; i++)
    {
        printf("Enter the process id, arrival time and  burst time\n");
        scanf("%d", &process[i].pid);
        scanf("%d", &process[i].arrival_time);
        scanf("%d", &process[i].burst_time);
        process[i].remaining_time=process[i].burst_time;
        process[i].completed = false;
    }

    while(tot_comp<MAX){
		int min_burst = INT_MAX;
        int min = -1;

        for (j = MAX-1; j >=0; j--) {
            if (process[j].arrival_time <= time && !process[j].completed && process[j].burst_time < min_burst) {
                min = j;
                min_burst = process[j].burst_time;
            }
        }

        if (min > -1) {
			printf("Process pid:%d is executing at time:%d\n",process[min].pid,time);
            process[min].remaining_time--;
            if(process[min].remaining_time==0){
                //time = time + process[min].burst_time;
                waiting_time[min] = (time+1) - process[min].arrival_time - process[min].burst_time;
                turnaround_time[min] = (time+1) - process[min].arrival_time;
                process[min].completed = true;
                tot_comp++;
            }
        }
        time++;
	}	
    
	printf("Process\tWaiting Time\tTurnaround Time\n");
	for (i = 0; i < MAX; i++) {
		printf("%d\t%d\t\t%d\n", process[i].pid, waiting_time[i], turnaround_time[i]);
	}
}

