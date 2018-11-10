#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>

#define NUMS		(10000)

LARGE_INTEGER start, stop, duration, frequency;

void Start() {
	QueryPerformanceCounter(&start);
}

void Stop() {
	QueryPerformanceCounter(&stop);
	duration.QuadPart = stop.QuadPart - start.QuadPart;
	duration.QuadPart *= 1000000;
	duration.QuadPart /= frequency.QuadPart;
	double ms = duration.QuadPart / 1000.0;
	printf("%.2f ms\n", ms);
}

void Shuffle(int *nums, int n) {
	for (int i = n - 1; i > 0; --i) {
		int j = rand() & i;
		int tmp = nums[i];
		nums[i] = nums[j];
		nums[j] = tmp;
	}
}

bool Test(int *nums, int n) {
	for (int i = 0; i < n; ++i) {
		if (nums[i] != i) {
			return false;
		}
	}
	return true;
}

void Print(int *nums, int n) {
	for (int i = 0; i < n; ++i) {
		printf("%d ", nums[i]);
		if (i % 20 == 19 && i + 1 != n) {
			printf("\n");
		}
	}
	printf("\n");
}

void NaiveBubbleSort(int *nums, int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - 1; ++j) {
			if (nums[j] > nums[j + 1]) {
				int tmp = nums[j];
				nums[j] = nums[j + 1];
				nums[j + 1] = tmp;
			}
		}
	}
}

void BubbleSort(int *nums, int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - i - 1; ++j) {
			if (nums[j] > nums[j + 1]) {
				int tmp = nums[j];
				nums[j] = nums[j + 1];
				nums[j + 1] = tmp;
			}
		}
	}
}

void MergeSort(int *nums, int n) {
	if (n < 2) {
		return;
	}
	int nl = n / 2;
	int nr = n - nl;
	int *left = malloc(sizeof(int) * nl);
	int *right = malloc(sizeof(int) * nr);
	for (int i = 0; i < nl; ++i) {
		left[i] = nums[i];
	}
	for (int i = 0; i < nr; ++i) {
		right[i] = nums[i + nl];
	}
	MergeSort(left, nl);
	MergeSort(right, nr);
	int i = 0, j = 0;
	while (i < nl && j < nr) {
		if (left[i] < right[j]) {
			nums[i + j] = left[i];
			++i;
		}
		else {
			nums[i + j] = right[j];
			++j;
		}
	}
	while (i < nl) {
		nums[i + j] = left[i++];
	}
	while (j < nr) {
		nums[i + j] = right[j++];
	}
	free(left);
	free(right);
}

void QuickSortHelper(int *nums, int i, int j) {
	if (i < j) {
		int k = Partition(nums, i, j);
		QuickSortHelper(nums, i, k);
		QuickSortHelper(nums, k + 1, j);
	}
} 

void QuickSort(int *nums, int n) {
	QuickSortHelper(nums, 0, n - 1);
}

int Partition(int *nums, int i, int j) {
	int k = nums[i];
	--i;
	++j;
	for (;;) {
		do {
			++i;
		} while (nums[i] < k);
		do {
			--j;
		} while (nums[j] > k);
		if (i >= j) {
			return j;
		}
		int tmp = nums[i];
		nums[i] = nums[j];
		nums[j] = tmp;
	}
}

void RecursiveInsertionSort(int *nums, int n) {
	int i = 0;
	for (int j = 1; j < n; ++j) {
		if (nums[j] < nums[i]) {
			i = j;
		}
	}
	int tmp = nums[i];
	nums[i] = nums[0];
	nums[0] = tmp;
	if (n > 2) {
		RecursiveInsertionSort(nums + 1, n - 1);
	}
} 

void IterativeInsertionSort(int *nums, int n) {
	for (int i = 0; i < n; ++i) {
		int j = i;
		for (int k = j + 1; k < n; ++k) {
			if (nums[k] < nums[j]) {
				j = k;
			}
		}
		int tmp = nums[i];
		nums[i] = nums[j];
		nums[j] = tmp;
	}
}

void Heapify(int *nums, int n, int i) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && nums[l] > nums[largest]) {
		largest = l;
	}
	if (r < n && nums[r] > nums[largest]) {
		largest = r;
	}
	if (largest != i) {
		int tmp = nums[i];
		nums[i] = nums[largest];
		nums[largest] = tmp;
		Heapify(nums, n, largest);
	}
}

void HeapSort(int *nums, int n) {
	for (int i = n / 2 - 1; i >= 0; --i) {
		Heapify(nums, n, i);
	}
	for (int i = n - 1; i >= 0; --i) {
		int tmp = nums[0];
		nums[0] = nums[i];
		nums[i] = tmp;
		Heapify(nums, i, 0);
	}
}

int main() {
	QueryPerformanceFrequency(&frequency);
	srand(0);
	int n = NUMS;
	int *nums = malloc(sizeof(int) * n);
	for (int i = 0; i < n; ++i) {
		nums[i] = i;
	}
	void (*funcs[])(int*, int) = { 
		NaiveBubbleSort, BubbleSort, MergeSort,
		RecursiveInsertionSort,
		IterativeInsertionSort, QuickSort, HeapSort 
	};
	char *names[] = {
		"Naive Bubble", "Bubble", "Merge",
		"Rec Insertion", "Iter Insertion",
		"Quick Sort", "Heap"
	};
	int size = sizeof(funcs) / sizeof(*funcs);
	for (int i = 0; i < size; ++i) {	
		Shuffle(nums, n);
		Start();
		(*funcs[i])(nums, n);
		int len = strlen(names[i]) + strlen(" Sort");
		printf("%s Sort", names[i]);
		while (len < 25) {
			printf(" ");
			++len;
		}
		Stop();
		assert(Test(nums, n));
	}
	free(nums);
}

