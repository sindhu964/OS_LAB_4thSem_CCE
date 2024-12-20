#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
int main(int argc, char *argv[]){
	char temp[10];
	char str[25][25];
	printf("Enter the strings: \n");
	for(int i=0;i<5;i++){
		scanf("%s",argv[i]);
		//strcpy(str[i],argv[i]);
	}
	for(int i=0;i<5;i++){
		for(int j=i+1;j<5;j++){
			if(strcmp(argv[i],argv[j])>0){
				strcpy(temp,argv[i]); // temp = argv[i];
				strcpy(argv[i],argv[j]);   //argv[i] = argv[j];
				strcpy(argv[j],temp);  // argv[j] = temp;
			}
		}
	}
	printf("\n");
	for(int i=0;i<5;i++){
		printf("%s ",argv[i]);
	}
}
