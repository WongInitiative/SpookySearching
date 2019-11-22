#include "multitest.h"


void splitSearch(int* data, int target, int length, int groupSize){
	printf("Below test is searching with processes: \n);	

	if(groupSize > 250){
		printf("Error: groupSize must be <= 250");
		return;
	}
	int ProcCount = ceil(((double)length)/((double)groupSize)); //number of processes we need
	int Remain = length%groupSize; //remainder: used in last process to count remaining indexes if the number of elements in the array does not divide evenly by groupSize
	pid_t pids[ProcCount];
	int result;
  	int i;
  	for (i = 0; i < ProcCount; i++){	
		pids[i] = fork();
		if(pids[i] == 0){ //Is the child, assign array processing
			printf("Process %d is being created...\n", getpid());
			if(Remain == 0){ //Remainder is 0 so all processes will look through groupSize elements each
				result = genericSearch(data, (i*groupSize), ((i+1)*groupSize), target);
			}else if(i < (ProcCount-1)){ //Remainder is not 0, this means every process except the last one will look through groupSize elements 
				result = genericSearch(data, (i*groupSize), ((i+1)*groupSize), target);
			}else{ //This tells the last process (in the case that the remainder is not 0), to count the remaining elements (<groupSize) as to not overstep
				result = genericSearch(data, (i*groupSize), ((i*groupSize)+Remain), target);
			}

			if(result == -1){
				exit(255); //exit on success should never be more than 249, so this represents exit on failure to find the index
			}else{
				exit(result-(i*groupSize)); //exit with the relative index found by process
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
			if(exit_status != 255){
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
	return -1;
}
