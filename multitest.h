#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#ifndef _MULTITEST_H
#define _MULTITEST_H
	#define dummySearch(w, x, y, z) splitSearch((w), (x), (y), (z))
	typedef struct bounds{
 		int start;
		int end;
	}bounds;

	int* numArray;
	void* threadSearch(void*);
	void splitSearch(int* data, int target, int length, int groupSize);
	int genericSearch(int* data, int start, int end, int target);

#endif
