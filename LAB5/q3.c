#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main(void){
	char str[25][25];
	char temp[25];
	int n;
	printf("Enter the number of strings: ");
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%s",str[i]);
	}
	pid_t pid1;
	pid1 = fork();
	if(pid1<0){
		printf("Fork Failed!!..");
		return 1;
	}	
	else if(pid1==0){
		printf("\nChild 1  Executing!!..\n");

		//PERFORMING BUBBLE SORT
		for(int i=0;i<n;i++){
			for(int j=i+1;j<n;j++){
				if(strcmp(str[i],str[j])>0){
					strcpy(temp,str[i]);
					strcpy(str[i],str[j]);
					strcpy(str[j],temp);
				}
			}
		}

		//DISPLAYING SORTED STRINGS
		for(int i=0;i<n;i++){
			printf("%s\n",str[i]);
		}
		exit(0);
	}
	else{
		pid_t pid2;
		pid2 = fork();
		if(pid2==0){
			printf("\nChild 2 Executing!!...\n");

			//PERFORMING SELECTION SORT
			for(int i=0;i<n-1;i++){
				int min = i;
				for(int j=i+1;j<n;j++){
					if(strcmp(str[j],str[min])<0){
						min = j;
					}
				}
				if(min != i){
					strcpy(temp,str[i]);
					strcpy(str[i],str[min]);
					strcpy(str[min],temp);
				}
			}

			//DISPLAYING THE SORTED STRINGS
			for(int i=0;i<n;i++){
				printf("%s\n",str[i]);
			}
			exit(0);
		}
		else if(pid2>0){
			sleep(5);
			printf("Parent Process Executing!!...");
		}
	}
}
