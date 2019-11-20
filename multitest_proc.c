#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void procSearch(int* data, int target, int length);
int genericSearch(int* data, int start, int end, int target);

int main(int argc, char** argv){
	int i;
	int RandList[550];
	for(i = 0; i < 550; i++){
		RandList[i] = i+1;
	}
	procSearch(RandList, 350, 550);
	return 0;
}
//TODO
//clean up pids array since there isn't much of a use for them
void procSearch(int* data, int target, int length){
	int ProcCount = ceil(((double)length)/((double)250)); //number of processes we need
	int Remain = length%250; //remainder: used in last process to count remaining indexes if the number of elements in the array does not divide evenly by 250
	pid_t pids[ProcCount];
	int result;
  	int i;
  	for (i = 0; i < ProcCount; i++){	
		pids[i] = fork();
		if(pids[i] == 0){ //Is the child, assign array processing
			printf("Process %d is being created...\n", getpid());
			if(Remain == 0){ //Remainder is 0 so all processes will look through 250 elements each
				result = genericSearch(data, (i*250), ((i+1)*250), target);
			}else if(i < (ProcCount-1)){ //Remainder is not 0, this means every process except the last one will look through 250 elements 
				result = genericSearch(data, (i*250), ((i+1)*250), target);
			}else{ //This tells the last process (in the case that the remainder is not 0), to count the remaining elements (<250) as to not overstep
				result = genericSearch(data, (i*250), ((i*250)+Remain), target);
			}

			if(result == 0){
				exit(0);
			}else{
				exit(result-(i*250)); //exit here
			}
		}
	}
  
	int status, exit_status;
	pid_t deadpid;
	while(ProcCount > 0){
		deadpid = wait(&status);
		//printf("A process %d died", i);
		if(WIFEXITED(status)){
			exit_status = WEXITSTATUS(status);
			if(exit_status != 0){
				printf("Process with PID: %zu has found the target at relative index: %d\n", deadpid, exit_status); //add print shit here
			}else{
				printf("Process with PID: %zu did not find the target \n", deadpid);
			}
		}
		--ProcCount;
	}
	return;
}

int genericSearch(int* data, int start, int end, int target){
	int i;
	for(i = start; i < end; i++){
		if (data[i] == target){
			return i;
		}
	}
	return 0;
}
