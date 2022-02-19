/*
 * Search engine for the whole data in the /data 
 * Author: Roy Shao
 * Date: 2022/2/19
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
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
int main(){
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
            while(ifs >> word){
                trs[i].insert(word);
            }
        }
    }
    // console interface and search for the word
    while(true){
        bool find = false;
        cout << "Please enter the word to search for" << endl
            << "(!q or !quit for exit)" << endl << "=>";
        cin >> word;
        if(strcmp(word, "!q") == 0 || strcmp(word, "!quit") == 0){
            cout << "program terminated." << endl;
            return 0;
        }
        cout << endl;
        cout << "--------------------" << endl;
        for(int i = 0; i < 100; ++i){
            if(trs[i].search(word)){
                find = true;
                cout << "find in \"" << i << ".txt\"" << endl;
           } 
        }
        if(!find)
            cout << "Not found in any file." << endl;
        cout << "--------------------" << endl << endl;
    }
    return 0;
}
