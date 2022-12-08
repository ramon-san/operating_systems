#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define ARRAY_SIZE 100000
#define RAND_NUM 300000

// void bubble_sort(int *array, int array_size);
void *bubble_sort();
void merge_sort(int *array, float array_size);
void merge_arrays(int *A,int *L,int leftCount,int *R,int rightCount);
typedef struct ArrayToSort {
  int *array;
  int size;
} ArrayToSort;

int main() {
    pthread_t tid1,tid2; /* The thread identifier */
    pthread_attr_t attr; /* Set of attributes for the thread, create struct. */

    srand(time(NULL)); // Randomize seed.
    // We create an array to sort.
    int num_list[ARRAY_SIZE];

    /* Get the default attributes. */
    pthread_attr_init(&attr);

    // printf("\nOriginal array: ");
    for (int i=0; i<ARRAY_SIZE; i++) {
        num_list[i] = rand() % RAND_NUM;
        // if (i == ARRAY_SIZE-1) printf("%d.\n", num_list[i]);
        // else printf("%d, ", num_list[i]);
    }
    
    clock_t begin = clock();
    /* Create the thread 1, encapsulating params as (void *). */
    ArrayToSort arr1 = {.array=num_list+ARRAY_SIZE/2, .size=ARRAY_SIZE/2}; 
    pthread_create(&tid1, &attr, bubble_sort, (void *)&arr1); // Sort first half of array.
    // for (int i = (ARRAY_SIZE/2); i < ARRAY_SIZE; i++)
    //     printf("T1 (%d): %d\n", i, num_list[i]);

    /* Create the thread 2, encapsulating params as (void *). */
    ArrayToSort arr2 = {.array=num_list, .size=ARRAY_SIZE/2};
    pthread_create(&tid1, &attr, bubble_sort, (void *)&arr2); // Sort second half of array.
    // for (int i = (ARRAY_SIZE/2); i < ARRAY_SIZE; i++)
    //     printf("T2 (%d): %d\n", i, num_list[i]);

    /* Wait for the threads, they're killed when process ends other wise.. */
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    merge_sort(num_list, ARRAY_SIZE);

    clock_t end = clock();
    double timeSpent = (double)(end - begin) / CLOCKS_PER_SEC; // Pass result to seconds.
    printf("End: %lu -> Begin: %lu", end, begin);
    printf("\nThreads took (%i): %f seconds\n", ARRAY_SIZE, timeSpent);
    
    // printf("\nSorted array: ");
    // for (int i=0; i<ARRAY_SIZE; i++) {
    //     if (i == ARRAY_SIZE-1) printf("%d.\n\n", num_list[i]);
    //     else printf("%d, ", num_list[i]);
    // }
}

/**
 * Function that does a bubble sort.
 * 
 * @param params    Structure of type ArrayToSort.
 *
 */
void *bubble_sort(void *params) {
    ArrayToSort *castedParams = (ArrayToSort *)params;
    int *array = castedParams->array;
    int array_size = castedParams->size;
    int sortFlag = 0;
    int tempHolder = 0;
    do {
        sortFlag = 1;
        // printf("\nIteration: ");
        for (int i = 1; i < array_size; i++) {
            if (array[i-1] > array[i]) {
                tempHolder = array[i-1];
                array[i-1] = array[i];
                array[i] = tempHolder;
            } else sortFlag++;
            // if (i-1 < array_size) printf("%i, ", array[i-1]);
            // if (i == array_size-1) printf("%i. ", array[i]);
        }
        // printf("Made %i moves.", array_size-sortFlag);
    } while (sortFlag < array_size);
    // printf("\n");
    return NULL;
}

/**
 * Function that does a merge sort.
 * 
 */
void merge_sort(int *array, float array_size) {
    if (array_size < 2) return;

    int *merge = NULL;
    int middle = (array_size/2);
    int *left = (int*)malloc(ceil(middle)*sizeof(int)); 
	int *right = (int*)malloc(floor(middle)*sizeof(int));

    for(int i = 0; i<middle; i++) left[i] = array[i]; // Creating left subarray
	for(int i = middle; i<array_size; i++) right[i-middle] = array[i]; // Creating right subarray
    
    merge_sort(left, middle);  // sorting the left subarray
	merge_sort(right, array_size-middle);  // sorting the right subarray

    // Merge results into one.
    merge_arrays(array, left, middle, right, array_size-middle);

    free(left);
    free(right);
}

/**
 * Function to merge left and right array into the original array. 
 * 
 * @param original_array    Array we started with.
 * @param left              What we consider the left array.
 * @param left_count        Number of elements in the left array.
 * @param right             What we consider the right array.
 * @param right_count       Number of elements in the right array.
 */
void merge_arrays(int *original_array,int *left,int left_count,int *right,int right_count) {
	int i = 0; // i - to mark the index of left subarray (left).
	int j = 0; // j - to mark the index of right subarray (right).
    int k = 0; // k - to mark the index of merged subarray (original_array).
	 

	while(i < left_count && j < right_count) {
		if(left[i]  < right[j]) original_array[k++] = left[i++];
		else original_array[k++] = right[j++];
	}
	while(i < left_count) original_array[k++] = left[i++];
	while(j < right_count) original_array[k++] = right[j++];
}