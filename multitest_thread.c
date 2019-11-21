#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h> //Do I need this?
#include <sys/wait.h> //Do I need this?
#include <pthread.h>
void* threadSearch(void*);


typedef struct bounds {
  int start;
  int end;
} bounds;

int target;
int wasFound = -1;
int* numArray;


void* threadSearch(void* args){
  bounds * boundPtr = (bounds *) args;
  printf("%d %d\n", boundPtr->start, boundPtr->end);
  int start = boundPtr-> start;
  int end = boundPtr -> end;
  while (start <= end){
      if (numArray[start] == target){
        wasFound = start;
        pthread_exit(0);
      }
      start++;
  }

  pthread_exit(0);
}



int main(int argc, char* argv[]){
  // finding target and finding the size of my array ~ Worked
  int soa = atoi(argv[1]);
  printf("%d\n", soa);

  numArray = (int *) malloc(sizeof(int) * soa);

  printf("Enter the search value:\n");
  scanf("%d", &target);

  ///Populating the array ~ Worked
  int i;
  for (i = 0; i < soa; i++){
    numArray[i] = i + 1;
  }

  ///Creating threads need to execute my fxn ~ Worked
  int threadsReq = soa % 250 == 0? soa/250: soa/250 + 1;
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
    if (leftover < 249){
      start = 0;
      searchBound[i].start = start;
      searchBound[i].end = end;
      break;
    }

    ///Changing bounds
    start = start - 249;
    searchBound[i].start = start;
    searchBound[i].end = end;
    leftover = leftover - 250;
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
    pthread_join (tids[i], NULL);
  }

if (wasFound >=0) printf("target was found at position %d", wasFound);
else printf("target was not found");

return 0;
}
