#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
int main(){
	char str[25][25];
	char temp[25];
	int n;
	printf("Enter the number of strings:");
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%s",str[i]);
	}
	pid_t pid ;
	pid = fork();
	if(pid<0){
		printf("Fork failed!!");
		return 1;
	}
	else if(pid==0){
		printf("\nChild Process Executing!!..\n");
		for(int i=0;i<n;i++){
			for(int j=i+1;j<n;j++){
				if(strcmp(str[i],str[j])>0){
					strcpy(temp,str[i]);
					strcpy(str[i],str[j]);
					strcpy(str[j],temp);
				}
			}
		}
	}
	else{
		sleep(5);
		printf("\nParent Process Executing!!..\n");
	}
	printf("\nThe sorted of strings are:\n");
	for(int i=0;i<n;i++){
		printf("%s\n",str[i]);
	}
}
