// implemented from https://medium.com/human-in-a-machine-world/quicksort-the-best-sorting-algorithm-6ab461b5a9d0
// Function to swap two pointers
#ifndef QSORT_H
#define QSORT_H

#include <vector>
#include "freq.h"

void swap(Freq *a, Freq *b)
{
	Freq temp = *a;
	*a = *b;
	*b = temp;
}

// l is the leftmost starting index, which begins at 0
// r is the rightmost starting index, which begins at array length - 1
void quicksort(std::vector<Freq> &arr, int l, int r)
{
	// Base case: No need to sort arrays of length <= 1
	if (l >= r)
	{
		return;
	}

	// Choose pivot to be the last element in the subarray
	int pivot = arr[r];

	// Index indicating the "split" between elements smaller than pivot and 
	// elements greater than pivot
	int cnt = l;

	// Traverse through array from l to r
	for (int i = l; i <= r; i++)
	{
		// If an element less than or equal to the pivot is found...
		if (arr[i] <= pivot)
		{
			// Then swap arr[cnt] and arr[i] so that the smaller element arr[i] 
			// is to the left of all elements greater than pivot
			swap(&arr[cnt], &arr[i]);

			// Make sure to increment cnt so we can keep track of what to swap
			// arr[i] with
			cnt++;
		}
	}

	// NOTE: cnt is currently at one plus the pivot's index 
	// (Hence, the cnt-2 when recursively sorting the left side of pivot)
	quicksort(arr, l, cnt - 2); // Recursively sort the left side of pivot
	quicksort(arr, cnt, r);   // Recursively sort the right side of pivot
}
#endif