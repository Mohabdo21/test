#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000

/**
 * swap - Swaps the values of two integer pointers.
 *
 * @x: Pointer to first integer
 * @y: Pointer to second integer
 */
void swap(int *x, int *y)
{
	int temp = *x;

	*x = *y;
	*y = temp;
}

/**
 * partition - Partitions a subarray for quicksort.
 * Selects a pivot element, rearranges elements less
 * than the pivot to the left of it, and elements
 * greater than the pivot to the right of it.
 *
 * @arr: Array to partition
 * @low: Starting index of subarray
 * @high: Ending index of subarray
 *
 * Return: index of pivot element
 */
int partition(int arr[], long int low, long int high)
{
	int pivot_index, pivot_value, i, j;

	pivot_index = low + (rand() % (high - low));

	if (pivot_index != high)
		swap(&arr[pivot_index], &arr[high]);

	pivot_value = arr[high];
	i = (low);

	for (j = low; j < high; j++)
	{
		if (arr[j] <= pivot_value)
		{
			swap(&arr[i], &arr[j]);
			i++;
		}
	}
	swap(&arr[i], &arr[high]);

	return (i);
}

/**
 * quicksort_recursion - Recursively sorts a subarray using quicksort algorithm
 * @arr: Array to sort
 * @low: Starting index of subarray
 * @high: Ending index of subarray
 */
void quicksort_recursion(int arr[], long int low, long int high)
{
	if (low < high)
	{
		int pivot_index = partition(arr, low, high);

		quicksort_recursion(arr, low, pivot_index - 1);
		quicksort_recursion(arr, pivot_index + 1, high);
	}
}

/**
 * quicksort - Sorts an array of integers in ascending order using the
 * quicksort algorithm.
 * @arr: The array to be sorted.
 * @length: The number of elements in the array.
 */
void quicksort(int arr[], long int length)
{
	srand(time(NULL));

	quicksort_recursion(arr, 0, (length - 1));
}


/**
 * insertion_sort - Sorts an array of integers in ascending order using the
 * insertion sort algorithm
 * @arr: The array to be sorted
 * @length: The number of elements in the array
 */
void insertion_sort(int arr[], long int length)
{
	int i, j, key;

	for (i = 1; i < length; i++)
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

/**
 * bubble_sort - Sorts an array of integers in ascending order using the
 * bubble sort algorithm
 * @arr: The array to be sorted
 * @length: The number of elements in the array
 *
 * Repeatedly steps through the array, compares adjacent elements and
 * swaps them if they are in the wrong order.
 * The largest values bubble up to the end of the array.
 */
void bubble_sort(int arr[], long int length)
{
	bool swapped = false;
	int temp, i;

	do {
		swapped = false;
		for (i = 0; i < length - 1; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				swapped = true;
			}
		}
		length--;
	} while (swapped);
}

/**
 * selection_sort - Sorts an array of integers in ascending order using the
 * selection sort algorithm
 *
 * @arr: The array to be sorted
 * @length: The number of the elements in the array.
 *
 * Repeatedly finds the minimum element from the unsorted part and puts
 * it at the beginning.
 */
void selection_sort(int arr[], long int length)
{
	int min_pos, temp, i, j = 0;

	for (i = 0; i < (length - 1); i++)
	{
		min_pos = i;
		for (j = i + 1; j < length; j++)
		{
			if (arr[j] < arr[min_pos])
				min_pos = j;
		}
		if (min_pos != i) /* if necessary */
		{
			temp = arr[i];
			arr[i] = arr[min_pos];
			arr[min_pos] = temp;
		}
	}
}


/**
 * shellSort - Sorts an array using Shell sort algorithm.
 *
 * Sorts the input integer array by dividing it into smaller sublists,
 * sorting them with insertion sort, and progressively reducing the sublist
 * size until the entire array is sorted.
 *
 * @arr: The array to be sorted.
 * @length: The number of elements in the array.
 */
void shellSort(int arr[], long int length)
{
	int gap, i, j, temp;
	/* Start with a big gap, then reduce the gap */
	for (gap = length / 2; gap > 0; gap /= 2)
	{
		/* Do a gapped insertion sort for this gap size. */
		for (i = gap; i < length; i++)
		{
			/* add a[i] to the elements that have been gap sorted */
			temp = arr[i];
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
			{
				arr[j] = arr[j - gap];
			}
			/* put temp (the original a[i]) in its correct location */
			arr[j] = temp;
		}
	}
}

/**
 * main -  function to test sorting algorithms.
 * Initializes an array, prints it, sorts it using selection sort,
 * and prints the sorted array.
 * Return: 0 Always Success.
 */
int main(void)
{
	int arr[SIZE], arr_copy[SIZE];
	int j;
	clock_t start, end;
	double cpu_time_used;

	/* Seed the random number generator */
	srand(time(NULL));

	/* Generate 100000 random numbers */
	for (j = 0; j < SIZE; j++)
	{
		arr[j] = rand() % 100000; /* Generate numbers between 0 and 99999 */
	}

	printf("10 Items of 100000 Items Original array: ");
	for (j = 0; j < 10; j++)
	{
		printf("%d ", arr[j]);
	}
	printf("\n");

	memcpy(arr_copy, arr, SIZE * sizeof(int));
	start = clock();
	quicksort(arr_copy, SIZE);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time taken by quicksort: %f seconds\n", cpu_time_used);

	memcpy(arr_copy, arr, SIZE * sizeof(int));
	start = clock();
	selection_sort(arr_copy, SIZE);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time taken by selection sort: %f seconds\n", cpu_time_used);

	memcpy(arr_copy, arr, SIZE * sizeof(int));
	start = clock();
	insertion_sort(arr_copy, SIZE);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time taken by insertion sort: %f seconds\n", cpu_time_used);

	memcpy(arr_copy, arr, SIZE * sizeof(int));
	start = clock();
	bubble_sort(arr_copy, SIZE);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time taken by bubble sort: %f seconds\n", cpu_time_used);

	memcpy(arr_copy, arr, SIZE * sizeof(int));
	start = clock();
	shellSort(arr_copy, SIZE);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time taken by shell sort: %f seconds\n", cpu_time_used);

	printf("10 Items of 100000 Items Sorted array: ");
	for (j = 0; j < 10; j++)
	{
		printf("%d ", arr_copy[j]);
	}
	printf("\n");

	return (0);
}