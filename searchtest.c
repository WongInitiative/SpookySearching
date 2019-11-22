#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#include "multitest.h"

int* RNG(int soa);
void workload1(int* data, int size, int target, int groupSize);
double min(double* times, int length);

int main(int argc, char* argv[]){
//	workload1(500, 60, 150);
//	workload1(500, 10, 150);
//	workload1(500, 0, 150);
//	workload1(500, 500, 150);

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
int* RNG(int soa){
	srand(1);						//NOTE: GET RID OF THIS IF YOU WANT EVERY CALL TO A WORKLOAD TO CREATE A DIFFERENT ARRAY SEQUENCE
	int* data = (int*) malloc(sizeof(int)*soa);
	int i;	
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

  return data;
}

void workload1(int* data, int size, int target, int groupSize){
	int i = 0;
	for(i = 0; i < 100; i++){
		int index = dummySearch(data, target, size, groupSize);
		//swap
		if(index != -1){
			int temp = data[index];
			int randIndex = rand() % size;
			data[index] = data[randIndex];
			data[randIndex] = temp;
		}
	}
	return;
}

//minimum
double min(double* times, int length){
	int i, lowest;
	for(i = 0; i < length; i++){
		if(i == 0){
			lowest = times[i]
		}else if(times[i] < lowest){
			lowest = times[i];
		}
	}
	return lowest;
}




//let list size be constant and change groupSize
void workload2(int size, int target, int groupSize){
	


}



