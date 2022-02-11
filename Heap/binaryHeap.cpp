/*
 *  It is a min heap use binary heap
 *  Author : royshao
 *  Date : 2022/2/9
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int nodenum = 0;

// class Minheap definition
class Minheap {
public:
    Minheap();
    void insert(int newval);
    int extract();
    void display();
    void heapify(int node);
    int getArrSize() { return arr.size(); };
private:
    // use a vector to store datas
    vector<int> arr;
};

Minheap::Minheap() {
    arr.clear();
    // to make the index begin with 1, fill arr[0]
    arr.push_back(-1);
}

void
Minheap::insert(int newval) {
    arr.push_back(newval);
}

int
Minheap::extract() {
    int min = arr[1];
    arr[1] = arr.back();
    arr.pop_back();
    return min;
}

// recursive function from the head's left child of the array
// to heapify the array
void
Minheap::heapify(int node) {
    if (node > arr.size()-1)
        return;
    if (arr[node] < arr[node / 2])
        swap(arr[node], arr[node / 2]);
    heapify(node + 1);
}

// display the result currently
void
Minheap::display() {
    int counter = 1, cnt_record = 2;
    for (auto it = arr.begin() + 1; it != arr.end(); ++it){
        cout << *it << " ";
        if(counter == cnt_record -1){
            cout << "| ";
            cnt_record *= 2;
        }
        counter++;
    }
    cout << endl;
}

int main() {
    Minheap mh;
    int option = 0;
    int newnode, root;
    // construct the console
    while (true) {
        cout << "Enter '1' for insert a node" << endl
            << "Enter '2' for extract root" << endl
            << "Enter '3' for display the tree" << endl
            << "Enter '4' for exist the program while print the tree" << endl << "=> ";
        cin >> option;
        if (option == 4) {
            mh.display();
            break;
        }
        // option switch case
        switch (option) {
        case 1:
            cout << "Enter the value of the node => ";
            cin >> newnode;
            mh.insert(newnode);
            nodenum++;
            break;
        case 2:
            if(!nodenum){
                cout << "Attempt to extract a node from an empty heap." << endl;
                break;
            }
            root = mh.extract();
            nodenum--;
            cout << "Min value in the heap is : " << root << endl;
            break;
        case 3:
            mh.display();
            break;
        default:
            cout << "command not known" << endl;
            break;
        }
        mh.heapify(2);
    }
    cout << "program terminated." << endl;
    return 0;
}
