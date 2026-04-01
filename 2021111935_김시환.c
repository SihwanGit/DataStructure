#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"
int experiment[10000];

void main() {
	srand((unsigned)time(NULL));
	int	list[SIZE], n = SIZE;
	int	exp_list[EXP_SIZE];

	printf("\n ----- insertion sort ----- \n");
	copy_list(original, list, n);
	print_list(list, 0, n - 1);
	num_compare = 0;
	insertion_sort(list, n, 1);
	printf("\n");
	print_list(list, 0, n - 1);
	printf("\n Total number of comparison = %d \n", num_compare);

	printf("\n ----- quick sort ----- \n");
	copy_list(original, list, n);
	print_list(list, 0, n - 1);
	num_compare = 0;
	quick_sort(list, 0, n - 1, 1);
	printf("\n");
	print_list(list, 0, n - 1);
	printf("\n Total number of comparison = %d \n", num_compare);

	printf("\n ----- merge sort ----- \n");
	copy_list(original, list, n);
	print_list(list, 0, n - 1);
	num_compare = 0;
	merge_sort(list, 0, n - 1, 1);
	printf("\n");
	print_list(list, 0, n - 1);
	printf("\n Total number of comparison = %d \n", num_compare);

	
	for (int i = 1; i <= 10; i++) {
		n = i * 1000;
		printf("\n ----- n = %d ----- \n", n);
		random_initialize(experiment, n);

		copy_list(experiment, exp_list, n);
		num_compare = 0; 
		insertion_sort(exp_list, n, 0);
		printf("\n No. of comparison (insertion sort) = %d \n", num_compare);

		copy_list(experiment, exp_list, n);
		num_compare = 0; 
		quick_sort(exp_list, 0, n - 1, 0);
		printf("\n No. of comparison (quick sort) = %d \n", num_compare);

		copy_list(experiment, exp_list, n);
		num_compare = 0; 
		merge_sort(exp_list, 0, n - 1, 0);
		printf("\n No. of comparison (merge sort) = %d \n", num_compare);
	}
	
}

// insertion sort
void insertion_sort(int list[], int n, int show) {
	int i, j, key;
	for (i = 0; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--) {
			list[j + 1] = list[j];
			num_compare++;
		}
		if (show == 1) print_list(list, 0, n - 1);
		list[j+1] = key;
	}
}

// quick sort
void quick_sort(int list[], int left, int right, int show) {
	int q;
	if (left < right) {
		q = partition(list, left, right);
		quick_sort(list, left, q-1, show);
		quick_sort(list, q+1, right, show);
	}
	if (show == 1) print_list(list, left, right);
}

int partition(int list[], int left, int right) {
	int low, high, pivot, temp;
	pivot = list[left];
	low = left;
	high = right + 1;
	do {
		do {
			low++;
		} while (list[low] < pivot);
		do {
			high--;
		} while (list[high] > pivot);
		if (low < high) {
			temp = list[high];
			list[high] = list[low];
			list[low] = temp;
		}
		num_compare++;
	} while (low < high);
	temp = list[high];
	list[high] = list[left];
	list[left] = temp;
	num_compare++;

	return high;
}

// merge sort
void merge_sort(int list[], int left, int right, int show) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(list, left, mid, show);
		merge_sort(list, mid + 1, right, show);
		merge(list, left, mid, right);
	}
	if (show == 1) print_list(list, left, right);
}

void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;
	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) {
			experiment[k++] = list[i++];
			num_compare++;
		}
		else {
			experiment[k++] = list[j++];
			num_compare++;
		}
	}
	if (i > mid) {
		for (l = j; l <= right; l++) experiment[k++] = list[l];
	}
	else if(j > right){
		for (l = i; l <= mid; l++) experiment[k++] = list[l];
	}

	for (l = left; l <= right; l++) list[l] = experiment[l];
}

/********/

void copy_list(int original[], int list[], int n)
{
	for (int i = 0; i < n; i++)
		list[i] = original[i];
}

void print_list(int list[], int left, int right)
{
	for (int i = 0; i < left; i++)
		printf("    ");
	for (int i = left; i <= right; i++)
		printf("%4d", list[i]);
	printf("\n");
}

void random_initialize(int list[], int n) {
	int i;
	for (i = 0; i < n; i++)
		list[i] = rand();
}