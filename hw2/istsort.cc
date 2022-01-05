// C++ program for insertion sort
#include <bits/stdc++.h>
#include <ctime>
#include <fstream>
using namespace std;
 
/* Function to sort an array using insertion sort */
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// A recursive binary search function. It returns
// location of x in given array arr[l..r] is present,
// otherwise -1
int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;
 
        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return mid;
 
        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
 
        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, r, x);
    }
 
    // We reach here when element is not
    // present in array
    return -1;
}

/* Driver code */
int main()
{
    int randnum, k = 10;
    srand(time(NULL));
    ofstream result;
    result.open("sorted_result.csv");
    while(k < 31)
    {
        int idx = 0, length = 1 << k;
        clock_t insertStart, insertEnd;
        int *arr = new int[length];
        insertStart = clock();
        // insert
        while((idx+1) < length)
        {
            randnum = rand() / RAND_MAX;
            arr[idx] = randnum; // insert a random number to the tail of the array
            idx++;
        }
        insertionSort(arr, idx+1);
        insertEnd = clock();
        double insertDiff = double(insertEnd)/CLOCKS_PER_SEC - double(insertStart)/CLOCKS_PER_SEC;
        result << "n=2^" << k << ",Insert," << insertDiff;

        // search
        clock_t searchStart, searchEnd;
        searchStart = clock();
        for(int i = 0; i < 100000; ++i)
        {
            randnum = rand() % RAND_MAX;
            int search = binarySearch(arr, 0, length-1, randnum);
        }
        searchEnd = clock();
        double searchDiff = double(searchEnd)/CLOCKS_PER_SEC - double(searchStart)/CLOCKS_PER_SEC;
        result << ",Search," << searchDiff << endl;
        cout << "n=2^" << k << "completed.." << endl;
        k++; 
        delete [] arr;
    }
    result.close();
    return 0;
}
 
