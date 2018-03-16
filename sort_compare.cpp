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
int parent(int node_pos);

/*	Purpose: Return index of left child in heap tree
	Dependencies: none */
int left(int node_pos);

/*	Purpose: Return index of right child in heap tree
Dependencies: none */
int right(int node_pos);

/*	Purpose: place int at current_pos into the correct position in the heap
	Dependencies: std::swap */
void maxHeapify(int *A, int size, int current_pos);

/*	Purpose: convert array into a max heap
	Dependencies: std::swap */
void buildMaxHeap(int *A, int size);

/*	Purpose: sort array in increasing order
	Dependencies: std::swap */
void heapSort(int *A, int size);


int main() {
	int * sample;
	int sample_size = 30;

	unsigned long
		start_time	= 0,
		end_time		= 0;
		
	unsigned long
		ins_total_time	= 0,
		heap_total_time		= 0,
		quick_total_time		= 0,

		ins_avg_time	= 0,
		heap_avg_time			= 0,
		quick_avg_time		= 0;

	sample = randomArr(sample_size + 1);
	sample[0] = -1;
	heapSort(sample, sample_size);
	for (int i = 0; i <= sample_size; i++)
		std::cout << sample[i] << std::endl;

	delete[] sample;

	/*
	for (int trial = 0; trial < 10; trial++) {

		sample = randomArr(sample_size);

		for (int run = 0; run < 20; run++) {
			start_time = static_cast<unsigned long>(time(NULL));
			insertionSort(sample, sample_size);
			end_time = static_cast<unsigned long>(time(NULL));


			start_time = static_cast<unsigned long>(time(NULL));
			//heap sort
			end_time = static_cast<unsigned long>(time(NULL));


			start_time = static_cast<unsigned long>(time(NULL));
			//quick sort
			end_time = static_cast<unsigned long>(time(NULL));

			sample_size += 1000;
		}
		
		delete[] sample;
	}
	*/

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
	for (int i = 1; i < size; i++) {
		int key = sample[i];

		int j = i - 1;
		while (j >= 1 && sample[j] > key) {
			sample[j + 1] = sample[j];
			j--;
		}
		sample[j + 1] = key;
	}
}

// HEAP SORT
/*	Purpose: Return index of parent node in heap tree
	Dependencies: none */
int parent(int node_pos) {
	return (node_pos / 2);
}

/*	Purpose: Return index of left child in heap tree
	Dependencies: none */
int left(int node_pos) {
	return (2 * node_pos);
}
/*	Purpose: Return index of right child in heap tree
	Dependencies: none */
int right(int node_pos) {
	return (2 * node_pos + 1);
}

/*	Purpose: place int at current_pos into the correct position in the heap
	Dependencies: std::swap */
void maxHeapify(int *A, int size, int current_pos){
	int largest;
	int left_pos = left(current_pos);
	int right_pos = right(current_pos);
	if ((left_pos <= size) && (A[left_pos] > A[current_pos]))
		largest = left_pos;
	else
		largest = current_pos;

	if ((right_pos <= size) && (A[right_pos] > A[largest]))
		largest = right_pos;

	if (largest != current_pos) {
		std::swap(A[current_pos], A[largest]);
		maxHeapify(A, size, largest);
	}
}

/*	Purpose: convert array into a max heap
	Dependencies: std::swap */
void buildMaxHeap(int *A, int size) {
	for (int i = (size / 2); i > 0; i--)
		maxHeapify(A, size, i);
}

/*	Purpose: sort array in increasing order
	Dependencies: std::swap */
void heapSort(int *A, int size) {
	int nodes_left = size;
	buildMaxHeap(A, size);
	for (int i = size; i > 1; i--) {
		std::swap(A[1], A[i]);
		nodes_left--;
		maxHeapify(A, nodes_left, 1);
	}
}


// QUICK SORT