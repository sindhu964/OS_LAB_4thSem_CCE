#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#define MAX 5

typedef struct{
	int arrival_time;
	int burst_time;
	int remaining_time;
	int pid;
	int priority;
	bool completed;
}proc;

typedef struct{
	proc key;
}element;

element q[MAX];
int r=-1;
int f=-1;

element dequeue(){
	element ret;
	ret.key.pid = -1;
	if(f!=r){
		f++;
		ret = q[f];
	}
	return ret;
}

void enqueue(element e){
	if(r<MAX){
		r++;
		q[r]=e;
	}
}

int waiting_time[6];
int turnaround_time[6];
proc process[5];

void pre_sjf(){
	int time=0;
	int i,j;
	int tot_comp=0;
	for(i=0;i<5;i++){
		printf("Enter the process id ,arrival time and burst time\n");
		scanf("%d",&process[i].pid);
		scanf("%d",&process[i].arrival_time);
		scanf("%d",&process[i].burst_time);
		process[i].remaining_time = process[i].burst_time;
		process[i].completed = false;
	}
	while(tot_comp<5){
		int min_burst = INT_MAX;
		int min=-1;
		
		for(j=4;j>=0;j--){
			if(process[j].arrival_time <= time && !process[j].completed && process[j].burst_time<min_burst){
				min=j;
				min_burst = process[j].burst_time;
			}
		}
		if(min>-1){
			printf("Process pid : %d is executing at time : %d \n",process[min].pid,time);
			process[min].remaining_time--;
			if(process[min].remaining_time==0){
				waiting_time[min] = time-process[min].arrival_time-process[min].burst_time;
				turnaround_time[min] = time-process[min].arrival_time;
				process[min].completed=true;
				tot_comp++;
			}
		}
		time++;
	}
	printf("Process \t Waiting time \t Turn around time \n");
	for(i=0;i<5;i++){
		printf("%d \t %d \t %d \n",process[i].pid,waiting_time[i],turnaround_time[i]);
	}
}

void rr(){
	int time=0;
	int i,j;
	int tot_comp = 0;
	int quantum = 3;
	for(i=0;i<5;i++){
		printf("Enter the process id, arrival time and burst time\n");
		scanf("%d",&process[i].pid);
		scanf("%d",&process[i].arrival_time);
		scanf("%d",&process[i].burst_time);
		process[i].remaining_time = process[i].burst_time;
		process[i].completed = false;
	}
	while(tot_comp<5){
		element e;
		for(j=0;j<5;j++){
			 if(process[j].arrival_time<=time && !process[j].completed){
			 	e.key = process[j];
			 	enqueue(e);
			 	process[j].completed = true;
			 }
		}
		proc p = dequeue().key;
		p.completed = false;
		if(p.pid>-1){
			printf("Process pidn: %d is executing at time %d \n",p.pid,time);
			int sub_time = (p.remaining_time>quantum)?quantum:p.remaining_time;
			p.remaining_time -= sub_time;
			time += sub_time;
			if(p.remaining_time==0){
				waiting_time[p.pid] = time-p.arrival_time-p.burst_time;
				turnaround_time[p.pid] = time-p.arrival_time;
				process[p.pid].completed=true;
				tot_comp++;
			}
			else{
				e.key = p;
				enqueue(e);
			}
		}
		else{
			time++;
		}
	}
	printf("Process \t Waiting time \t Turn around time \n");
	for(i=0;i<5;i++){
		printf("%d \t %d \t %d \n",process[i].pid,waiting_time[i],turnaround_time[i]);
	}
}

void nonpre_pr(){
	int time=0;
	int i,j;
	int tot_comp = 0;
	for(i=0;i<5;i++){
		printf("Enter the process id, arrival time and burst time and priority\n");
		scanf("%d",&process[i].pid);
		scanf("%d",&process[i].arrival_time);
		scanf("%d",&process[i].burst_time);
		scanf("%d",&process[i].priority);
		process[i].completed = false;
	}
	while(tot_comp<5){
		int max_priority=INT_MAX;
		int max = -1;
		for(j=4;j>=0;j--){
			if(process[j].arrival_time<=time && !process[j].completed && process[j].priority<max_priority){
			max=j;
			max_priority = process[j].priority;
			}
		}
		if(max>-1){
			printf("Process pid : %d is executing at time : %d \n",process[max].pid,time);
				time += process[max].burst_time;
					waiting_time[max] = time-process[max].arrival_time-process[max].burst_time;
					turnaround_time[max] = time-process[max].arrival_time;
					process[max].completed=true;
					tot_comp++;
		}
		else{
			time++;
		}
	}
	printf("Process \t Waiting time \t Turn around time \n");
	for(i=0;i<5;i++){
		printf("%d \t %d \t %d \n",process[i].pid,waiting_time[i],turnaround_time[i]);
		}
}

int main(){
	int choice;
	while(true){
		printf("Would you like to perform \n");
		printf("0.Exit\n");
		printf("1.Preemptive SJF\n");
		printf("2.RR\n");
		printf("3.Non Preemptive Priority Scheduling\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				pre_sjf();
				break;
			case 2:
				rr();
				break;
			case 3:
				nonpre_pr();
				break;
			case 0:
				printf("Exiting..\n");
				exit(0);
				break;
			default: 
				printf("Invalid option\n");
		}
	}
}
