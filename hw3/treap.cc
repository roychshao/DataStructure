#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct TreapNod  { //node declaration
   int data;
   int priority;
   TreapNod* l, *r;
   TreapNod(int d) { //constructor
      this->data = d;
      this->priority = rand() % 100;
      this->l= this->r = nullptr;
   }
};

void rotLeft(TreapNod* &root) { //left rotation
   TreapNod* R = root->r;
   TreapNod* X = root->r->l;
   R->l = root;
   root->r= X;
   root = R;
}

void rotRight(TreapNod* &root) { //right rotation
   TreapNod* L = root->l;
   TreapNod* Y = root->l->r;
   L->r = root;
   root->l= Y;
   root = L;
}

void insertNod(TreapNod* &root, int d) { //insertion
   if (root == nullptr) {
      root = new TreapNod(d);
      return;
   }
   if (d < root->data) {
      insertNod(root->l, d);
      if (root->l != nullptr && root->l->priority > root->priority)
      rotRight(root);
   } else {
      insertNod(root->r, d);
      if (root->r!= nullptr && root->r->priority > root->priority)
      rotLeft(root);
   }
}

bool searchNod(TreapNod* root, int key) {
   if (root == nullptr)
      return false;
   if (root->data == key)
      return true;
   if (key < root->data)
      return searchNod(root->l, key);
      return searchNod(root->r, key);
}

/*
 * Main Contains Menu
 */

int main()
{
    int randnum, k = 10;
    bool flag = false;
    bool search = false;
    srand(time(NULL));
    ofstream result;
    result.open("treap_result.csv");
    while(k < 31)
    {
        TreapNod *root = NULL;
        int length = 1;
        clock_t insertStart, insertEnd;
        insertStart = clock();
        // insert
        while(length < (1 << k))
        {
            randnum = rand() % RAND_MAX;
            insertNod(root, randnum);
            length++;
        }
        insertEnd = clock();
        double insertDiff = double(insertEnd)/CLOCKS_PER_SEC - double(insertStart)/CLOCKS_PER_SEC;
        result << "n=2^" << k << ",Insert," << insertDiff;

        // search
        clock_t searchStart, searchEnd;
        searchStart = clock();
        for(int i = 0; i < 100000; ++i)
        {
            randnum = rand() % RAND_MAX;
            search = searchNod(root, randnum);
        }
        searchEnd = clock();
        double searchDiff = double(searchEnd)/CLOCKS_PER_SEC - double(searchStart)/CLOCKS_PER_SEC;
        result << ",Search," << searchDiff << endl;
        cout << "n=2^" << k << " completed.." << endl;
        k++;
    }
    result.close();
    return 0;
}
