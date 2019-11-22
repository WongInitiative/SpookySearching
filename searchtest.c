#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#include "multitest.h"

void RNG(int* data, int soa);
void workload1(int size, int target, int groupSize);

int main(int argc, char* argv[]){
	workload1(500, 60, 150);
	workload1(500, 10, 150);
	workload1(500, 0, 150);
	workload1(500, 500, 150);

//	workload1(500, 60, 250);
//	workload1(500, 60, 250);
//	workload1(500, 60, 250);
//	workload1(500, 60, 250);

	//int i;
	//for (i= 0; i < 500; i++){
    //	printf("%d \n", numArray[i]);
	//}
	return 0;
}

//populates random number array
void RNG(int* data, int soa){
  srand(1);						//NOTE: GET RID OF THIS IF YOU WANT EVERY CALL TO A WORKLOAD TO CREATE A DIFFERENT ARRAY SEQUENCE
  int i;
  ///Populating the numArray

  for (i = 0; i < soa; i++){
    data[i] = i;
    //printf("%d \n", data[i]);
  }

  i = 0;
  while (i < (0.75 * soa)){ 
	int index1 = rand() % soa;
    int index2= rand() % soa;
	//printf("%d, %d\n", index1, index2);
    //swap
    int temp = data[index1];
    data[index1] = data[index2];
    data[index2] = temp;

    i++;
  }

}

//takes the size of the list to be generated, and the target value, creates the list, then searches for the target value using splitSearch
void workload1(int size, int target, int groupSize){
	int* data = (int*) malloc(sizeof(int)*size);
	RNG(data, size);
	dummySearch(data, target, size, groupSize);
}

////Workload 1
//
//void Workload 1 (){
//
//
//}
//
//
////Workload 2 
//
//void Workload 2(){
//
//
//}
//
//
////Workload 3
//
//void Workload 3(){
//
//
//
//}
//
//
////Workload 4
//
//void Worklaod 4(){
//
//}
//
//
////Workload 5
//void Workload 5() {
//
//
//}
