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
	#define dummySearch(x, y, z) splitSearch((x), (y), (z))
	void* threadSearch(void*);

	int* numArray;

#endif
