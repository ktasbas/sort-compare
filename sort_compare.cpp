//M. Kaan Tasbas | mktasbas@gmail.com
//13 March 2018

/* Info
	This program contains implementations of insertion sort, heap sort, and quick sort 
	and tests the average running time of each algorithm. 
	
	An array of size 20,000 integers is filled with randomly generated integers. This is
	used to test each alg with a starting sample size of 1,000 that is incremented by 1,000
	until we reach 20,000 samples. 10 trials are done with a new array each time. The average
	of these 10 runs are then used.
*/

/* Todo
	Generate random array
	Implement insertion sort
	Implement heap sort
	Implement quick sort
	Calculate averages
	Run tests
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>

#define startSize	1000	// ns, inital sample size
#define delta		1000	// delta, sample increment between runs
#define endSize		20000	// nf, final sample size
#define numOfRuns	20		// number of increments required
#define numOfTrials	10		// m, number of trials to average from

/*	Purpose: 
	Dependencies: stdlib.h and time.h */
int * randomArr(int size);

void insertionSort(int * sample, int size);

int main() {
	int * sample;
	int sampleSize = 1000;

	unsigned long
		startTime = 0,
		endTime = 0;
		
	unsigned long
		insertionTotalTime	= 0,
		heapTotalTime		= 0,
		quickTotalTime		= 0,

		insertionAvgTime	= 0,
		heapAvgTime			= 0,
		quickAvgTime		= 0;

	for (int trial = 0; trial < 10; trial++) {

		sample = randomArr(sampleSize);

		for (int run = 0; run < 20; run++) {
			startTime = static_cast<unsigned long>(time(NULL));
			insertionSort(sample, sampleSize);
			endTime = static_cast<unsigned long>(time(NULL));


			startTime = static_cast<unsigned long>(time(NULL));
			//heap sort
			endTime = static_cast<unsigned long>(time(NULL));

			startTime = static_cast<unsigned long>(time(NULL));
			//quick sort
			endTime = static_cast<unsigned long>(time(NULL));

			sampleSize += 1000;
		}
		
		delete[] sample;

	}

	return 0;
}

/*	Purpose: 
	Dependencies: stdlib.h and time.h */
int * randomArr(int size) {
	int * arr = new int[size];

	srand((unsigned)time(NULL));

	for (int i = 0; i < size; i++)
		arr[i] = rand();

	return arr;
}

void insertionSort(int * sample, int size) {
	for (int i = 0; i < size; i++) {
		int key = sample[i];

		int j = i - 1;
		while (j >= 0 && sample[j] > key) {
			sample[j + 1] = sample[j];
			j--;
		}
		sample[j + 1] = key;
	}
}