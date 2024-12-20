#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(void){
	pid_t pid1 = fork();
	if(pid1<0){
		printf("Fork failed!\n");
		return 1;
	}
	else if(pid1==0){
		printf("Child process executing.... (PID: %d , PPID: %d)\n", getpid(),getppid());
	}
	else{
		printf("Parent process executing... (PID: %d , PPID: %d)\n", getpid(),getppid());
	}
}

