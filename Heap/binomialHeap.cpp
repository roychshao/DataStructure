/*
 * Binomial Heap implementation
 * Author: Roy Shao
 * Date: 2022/2/11
 */ 

#include <iostream>
#include <vector>
#include <algorithm>
#define IFN 2147483647  // infinite number, to initialize a min value
using namespace std;

int nodenum = 0;    // counter of the node's quantity in the heap

// node definition
struct node {
    int val;
    vector<node*> children;
};

// class Binomialheap definition
class Binomialheap {
public:
    Binomialheap();
    void insert(int newval);
    int extract();
    void display(vector<node*>, int);
    void merge(int, int);
    vector<node*> getArr() { return arr; };
private:
    vector<node*> arr;
    vector<int> status;
    vector<int> heapsize;
};

Binomialheap::Binomialheap() {
    arr.clear();
    arr.push_back(NULL);
    arr.push_back(NULL);
    status.push_back(-1);
    status.push_back(0);
    heapsize.push_back(0);
    heapsize.push_back(1);
}

// insert a node into heap
void
Binomialheap::insert(int newval) {
    node* newnode = new node;
    newnode->val = newval;
    newnode->children.push_back(NULL);
    arr[0] = newnode;
    if (status[1] == 1)
        merge(0, 1);
    else {
        arr[1] = newnode;
        arr[0] = NULL;
        status[1] = 1;
    }
}

// merge the two same size heap and move it to next index
void
Binomialheap::merge(int fidx, int sidx) {
    // build a new space and put the node in
    if (sidx >= arr.size()) {
        arr.push_back(arr[fidx]);
        arr[fidx] = NULL;
        status.push_back(1);
        status[fidx] = 0;
        heapsize.push_back(2 * heapsize[fidx]);
        return;
    }
    // if arr[sidx] not exists
    if (arr[sidx] == NULL) {
        arr[sidx] = arr[fidx];
        arr[fidx] = NULL;
        status[fidx] = 0;
        status[sidx]++;
        return;
    }
    // merge to one heap
    if (arr[fidx]->val < arr[sidx]->val) {
        arr[fidx]->children.push_back(arr[sidx]);
        arr[sidx] = arr[fidx];
        arr[fidx] = NULL;
    }
    else {
        arr[sidx]->children.push_back(arr[fidx]);
        arr[fidx] = NULL;
    }
    // update status
    status[fidx] = 0, status[sidx]++;
    // if neccessary, keep merging
    if (status[sidx] >= 2)
        merge(sidx, sidx + 1);
}

// return the min value in the heap and remove it from the heap
int
Binomialheap::extract() {
    int min = IFN;
    int minidx = 0;
    // find the min and the minidx
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] == NULL)
            continue;
        if (arr[i]->val < min) {
            min = arr[i]->val;
            minidx = i;
        }
    }
    // expose the heap
    vector<node*> children = arr[minidx]->children;
    arr[minidx] = NULL;
    status[minidx] = 0;
    for (auto it = children.begin() + 1; it != children.end(); ++it) {
        arr[0] = *it;
        int idx = 0;
        for (int i = 1; i < heapsize.size(); ++i) {
            if (((*it)->children.size()) == heapsize[i])
                idx = i;
        }
        // merge the exposed heap with original heap
        merge(0, idx);
    }
    return min;
}

// print out the status of the heap
void
Binomialheap::display(vector<node*> arr, int flag) {
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] == NULL) {
            cout << endl;
            continue;
        }
        node* tmp = arr[i];
        cout << tmp->val << " ";
        if(tmp->children.size() > 1)
            display(tmp->children, 0);
        if (flag)
            cout << endl;
    }
    // flag determine if the recursive function is at its first time
    if (flag) {
        for (int i = 1; i < status.size(); ++i)
            cout << status[i] << " ";
        cout << endl;
    }
}

// main function
int main() {
    Binomialheap bh;
    int option = 0;
    int newval, root;
    // construct the console
    while (true) {
        cout << "Enter '1' for insert a node" << endl
            << "Enter '2' for extract root" << endl
            << "Enter '3' for display the tree" << endl
            << "Enter '4' for exist the program while print the tree" << endl << "=> ";
        cin >> option;
        if (option == 4) {
            bh.display(bh.getArr(), 1);
            break;
        }
        // option switch case
        switch (option) {
        case 1:
            cout << "Enter the value of the node => ";
            cin >> newval;
            bh.insert(newval);
            nodenum++;
            break;
        case 2:
            if (!nodenum) {
                cout << "Attempt to extract a node from an empty heap" << endl;
                break;
            }
            root = bh.extract();
            nodenum--;
            cout << "Min value in the heap is : " << root << endl;
            break;
        case 3:
            bh.display(bh.getArr(), 1);
            break;
        default:
            cout << "command not known" << endl;
            break;
        }
    }
    cout << "program terminated." << endl;
    return 0;
}
