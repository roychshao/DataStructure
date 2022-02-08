/*
 *  It is a min heap use binary heap
 *  Author : royshao
 *  Date : 2022/2/8
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Minheap {
public:
    Minheap();
    void insert(int newval);
    int extract();
    void display();
    void heapify(int node);
    int getArrSize() { return arr.size(); };
private:
    vector<int> arr;
};

Minheap::Minheap() {
    arr.clear();
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

void
Minheap::heapify(int node) {
    if (node == 1)
        return;
    if (arr[node] < arr[node / 2])
        swap(arr[node], arr[node / 2]);
    heapify(node - 1);
}

void
Minheap::display() {
    for (auto it = arr.begin() + 1; it != arr.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

int main() {
    Minheap mh;
    int option = 0;
    int newnode, root;
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
        switch (option) {
        case 1:
            cout << "Enter the value of the node => ";
            cin >> newnode;
            mh.insert(newnode);
            break;
        case 2:
            root = mh.extract();
            cout << "Min value in the heap is : " << root << endl;
            break;
        case 3:
            mh.display();
            break;
        default:
            cout << "command not known" << endl;
            break;
        }
        mh.heapify(mh.getArrSize()-1);
    }
    cout << "program terminated." << endl;
    return 0;
}
