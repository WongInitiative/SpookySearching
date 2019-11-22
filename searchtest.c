#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>

#include "multitest.h"

void RNG(int* data, int soa);
void workload1(int size, int target, int groupSize);
void workload2(int* arrayName, int size, int target, int groupSize);
double max (double * trialTimes, int numberOfTrials);
double SD (double* trialTimes, int numberOfTrials);
double average (double* trialTimes, int numberOfTrials); 

int main(int argc, char* argv[]){
	workload1(500, 60, 250);
	workload1(500, 10, 250);
	workload1(500, 0, 250);
	workload1(500, 500, 250);

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




//let list size be constant and change groupSize
void workload2(int* arrayName, int size, int target, int groupSize){
	
	double timeArray[20];
	
	int a
	for (a = 0; a < 20; a++){ //Running 20 trials
		gettimeofday(&start, NULL);
		
		int oldIndex = dummySearch(data, target, size, groupSize);

		gettimeofday(&end, NULL);
		timeArray[a] = (double) (end.tv_usec - start.tv_usec);
		
		if(oldIndex == -1){
			printf("\ntarget not found;\n");
			return;
		}

		int newIndex = rand() % size ;

		while (newIndex == oldIndex){
			newIndex= rand() % size; 
		}

		int temp = arrayName[oldIndex];
		arrayName[oldIndex] = arrayName[newIndex];
		arrayName[newIndex] = temp;
	}

	//find average, max, min, and standard deviation
	double averageTime = average (timeArray, 20);
	double maxTime = max(timeArray, 20);
	double standDev = SD(timeArray, 20);

	printf("the Average time is: %lf; the Max time is: %lf; the standard deviation is: %lf\n", averageTime, maxTime, standDev);

	return;		
}


//Maximum time 
double max(double* trialTimes, int numberOfTrials){

	double maxVal = 0.0;
	int a;
	for (a = 0; a < numberOfTrials; a++){
		if(trialTimes[a] > maxVal) maxVal = trialTimes[a]
	}

	return maxVal;
}


//Standard Deviation
double SD (double* trialTimes, int numberOfTrials){
	double sum = 0.0, mean, SD = 0.0;
	int a; 
	for (a = 0; a<numberOfTrials; ++a){
		sum += trialTimes[a];
	}
	mean = sum/numberOfTrials;

	for (a=0; a<numberOfTrials; ++a){
		SD += pow(trialTimes[a] - mean, 2);
	}

	return sqrt(SD/numberOfTrials);

}

double average (double* trialTimes, int numberOfTrials){
	double totalTime = 0;
	int a;
	for (a = 0; a < numberOfTrials; a++){
		totalTime += trialTimes[a];
	}

	double averageTime = totalTime / numberOfTrials;

	return averageTime;
}




