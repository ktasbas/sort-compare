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

/*	Purpose: Return an array of randomly generated integers
	Dependencies: stdlib.h and time.h */
int * randomArr(int size);

/*	Purpose: Sort array in increasing order using insertion sort method
	Dependencies: none */
void insertionSort(int * sample, int size);

/*	Purpose: Return index of parent node in heap tree
	Dependencies: none */
int parent(int nodePos);

/*	Purpose: Return index of left child in heap tree
	Dependencies: none */
int left(int nodePos);

/*	Purpose: Return index of right child in heap tree
Dependencies: none */
int right(int nodePos);

int main() {
	int * sample;
	int sampleSize = 1000;

	unsigned long
		startTime	= 0,
		endTime		= 0;
		
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

/*	Purpose: Return an array of randomly generated integers
	Dependencies: stdlib.h and time.h */
int * randomArr(int size) {
	int * arr = new int[size];

	srand((unsigned)time(NULL));

	for (int i = 0; i < size; i++)
		arr[i] = rand();

	return arr;
}

// INSERTION SORT

/*	Purpose: Sort array in increasing order using insertion sort method
	Dependencies: none */
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

// HEAP SORT
/*	Purpose: Return index of parent node in heap tree
	Dependencies: none */
int parent(int nodePos) {
	return (nodePos / 2);
}

/*	Purpose: Return index of left child in heap tree
	Dependencies: none */
int left(int nodePos) {
	return (2 * nodePos);
}
/*	Purpose: Return index of right child in heap tree
	Dependencies: none */
int right(int nodePos) {
	return (2 * nodePos + 1);
}

/*	Purpose: place int at currentPos into the correct position in the heap
	Dependencies: std::swap */
void minHeapify(int *A, int size, int currentPos){
	int smallest = 0;
	int leftPos = left(currentPos);
	int rightPos = right(currentPos);
	if ((leftPos <= size) && (A[leftPos] < A[currentPos]))
		smallest = leftPos;
	else
		smallest = currentPos;

	if ((rightPos <= size) && (A[rightPos] < A[smallest]))
		smallest = rightPos;

	if (smallest != currentPos) {
		std::swap(A[currentPos], A[smallest]);
		minHeapify(A, size, smallest);
	}
}

void buildMaxHeap(int *A, int size) {
	for (int i = size / 2; i > 0; i--)
		minHeapify(A, size, i);
}

void heapSort(int *A) {

}


// QUICK SORT