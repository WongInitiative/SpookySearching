#include "multitest.h"

int target;
int wasFound = -1;


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



void splitSearch(int *data, int t, int soa){
  // finding target and finding the size of my array ~ Worked
  // int soa = atoi(argv[1]); **DON"T NEED THE PRECEDING CODE

  printf("%d\n", soa);

 // numArray = (int *) malloc(sizeof(int) * soa);

/* DON"T NEED THE BELOW CODE
  printf("Enter the search value:\n");
  scanf("%d", &target);
*/

  target = t;
  ///Populating the array ~ NEED TO ADD RANDOMIZE PART
  int i;
 // for (i = 0; i < soa; i++){
 //   numArray[i] = i + 1;
 // }

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

return;
}
