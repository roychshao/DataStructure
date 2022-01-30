#include <bits/stdc++.h>
using namespace std;

/* This function partitions a[] in three parts
   a) a[l..i] contains all elements smaller than pivot
   b) a[i+1..j-1] contains all occurrences of pivot
   c) a[j..r] contains all elements greater than pivot */
void partition(int a[], int l, int r, int& i, int& j)
{
	i = l - 1, j = r;
	int p = l - 1, q = r;
	int v = a[r];

	while (true) {
		// From left, find the first element greater than
		// or equal to v. This loop will definitely
		// terminate as v is last element
		while (a[++i] < v)
			;

		// From right, find the first element smaller than
		// or equal to v
		while (v < a[--j])
			if (j == l)
				break;

		// If i and j cross, then we are done
		if (i >= j)
			break;

		// Swap, so that smaller goes on left greater goes
		// on right
		swap(a[i], a[j]);

		// Move all same left occurrence of pivot to
		// beginning of array and keep count using p
		if (a[i] == v) {
			p++;
			swap(a[p], a[i]);
		}

		// Move all same right occurrence of pivot to end of
		// array and keep count using q
		if (a[j] == v) {
			q--;
			swap(a[j], a[q]);
		}
	}

	// Move pivot element to its correct index
	swap(a[i], a[r]);

	// Move all left same occurrences from beginning
	// to adjacent to arr[i]
	j = i - 1;
	for (int k = l; k < p; k++, j--)
		swap(a[k], a[j]);

	// Move all right same occurrences from end
	// to adjacent to arr[i]
	i = i + 1;
	for (int k = r - 1; k > q; k--, i++)
		swap(a[i], a[k]);
}

// 3-way partition based quick sort
void quicksort(int a[], int l, int r)
{
	if (r <= l)
		return;

	int i, j;

	// Note that i and j are passed as reference
	partition(a, l, r, i, j);

	// Recur
	quicksort(a, l, j);
	quicksort(a, i, r);
}

double Cal(double *record)
{
	double sum = 0;
	for(int i = 0; i < 10; ++i)
		sum += record[i];
	return sum / 10;
}

void Initialize(int *arr, int length)   /* use rand() to fill the array with 1~1000 */
{
	for(int i = 0; i < length; ++i)
		arr[i] = rand() % 1000 + 1;
}

int main()
{
	int k = 11;
	while(k < 31)
	{
		int length = 1 << k, counter = 0;
		cout << "k = " << k << endl;
		cout << "**********" << endl;
		double *record = new double[10];
		while(counter < 10)
		{
			int *arr = new int[length];
			if(arr == NULL)
				cout << "ERROR: array allocate failed." << endl;
			clock_t start, end;
			srand(time(NULL));
			Initialize(arr, length);
			start = clock();     //      start count the time
			quicksort(arr, 0, length);
			end = clock();       //      stop count the time
			double diff = double(end)/CLOCKS_PER_SEC - double(start)/CLOCKS_PER_SEC;
			cout << counter + 1 << ".Time = " << diff << endl;
			record[counter] = diff;
			delete[] arr;
			counter++;
		}
		double average = Cal(record);
		delete[] record;
		cout << "Average = " << average << endl;
		cout << "**********" << endl;
		k++;
	}
	return 0;
}
