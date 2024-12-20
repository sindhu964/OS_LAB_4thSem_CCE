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
    int priority;
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
		int max_priority = INT_MAX;
        int max = -1;

        for (j = MAX-1; j >=0; j--) {
            if (process[j].arrival_time <= time && !process[j].completed && process[j].burst_time < min_burst) {
                max = j;
                max_priority = process[j].burst_time;
            }
        }

        if (max > -1) {
			printf("Process pid:%d is executing at time:%d\n",process[max].pid,time);
            process[max].remaining_time--;
            if(process[max].remaining_time==0){
                //time = time + process[max].burst_time;
                waiting_time[max] = (time+1) - process[max].arrival_time - process[max].burst_time;
                turnaround_time[max] = (time+1) - process[max].arrival_time;
                process[max].completed = true;
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

