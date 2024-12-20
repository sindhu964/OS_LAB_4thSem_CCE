#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define MAX 4
typedef struct
{
    int arrival_time;
    int burst_time;
    int remaining_time;
    int pid;
    int priority;
    bool completed;
} proc;


int Q[100];
int r=-1;
int f=-1;

int dequeue(){
    int ret;
    ret=-1;
    if(f!=r){
        f++;
        ret = Q[f];
    }
    return ret;
}

void enqueue(int e){
    if(r<100){
        r++;
        Q[r]= e;
    }
}

//calculate for each
int waiting_time[MAX+1];
int turnaround_time[MAX+1];
proc process[MAX];

void main(){
    int time=0;
    int i,j;
	int tot_comp=0;
    int quantum =3;
    int min=-1;
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
        for (j = 0; j <MAX; j++) {
            if (process[j].arrival_time <= time && !process[j].completed) {
                enqueue(j);
                process[j].completed=true; // once process is enqueued in this turn I don't wanna include it in the next turn so I'm gonna temporarily mark it as completed so it is omitted in the immediate next pass
            }
        }
        //once process has executed one time quantum we can again make the temporary completed to false
        if(min>-1)
            process[min].completed=false;
        min = dequeue();
        if (min > -1) {
            printf("Process pid:%d is executing at time:%d\n", process[min].pid, time);
            int sub_time = (process[min].remaining_time>quantum)?quantum:process[min].remaining_time;
            process[min].remaining_time -=sub_time;
            time+=sub_time;
            if (process[min].remaining_time == 0) {
                waiting_time[min] = time - process[min].arrival_time - process[min].burst_time;
                turnaround_time[min] = time - process[min].arrival_time;
                process[min].completed = true;
                min=-1; // ensuring completed process doesn't get get marked as incomplete again
                tot_comp++;
            }
        } else {
            time++;
        }
	}	
	printf("Process\tWaiting Time\tTurnaround Time\n");
	for (i = 0; i < MAX; i++) {
		printf("%d\t%d\t\t%d\n", process[i].pid, waiting_time[i], turnaround_time[i]);
	}
}