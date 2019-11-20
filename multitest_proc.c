#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
	int i;
	int RandList[500];
	for(i = 0; i < 500; i++){
		RandList[i] = i+1;
	}


	
	return 0;
}

void procSearch(int* data, int target){
	int ArrLength = sizeof(RandList)/sizeof(integer);
	int GroupCount = ArrLength/250;
	int Remain = ArrLength%250;
	pid_t pids[GroupCount];
	pid_t lastpid;
	int result;
	//TODO
	//Add Exits
	//Add Waits
	//Implement Child Procs
	lastpid = fork();
	if(lastpid == 0){ //Is the child, Act as last group and check remainding
		result = genericSearch(data, (GroupCount*250), ((GroupCount*250)+Remain), target);
		exit(result); //exit here
	}
	//make sure relative index is encoded in the exit status of the WAIT for this child process

	for (int i = 0; i < GroupCount; i++){
		pids[i] = fork();
		if(pids[i] == 0){ //Is the child, assign array processing
			int result = genericSearch(data, (i*250), ((i+1)*250), target);
			exit(result); //exit here
		}
	}
	
	int status, exit_status;
	int deadpid;
	while(GroupCount > 0){
		deadpid = wait(&status);
		if(WIFEXITED(status)){
			exit_status = WEXITSTATUS(status);
			if(exit_status != 0){
				printf("Process with PID: %zu has found the target at relative index: %d", deadpid, exit_status); //add print shit here
			}else{
				printf("Process with PID: %zu did not find the target", deadpid);
			}
		}
		--GroupCount;
	}
	//add waits here
	//
}

//TODO
//change this so it returns the relative index of the target
int genericSearch(int* data, int start, int end, int target){
	int i;
	for(i = start; i < end; i++){
		if (data[i] == target){
			return i;
		}
	}
	return 0;
}
