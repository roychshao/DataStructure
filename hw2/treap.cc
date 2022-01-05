/*
 * C++ Program to Implement Treap
 */
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;
 
typedef struct ctreenode *ctree;
/*
 * Tree Node Declaration
 */
struct ctreenode
{
    int key, fix;
    ctree left, right;
};
ctree nullnode, root;
 
/*
 * Treap Class Declaration
 */
class CTree
{
    public:
        void initialize();
        void sigrotl(ctree &);
        void sigrotr(ctree &);
        void insert(ctree &, int);
        void remove(ctree &, int);
        void display(ctree, int);
        void deletechildren(ctree);    
        bool find(ctree, int);	
        CTree()
        {}
};
/*
 * Initializing node 
 */
void CTree::initialize()
{
    nullnode = new ctreenode;
    nullnode->left = nullnode->right = nullnode;
    root = nullnode;
}
 
/*
 * Left Rotation
 */
void CTree::sigrotl(ctree& k1)
{
    ctree k2;
    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1 = k2;
}
 
/*
 * Right Rotation
 */
void CTree::sigrotr(ctree& k1)
{
    ctree k2;
    k2 = k1->left;
    k1->left = k2->right;
    k2->right = k1;
    k1 = k2;
}
/*
 * Insert Element into Treap
 */
void CTree::insert(ctree& t, int x)
{
    if (t == nullnode)
    {
        t = new ctreenode;
        t->left = t->right = nullnode;
        t->key = x;
        t->fix = rand();
    }
    else
    {
        if (t->key == x)
        {
            return;
	}
        else
        {
            if (x < t->key)
            {
                insert(t->left, x);
                if (t->left->fix > t->fix)
                    sigrotr(t);
            }
            else
            {
                insert(t->right, x);
                if (t->right->fix > t->fix)
                sigrotl(t);
            }
        }   
    }
}
 
/*
 * Remove Element from Treap
 */
void CTree::remove(ctree& t, int x)
{
    if (t == nullnode)
        return;
    if (x > t->key)
        remove(t->right, x);
    else if (x < t->key)
        remove(t->left, x);
    else
    {
        if (t->left == nullnode && t->right == nullnode)
        {
            delete t;
            t = nullnode;
        }
        else if (t->left == nullnode)
        {
            ctree tmp = t;
            t = t->right;
            delete tmp;
        }
        else if (t->right == nullnode)
        {
            ctree tmp = t;
            t = t->left;
            delete tmp;
        }
        else
        {
            if (t->left->fix < t->right->fix)
            {
                sigrotl(t);
                remove(t->left, x);
            }
            else
            {
                sigrotr(t);
                remove(t->right, x);
            }
        }
    }
}
/*
 * Search an element in Treap
 */
bool CTree::find(ctree t,int x)
{
    if (t == nullnode)
        return false;
    if (t->key == x)
        return true;
    else
    {
        if (x < t->key)
            return find(t->left, x);
        else
            return find(t->right, x);
    }
}

/*
 * Inorder Travesal of Treap
 */
void CTree::deletechildren(ctree ptr)
{
    if (ptr == nullnode)
        return;
    if (ptr != NULL)
    {
        deletechildren(ptr->left);
        remove(ptr, ptr->key);
        deletechildren(ptr->right);
    }
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
        CTree ct;
        int length = 1;
        clock_t insertStart, insertEnd;
        insertStart = clock();
        ct.initialize();
        // insert
        while(length < (1 << k))
        {
            randnum = rand() / RAND_MAX;
            ct.insert(root, randnum);
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
            search = ct.find(root, randnum);
        }
        searchEnd = clock();
        double searchDiff = double(searchEnd)/CLOCKS_PER_SEC - double(searchStart)/CLOCKS_PER_SEC;
        result << ",Search," << searchDiff << endl;
        cout << "n=2^" << k << " completed.." << endl;
        ct.deletechildren(root);
        k++;
    }
    result.close();
    return 0;
}
