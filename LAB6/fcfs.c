#include<stdio.h>

struct pcb{
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
};

void pline(int x);


void main(){
    int i,j,num;
    float avg_wait = 0.0,avg_turnaround = 0.0, time = 0.0, wait_total = 0.0, turnaround_total = 0.0;
    struct pcb p[10],temp;
    printf("Enter the total number of processes:");
    scanf("%d",&num);
    for(i=0;i<num;i++){
        printf("Enter the pid,arrival_time and burst_time:");
        scanf("%d %d %d",&p[i].pid,&p[i].arrival_time,&p[i].burst_time);
    }
    for(i=0;i<num-1;i++){
        for(j=0;j<num-i-1;j++){
            if(p[j].arrival_time>p[j+1].arrival_time){
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    for(i=0;i<num;i++){
        time = time + p[i].burst_time;
        p[i].waiting_time = time - p[i].arrival_time - p[i].burst_time;
        p[i].turnaround_time = time - p[i].arrival_time;
    }
    
    //time=0;
    pline(44);
    printf("PID\tArrival Time\tBurst Time\tWaiting time\tTurnaround time\n");
    pline(44);
    for(i=0;i<num;i++){
        printf("%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].waiting_time,p[i].turnaround_time);
        turnaround_total += p[i].turnaround_time;
        wait_total += p[i].waiting_time;
    }
    pline(44);
    avg_turnaround = turnaround_total/(float)num;
    avg_wait = wait_total/(float)num;
    printf("Total turn around time : %f. ",turnaround_total);
    printf("\nAverage turn around time : %.3f. ",avg_turnaround);
    printf("\nTotal waiting time : %f. ",wait_total);
    printf("\nAverage waiting time : %.3f. ",avg_wait);
}

void pline(int x)
{
    int i;
    for(i=0;i<x;i++){
        printf("-");
    }
    printf("\n");
}