/*
 * Implementation of trie, support only for a single word,
 * if the input include ' ', the program will collapse.
 * Author: Roy Shao
 * Date: 2022/2/18
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
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
    Trie tr;
    while (true) {
        cout << "Enter '1' for insert a word to dictionary" << endl
            << "Enter '2' for delete a word from dictionary" << endl
            << "Enter '3' for search a word from dictionary" << endl
            << "Enter '4' for display the dictionary" << endl
            << "Enter '5' for exit the program and display the dictionary" << endl << "=> ";
        cin >> option;
        if (option == 5) {
            dic.clear();
            cout << endl << "---------------" << endl;
            tr.display(tr.getRoot());
            cout << "---------------" << endl;
            break;
        }
        // option switch case
        switch (option) {
        case 1:
            cout << "Enter the word => ";
            cin >> word;
            if(tr.search(word))
                cout << "This word has exist in the deictionary (x_x)" << endl;
            else
                tr.insert(word);
            break;
        case 2:
            cout << "Enter the word => ";
            cin >> word;
            if(!tr.search(word))
                cout << "This word isn't in the dictionary (x_x)" << endl;
            else
                tr.remove(word);
            break;
        case 3:
            cout << "Enter the word => ";
            cin >> word;
            if(tr.search(word))
                cout << '"' << word << '"' << " exist." << endl;
            else
                cout << '"' << word << '"' << " isn't existent." << endl;
            break;
        case 4:
            dic.clear();
            cout << endl << "---------------" << endl;
            tr.display(tr.getRoot());
            cout << "---------------" << endl;
            break;
        default:
            cout << "Command not known" << endl;
            break;
        }
    }
    cout << "program terminated." << endl;
    return 0;
}
