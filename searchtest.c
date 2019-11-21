#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "multitest.h"

int * numArray;

void RNG(int* data, int soa);
void workload1(int size, int target);

int main(int argc, char* argv[]){
//	workload1(500, 60);
//	workload1(500, 10);
//	workload1(500, 0);
	workload1(500, 500);
	//int i;
	//for (i= 0; i < 500; i++){
    //	printf("%d \n", numArray[i]);
	//}
	return 0;
}

//populates random number array
void RNG(int* data, int soa){
  int i;
  ///Populating the numArray

  for (i = 0; i < soa; i++){
    data[i] = i;
    printf("%d \n", data[i]);
  }

  i = 0;
  while (i < (0.75 * soa)){ 
	int index1 = rand() % soa;
    int index2= rand() % soa;
    //swap
    int temp = data[index1];
    data[index1] = data[index2];
    data[index2] = temp;

    i++;
  }

}

//takes the size of the list to be generated, and the target value, creates the list, then searches for the target value using splitSearch
void workload1(int size, int target){
	int* data = (int*) malloc(sizeof(int)*size);
	RNG(data, size);
	numArray = data;
	dummySearch(numArray, target, size);
}
