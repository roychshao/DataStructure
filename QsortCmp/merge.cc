#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>

using namespace std;

void merge(int array[], int const left, int const mid, int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	// Create temp arrays
	auto *leftArray = new int[subArrayOne],
	*rightArray = new int[subArrayTwo];

	// Copy data to temp arrays leftArray[] and rightArray[]
	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0, // Initial index of first sub-array
		 indexOfSubArrayTwo = 0; // Initial index of second sub-array
	int indexOfMergedArray = left; // Initial index of merged array

	// Merge the temp arrays back into array[left..right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// right[], if there are any
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	free(leftArray);
	free(rightArray);
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */

void mergeSort(int array[], int const begin, int const end)
{
	if (begin >= end)
		return; // Returns recursively

	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
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
			mergeSort(arr, 0, length);
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
