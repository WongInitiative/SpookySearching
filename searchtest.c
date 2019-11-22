#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>

#include "multitest.h"

int* RNG(int soa);
void workload1(int* data, int size, int target, int groupSize);
double min(double* times, int length);
void workload2(int* arrayName, int size, int target, int groupSize);
double max (double * trialTimes, int numberOfTrials);
double SD (double* trialTimes, int numberOfTrials);
double average (double* trialTimes, int numberOfTrials); 

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
void workload2(int* arrayName, int size, int target, int groupSize, int numberOfTrials){
	
	double timeArray[numOfTrials];
	
	int a
	for (a = 0; a < numOfTrials; a++){ //Running 20 trials
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
	double averageTime = average (timeArray, numOfTrials);
	double maxTime = max(timeArray, numOfTrials);
	double standDev = SD(timeArray, numOfTrials);

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




