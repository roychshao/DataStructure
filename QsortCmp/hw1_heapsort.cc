#include <bits/stdc++.h>
using namespace std;

void heapify(int arr[], int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
 
    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;
 
    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;
 
    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
 
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}
 
// main function to do heap sort
void heapSort(int arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);
 
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
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
                        heapSort(arr, length);
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
