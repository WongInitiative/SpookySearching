#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#include "multitest.h"

int * numArray;

void RNG(int soa){
  int i;
  ///Populating the numArray

  for (i = 0; i < soa; i++){
    numArray[i] = i;
    printf("%d \n", numArray[i]);
  }

  i = 0;
  while (i < (0.75 * soa)){ 
	int index1 = rand() % soa;
    int index2= rand() % soa;
    //swap
    int temp = numArray[index1];
    numArray[index1] = numArray[index2];
    numArray[index2] = temp;

    i++;
  }

}


int main(int argc, char* argv[]){

  int soa = 500;

  numArray = malloc(sizeof(int) * soa);
  RNG(soa);
  int i;

  for (i= 0; i < soa; i++){
    printf("%d \n", numArray[i]);
  }

  dummySearch(numArray, 60, soa); 

  return 0;
}

//Workload 1

void Workload 1 (){


}


//Workload 2 

void Workload 2(){


}


//Workload 3

void Workload 3(){



}


//Workload 4

void Worklaod 4(){

}


//Workload 5
void Workload 5() {


}
