// M. Kaan Tasbas | mktasbas@gmail.com
// 13 March 2018

/* Info
	This program contains implementations of insertion sort, heap sort, and quick sort 
	and tests the average running time of each algorithm. 
	
	An array of size 20,000 integers is filled with randomly generated integers. This is
	used to test each alg with a starting sample size of 1,000 that is incremented by 1,000
	until we reach 20,000 samples. 10 trials are done with a new array each time. The average
	of these 10 runs are then used.

	For proper implementation of the heap array, array index 0 is not used. All data begins
	at index 1. For consistency, this method is used for all arrays containing sample data
	to be sorted.
*/

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <chrono>

#define START_SIZE	1000	// ns, inital sample size
#define DELTA		1000	// delta, sample increment between runs
#define END_SIZE	20000	// nf, final sample size
#define RUNS		20		// number of increments required
#define TRIALS		10		// m, number of trials to average from

/*	Purpose: Return an array of randomly generated integers
	Dependencies: chrono.h, initialization of srand at beginning of program */
int * randomArr(int size);

/*	Purpose: Return a new array copied from the original passed in
	Dependencies: none */
int * copyArr(int *org, int size);

/*	Purpose: Print a double array to screen with 6 fixed decimal places
	Dependencies: iostream.h, iomanip.h */
void printArr(double *A, int size);

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

/*	Purpose: sort selected area of array from p to r in increasing order
	Dependencies: std::swap */
int partition(int *A, int p, int r);

/*	Purpose: divide array into sections to sort using divide and conquer method
	Dependencies: none */
void quicksort(int *A, int p, int r);

int main() {
	int *ins_sample, *heap_sample, *quick_sample;
	int sample_size;

	std::chrono::high_resolution_clock::time_point//<std::chrono::high_resolution_clock>
		start_time,
		end_time;

	std::chrono::duration<double>
		ins_run_time[TRIALS][RUNS],
		heap_run_time[TRIALS][RUNS],
		quick_run_time[TRIALS][RUNS];

	double
		ins_avg_time[RUNS] = { 0 },
		heap_avg_time[RUNS] = { 0 },
		quick_avg_time[RUNS] = { 0 };

	//seed rand() function with time for actual random numbers
	srand((int)time(0));
	
	for (int trial = 0; trial < TRIALS; trial++) {
		// reset sample_size to repeat testing
		sample_size = START_SIZE;

		std::cout << " * Trial # " << (trial + 1) << " *\n";

		for (int run = 0; run < RUNS; run++) {
			std::cout << "  * Run # " << (run + 1) << " *\n";

			/* generate random array then copy it twice
			 each sort needs an original array to run on */
			ins_sample = randomArr(sample_size + 1);
			heap_sample = copyArr(ins_sample, sample_size + 1);
			quick_sample = copyArr(ins_sample, sample_size + 1);

			// first element not used, set to -1
			ins_sample[0] = heap_sample[0] = quick_sample[0] = -1;

			// profile insertion sort
			std::cout << "   ** Running insertion sort **\n";
			start_time = std::chrono::high_resolution_clock::now();
			insertionSort(ins_sample, sample_size);
			end_time = std::chrono::high_resolution_clock::now();
			{
				using namespace std::chrono;
				ins_run_time[trial][run] = duration_cast<duration<double>>(end_time - start_time);
			}

			// profile heap sort
			std::cout << "   ** Running heap sort **\n";
			start_time = std::chrono::high_resolution_clock::now();
			heapSort(ins_sample, sample_size);
			end_time = std::chrono::high_resolution_clock::now();
			{
				using namespace std::chrono;
				heap_run_time[trial][run] = duration_cast<duration<double>>(end_time - start_time);
			}

			// profile quicksort
			std::cout << "   ** Running quicksort **\n";
			start_time = std::chrono::high_resolution_clock::now();
			quicksort(quick_sample, 1, sample_size);
			end_time = std::chrono::high_resolution_clock::now();
			{
				using namespace std::chrono;
				quick_run_time[trial][run] = duration_cast<duration<double>>(end_time - start_time);
			}

			// recover memory of sample array's
			delete[] ins_sample;
			delete[] heap_sample;
			delete[] quick_sample;

			// increase sample size in accordance with selected delta
			sample_size += DELTA;
		}
	}

	// calculate avg running time of each sample size for each alg
	for (int run = 0; run < RUNS; run++) {
		for (int trial = 0; trial < TRIALS; trial++) {
			// calculate average time in milliseconds
			ins_avg_time[run] += ((ins_run_time[trial][run].count() / TRIALS) * 1000);
			heap_avg_time[run] += heap_run_time[trial][run].count() / TRIALS;
			quick_avg_time[run] += quick_run_time[trial][run].count() / TRIALS;
		}
	}

	// print average times to screen
	std::cout << "\nAlg Running Times:\n\n";

	std::cout << "Insertion Sort:\n";
	printArr(ins_avg_time, RUNS);
	std::cout << std::endl;

	std::cout << "Heap Sort:\n";
	printArr(heap_avg_time, RUNS);
	std::cout << std::endl;

	std::cout << "Quicksort:\n";
	printArr(quick_avg_time, RUNS);
	std::cout << std::endl;
	
	return 0;
}

/*	Purpose: Return an array of randomly generated integers
	Dependencies: chrono.h, initialization of srand at beginning of program */
int * randomArr(int size) {
	int * arr = new int[size];

	for (int i = 0; i < size; i++)
		arr[i] = rand();

	return arr;
}

/*	Purpose: Return a new array copied from the original passed in
	Dependencies: none */
int * copyArr(int *org, int size) {
	int * arr = new int[size];
	for (int i = 0; i < size; i++)
		arr[i] = org[i];
	return arr;
}

/*	Purpose: Print a double array to screen with 6 fixed decimal places
	Dependencies: iostream.h, iomanip.h */
void printArr(double *A, int size) {
	std::cout << std::fixed << std::setprecision(6);
	for (int i = 0; i < size; i++) {
		std::cout << A[i] << "\n";
	}
}

// INSERTION SORT

/*	Purpose: Sort array in increasing order using insertion sort method
	Dependencies: none */
void insertionSort(int *A, int size) {
	for (int i = 2; i <= size; i++) {
		int key = A[i];

		int j = i - 1;
		while (j > 0 && A[j] > key) {
			A[j + 1] = A[j];
			j--;
			//std::cout << j << std::endl;
		}
		A[j + 1] = key;
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

/*	Purpose: sort selected area of array from p to r in increasing order
	Dependencies: std::swap */
int partition(int *A, int p, int r) {
	int x = A[r];
	int i = p - 1;
	for (int j = p; j <= (r - 1); j++) {
		if (A[j] <= x) {
			i = i + 1;
			std::swap(A[i], A[j]);
		}
	}
	std::swap(A[i + 1], A[r]);
	return i + 1;
}

/*	Purpose: divide array into sections to sort using divide and conquer method 
	Dependencies: none */
void quicksort(int *A, int p, int r) {
	if (p < r) {
		int q = partition(A, p, r);
		quicksort(A, p, q - 1);
		quicksort(A, q + 1, r);
	}
}