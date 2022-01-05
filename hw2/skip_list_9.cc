/*
 * C++ Program to Implement Skip List 
 */
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#define MAX_LEVEL 200    // change original max level 6 to 200 , for not to restrict the level
const float P = 0.5;
int highest = 0;    // record the highest level
long long totallvl = 0; // record the total level to get average level
double avglvl = 0.0;    // average level
using namespace std;
/*
 * Skip Node Declaration
 */
struct snode
{
    int value;
    snode **forw;
    snode(int level, int &value)
    {
        forw = new snode * [level + 1];
        memset(forw, 0, sizeof(snode*) * (level + 1));
        this->value = value; 
    }
    ~snode()
    {
        delete [] forw;        
    } 
};
/*
 * Skip List Declaration
 */
struct skiplist
{
    snode *header;
    int value;
    int level;
    skiplist() 
    {
        header = new snode(MAX_LEVEL, value);
        level = 0;
    }
    ~skiplist() 
    {
        delete header;
    }
    void display();
    bool contains(int &);
    void insert_element(int &);
    void delete_element(int &);        
};
/*
 * Main: Contains Menu
 */
int main() 
{
    int randnum, k = 10;
    bool search = false;
    srand(time(NULL));
    ofstream result;    /* store experiment result in the file "skip_result_9.csv" */
    result.open("skip_result_9.csv");
    while(k < 31)
    {
        skiplist ss;
        int i = 0, length = 1 << k;
        cout << length << endl;
        clock_t insertStart, insertEnd;
        insertStart = clock();
        highest = 0, avglvl = 0.0, totallvl = 0;

        /* insert */
        while(i < length)
        {
            randnum = rand() / RAND_MAX;
            ss.insert_element(randnum);
            i++;
        }
        insertEnd = clock();
        double insertDiff = double(insertEnd)/CLOCKS_PER_SEC - double(insertStart)/CLOCKS_PER_SEC;
        result << "n=2^" << k << ",Insert," << insertDiff;

        /* search */
        clock_t searchStart, searchEnd;
        searchStart = clock();
        for(int i = 0; i < 100000; ++i)
        {
            randnum = rand() % RAND_MAX;
            search = ss.contains(randnum);
        }
        searchEnd = clock();
        double searchDiff = double(searchEnd)/CLOCKS_PER_SEC - double(searchStart)/CLOCKS_PER_SEC;
        result << ",Search," << searchDiff;
        result << ",TopLevel," << highest;
        cout << "totallvl: " << totallvl << endl;
        avglvl = double(totallvl) / double(length);
        cout << "avglvl: " << avglvl << endl;
        result << fixed;
        result << setprecision(3);
        result << ",Avglvl," << avglvl << endl;
        cout << "n=2^" << k << " completed.." << endl << endl;
        k++;
    }
    result.close();
    return 0;
}
 
/*
 * Random Value Generator
 *
float frand() 
{
    return (float) rand() / RAND_MAX;
}
 */

/*
 * Random Level Generator
 */
int random_level() 
{
    static bool first = true;
    if (first) 
    {
        srand((unsigned)time(NULL));
        first = false;
    }
    // use positive probility 0.9
    int lvl = 0, randnum = rand() % 10;
    while(randnum > 0)
    {
        randnum = rand() % 10;
        lvl++;
    }
    return (lvl < MAX_LEVEL) ? lvl : MAX_LEVEL;
}
 
/*
 * Insert Element in Skip List
 */
void skiplist::insert_element(int &value) 
{
    snode *x = header;	
    snode *update[MAX_LEVEL + 1];
    memset(update, 0, sizeof(snode*) * (MAX_LEVEL + 1));
    int lvl = random_level();
    totallvl += lvl;
    highest = lvl > highest ? lvl : highest;
    for (int i = level;i >= 0;i--) 
    {
        while (x->forw[i] != NULL && x->forw[i]->value < value) 
        {
            x = x->forw[i];
        }
        update[i] = x; 
    }
    x = x->forw[0];
    if (x == NULL || x->value != value) 
    {        
        if (lvl > highest)
            highest = lvl;
        if (lvl > level) 
        {
            for (int i = level + 1;i <= lvl;i++) 
            {
                update[i] = header;
            }
            level = lvl;
        }
        x = new snode(lvl, value);
        for (int i = 0;i <= lvl;i++) 
        {
            x->forw[i] = update[i]->forw[i];
            update[i]->forw[i] = x;
        }
    }
}
 
/*
 * Search Elemets in Skip List
 */
bool skiplist::contains(int &s_value) 
{
    snode *x = header;
    for (int i = level;i >= 0;i--) 
    {
        while (x->forw[i] != NULL && x->forw[i]->value < s_value)
        {
            x = x->forw[i];
        }
    }
    x = x->forw[0];
    return x != NULL && x->value == s_value;
}
