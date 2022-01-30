#include <bits/stdc++.h>
#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>

using namespace std;

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}
 
/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
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
                        quickSort(arr, 0, length);
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
