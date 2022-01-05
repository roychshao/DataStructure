#include <bits/stdc++.h>
#include <fstream>
using namespace std;

class Hash
{
    int tablesize; // quan of buckets
    // Pointer to an array containing buckets
    list<int> *table;
public:
    Hash(int V); // Constructor
    void insert(int x); // insert
    int hashFunction(int x) // hash function
    {
        return (x % tablesize);
    }
    void clear()
    {
        delete [] table;
    } 
    void search(int);
};

Hash::Hash(int size)
{
    this->tablesize = size;
    table = new list<int>[tablesize];
}

void Hash::insert(int key)
{
    int index = hashFunction(key);
    table[index].push_back(key);
}

void Hash::search(int key)
{
    int index = hashFunction(key);
    list<int>::iterator i;
    //  traversal the index list
    for (i = table[index].begin(); i != table[index].end(); i++)
    {
        if (*i == key)
            return;
    }
}

int main()
{
    ofstream result;
    result.open("hash_result.csv", ios::out);
    int i = 10;
    while (i < 31)
    {
        Hash h(1 << i);
        clock_t Start, End;
        Start = clock();
        for (int j = 0; j < 1 << i; j++)
        {
            h.insert(rand()%(1<<31));
        }
        End = clock();
        result << "n=2^" << i << ",Insert,";
        double Diff = double(End - Start) / CLOCKS_PER_SEC;
        result << fixed << setprecision(6) << Diff;
        Start = clock();
        for(int j=0;j<100000;j++)
        {
            h.search(rand()%(1 << i));
        }
        End = clock();
        result << ",Search,";
        Diff = double(End - Start) / CLOCKS_PER_SEC;
        result << fixed << setprecision(6) << Diff << endl;
        cout << "n=2^" << i << " completed.." << endl;
        i++;
        h.clear();
    }
    result.close();
    return 0;
}
