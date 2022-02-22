/*
 * Search engine for the whole data in the /data 
 * support for only a +b, a -b and a OR b, these three kind grammers
 *
 * Author: Roy Shao
 * Date: 2022/2/22
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <string>
#define MAX_WORD_LEN 10000
using namespace std;

//class node definition
class node{
    public:
        // constructors
        node(){
            word = ' ';
            leaf = false;
            nexts.clear();
            nexts.resize(95, NULL);
        };
        node(char c){
            word = c;
            leaf = false;
            nexts.clear();
            nexts.resize(95, NULL);
        };

        // append a character to the back of current charactor
        node* append(char c){
            node* place = find(c);
            if(place == NULL){
                node* newnode = new node(c);
                this->nexts[int(c - ' ')] = newnode;
                return newnode;
            }
            else
                return place;
        };

        // check if the there exist the charactor in the nexts
        node* find(char c){
            return nexts[int(c - ' ')];
        };
        char word;
        bool leaf;
        vector<node*> nexts;
};


// class Trie definition
class Trie{
    public:
        Trie();
        void insert(char*);
        void remove(char*);
        bool search(char*);
        void display(node*);
        node* getRoot() { return root; };
    private:
        // the virtual root
        node *root;
};

Trie::Trie(){
    root = new node();
}

// insert function
void
Trie::insert(char* word){
    node* current = root;
    node* pre = current;
    for(int i=0; i<strlen(word); ++i){
        pre = current;
        current = current->append(word[i]);
    }
    current->leaf = true;
}

// remove function
void
Trie::remove(char* word){
    vector<node*> pre;
    node* current = root;
    // first find the leaf of the word
    for(int i=0; i<strlen(word); ++i){
        node* tmp = current->find(word[i]);
        current = tmp;
    }
    // from the leaf, remove nodes upward if able
    current->leaf = false;
    for(int i=(pre.size()-1); i>=0; --i){
        node* tmp = pre[i];
        if(tmp->nexts.size() == 0 && tmp->leaf != true){
            pre.pop_back();
        }
        else
            return;
    }
}

// search function
bool
Trie::search(char* word){
    node* current = root;
    for(int i=0; i<strlen(word); ++i){
        node* tmp = current->find(word[i]);
        if(tmp)
            current = tmp;
        else
            return false;
    }
    return true;
}

// vector to store a word at a time
vector<char> dic;
// display function
void
Trie::display(node* node){
    if(!node)
        return;
    if(node->leaf == true){
        for(int i=0; i<dic.size(); ++i)
            cout << dic[i];
        cout << endl;
    }
    for(auto it:node->nexts){
        if(it != NULL){
            dic.push_back(it->word);
            display(it);
            dic.pop_back();
        }
    }
}

// main function
int main(int argc, char** argv){
    if(argc == 1){
        cout << "Please add the word to search for in the command line." << endl;
        return 0;
    }
    int option;
    char* word = new char [MAX_WORD_LEN];
    vector<Trie> trs(100);
    // read every word in files
    for(int i = 0; i < 100; ++i){
        ifstream ifs;
        string filename = "./data/" + to_string(i) + ".txt";
        ifs.open(filename);
        if(!ifs.is_open())
            cout << "Failed to open the file : " << filename << endl;
        else{
            int counter = 0;
            while(ifs >> word){
                trs[i].insert(word);
                counter++;
            }
        }
    }
    // console interface and search for the word
    bool find = false;

    clock_t start = clock(), end;

    cout << endl;
    cout << "-----------------" << endl;
    for(int i = 0; i < 100; ++i){
        if(argc == 2){
            if(trs[i].search(argv[1])){
                find = true;
                cout << "find in \"" << i << ".txt\"" << endl;
            }
        }else if(argc == 3){
            char* word2 = new char [strlen(argv[2])-1];
            for(int i=0; i<strlen(argv[2])-1; ++i)
                word2[i] = argv[2][i+1];
            if(argv[2][0] == '+'){
                if(trs[i].search(argv[1]) && trs[i].search(word2)){
                    find = true;
                    cout << "find in \"" << i << ".txt\"" << endl;
                }
            }
            else if(argv[2][0] == '-'){
                if(trs[i].search(argv[1]) && !trs[i].search(word2)){
                    find = true;
                    cout << "find in \"" << i << ".txt\"" << endl;
                }
            }
        }else if(argc == 4){
        // currently only support for "OR"
            if(trs[i].search(argv[1]) || trs[i].search(argv[3])){
                find = true;
                cout << "find in \"" << i << ".txt\"" << endl;
            }
        }
    }
    if(!find)
        cout << "Not found in any file." << endl;
    end = clock();
    double duration = double(end)/CLOCKS_PER_SEC - double(start)/CLOCKS_PER_SEC;
    cout << "-----------------" << endl;
    cout << "(Searching time : " << duration << ")" << endl << endl;
    return 0;
}
