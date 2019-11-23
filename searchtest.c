#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>

#include "multitest.h"

int* RNG(int soa);
double min(double* times, int length);
void workloadGeneric(int* arrayName, int size, int target, int groupSize, int numOfTrials);
double max (double * trialTimes, int numberOfTrials);
double SD (double* trialTimes, int numberOfTrials);
double average (double* trialTimes, int numberOfTrials); 
void workload1();
void workload2();
void workload3();

int main(int argc, char* argv[]){
	workload1();
	workload2();
	workload3();
	return 0;
}

//populates random number array
int* RNG(int soa){
//	srand(1);						//NOTE: GET RID OF THIS IF YOU WANT EVERY CALL TO A WORKLOAD TO CREATE A DIFFERENT ARRAY SEQUENCE
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



//minimum
double min(double* times, int length){
	int i, lowest;
	for(i = 0; i < length; i++){
		if(i == 0){
			lowest = times[i];
		}else if(times[i] < lowest){
			lowest = times[i];
		}
	}
	return lowest;
}




void workloadGeneric(int* arrayName, int size, int target, int groupSize, int numOfTrials){
	printf("Running test with parameters:\n List Size: %d\n Target: %d\n Group Size per Thread/Proc: %d\n Number of Trials: %d\n\n", size, target, groupSize, numOfTrials);
	double timeArray[numOfTrials];
	struct timeval start, end;	


	int a;
	for (a = 0; a < numOfTrials; a++){ //Running numOfTrials times
		printf("Trial number %d is being run\n", (a+1));
		gettimeofday(&start, NULL);
		
		int oldIndex = dummySearch(arrayName, target, size, groupSize);

		gettimeofday(&end, NULL);
		timeArray[a] = (double) ((end.tv_sec*1e6 + end.tv_usec) - (start.tv_sec*1e6 + start.tv_usec));
		//timeArray[a] = (double) (end.tv_usec - start.tv_usec);
		printf("Time to complete Trial %d of this test was %lf microseconds\n", (a+1), timeArray[a]);
		
		if(oldIndex == -1){
			printf("target not found\n\n");
		}else{	
			printf("target was found at index: %d\n\n", oldIndex);
			int newIndex = rand() % size ;

			while (newIndex == oldIndex){
				newIndex= rand() % size; 
			}

			int temp = arrayName[oldIndex];
			arrayName[oldIndex] = arrayName[newIndex];
			arrayName[newIndex] = temp;
		}
	}

	//find average, max, min, and standard deviation
	
	double minTime = min(timeArray, numOfTrials);
	double averageTime = average (timeArray, numOfTrials);
	double maxTime = max(timeArray, numOfTrials);
	double standDev = SD(timeArray, numOfTrials);

	printf("Across all %d trials, the Min time is: %lf; the Average time is: %lf; the Max time is: %lf; the standard deviation is: %lf\n\n\n", numOfTrials, minTime, averageTime, maxTime, standDev);

	return;		
}


//Maximum time 
double max(double* trialTimes, int numberOfTrials){

	double maxVal = 0.0;
	int a;
	for (a = 0; a < numberOfTrials; a++){
		if(trialTimes[a] > maxVal) maxVal = trialTimes[a];
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

//The purpose of this function is to compare the runtime of splitsearch for processes and threads when only the size of the LIST is changed
void workload1(){
	int* data = RNG(500);
	printf("Running workload1()\n");
	workloadGeneric(data, 500, 10, 250, 100);
	free(data);
	data = RNG(1000);
	printf("Running workload1()\n");
	workloadGeneric(data, 1000, 10, 250, 100);
	free(data);
	data = RNG(10000);
	printf("Running workload1()\n");
	workloadGeneric(data, 10000, 10, 250, 100);
	free(data);
	data = RNG(20000);
	printf("Running workload1()\n");
	workloadGeneric(data, 20000, 10, 250, 100);
	free(data);
	data = RNG(25000);
	printf("Running workload1()\n");
	workloadGeneric(data, 25000, 10, 250, 100);
	free(data);
	
	return;
}

//The purpose of this function is to compare the runtime of splitsearch for processes and threads when only the size of the GROUP is changed
void workload2(){
	int* data = RNG(500);
	printf("Running workload2()\n");
	workloadGeneric(data, 500, 10, 250, 100);
	free(data);
	data = RNG(500);
	printf("Running workload2()\n");
	workloadGeneric(data, 500, 10, 200, 100);
	free(data);
	data = RNG(500);
	printf("Running workload2()\n");
	workloadGeneric(data, 500, 10, 150, 100);
	free(data);
	data = RNG(500);
	printf("Running workload2()\n");
	workloadGeneric(data, 500, 10, 100, 100);
	free(data);
	data = RNG(500);
	printf("Running workload2()\n");
	workloadGeneric(data, 500, 10, 50, 100);
	free(data);

	return;

}

//The purpose of this function is to figure out how many threads it takes for the time of of splitsearch to match  the time of splitsearch being run by a single process,
void workload3(){
//testing time for 1 process on a list of 250 vs. time for variable number of threads on 250
	int* data = RNG(250);
	printf("Running workload3()\n");
	workloadGeneric(data, 250, 10, 250, 100);
	free(data);
	data = RNG(250);
	printf("Running workload3()\n");
	workloadGeneric(data, 250, 10, 125, 100);
	free(data);
	data = RNG(250);
	printf("Running workload3()\n");
	workloadGeneric(data, 250, 10, 50, 100);
	free(data);
	data = RNG(250);
	printf("Running workload3()\n");
	workloadGeneric(data, 250, 10, 20, 100);
	free(data);
	data = RNG(250);
	printf("Running workload3()\n");
	workloadGeneric(data, 250, 10, 5, 100);
	free(data);
	data = RNG(250);
	printf("Running workload3()\n");
	workloadGeneric(data, 250, 10, 3, 100);
	free(data);
	
	return;
}

