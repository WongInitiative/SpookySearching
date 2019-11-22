#include "multitest.h"

int target;
//int wasFound = -1;


void* threadSearch(void* args){
  bounds * boundPtr = (bounds *) args;
  printf("%d %d\n", boundPtr->start, boundPtr->end);
  int start = boundPtr-> start;
  int end = boundPtr -> end;
  int* wasFound = (int*) malloc(sizeof(int));
  while (start <= end){
      if (numArray[start] == target){
	    *wasFound = start;
		return (void*) wasFound;
      }
      start++;
  }
  
  *wasFound = -1;
  return (void*) wasFound;
}



void splitSearch(int *data, int t, int soa, int groupSize){

  target = t;
  int i;

  if (groupSize > 250){
	printf("Error Group Size greater than 250\n");   
	return;
  }

  ///Creating threads need to execute my fxn ~ Worked
  int threadsReq = soa % groupSize == 0? soa/groupSize: soa/groupSize + 1;
  printf("\n %d \n", threadsReq);

  pthread_t tids[threadsReq];

  bounds searchBound[threadsReq];
  int lastindex = soa -1; 

  //Populate the bounds
  int leftover = lastindex;
  int start = lastindex;
  int end = lastindex;
  i = 0;

  while (leftover > 0){
    if (leftover < (groupSize - 1)){
      start = 0;
      searchBound[i].start = start;
      searchBound[i].end = end;
      break;
    }

    ///Changing bounds
    start = start - (groupSize - 1);
    searchBound[i].start = start;
    searchBound[i].end = end;
    leftover = leftover - groupSize;
    start = leftover;
    end = leftover;
    i++;
  }

  ///Checking bounds
  i = 0;
  while (i < threadsReq){
    printf("%d %d\n", searchBound[i].start, searchBound[i].end);
    i++;
  }

  for (i = 0; i < threadsReq; i++){
    ///Do I need any attributes?
    pthread_create(&tids[i], NULL, threadSearch, &searchBound[i]);
    printf("Succesfully Created\n");
  }

  for (i = 0; i < threadsReq; i++){
	void* thread_result;
    pthread_join (tids[i], &thread_result);
	int wasFound = *(int*)thread_result;
	if (wasFound >=0){ 
		printf("Thread with id %zu found the target at position %d\n", tids[i], wasFound);
	}else{
		printf("Thread with id %zu did not find the target\n");
	}
	free(thread_result);

  }

return;
}
