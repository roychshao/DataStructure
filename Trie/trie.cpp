#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAX_WORD_LEN 10000
using namespace std;


class node{
public:
    node(){
        word = ' ';
        leaf = false;
        nexts.clear();
    };
    node(char c){
        word = c;
        leaf = false;
        nexts.clear();
    };
    node* append(char c){
        node* place = find(c);
        if(place == NULL){
            node* newnode = new node(c);
            this->nexts.push_back(newnode);
            return newnode;
        }
        else
            return place;
    };
    node* find(char c){
        for(auto it:nexts){
            if(it->word == c)
                return it;
        }
        return NULL;
    };
    char word;
    bool leaf;
    vector<node*> nexts;
};

class Trie{
public:
    Trie();
    void insert(char*);
    void remove(char*);
    bool search(char*);
    void display(node*);
    node* getRoot() { return root; };
private:
    node *root;
};

Trie::Trie(){
    root = new node();
}

void
Trie::insert(char* word){
    node* current = root;
    node* pre = current;
    for(int i=0; i<strlen(word); ++i){
        pre = current;
        current = current->append(word[i]);
    }
    pre->leaf = true;
}

void
Trie::remove(char* word){
    vector<node*> pre;
    node* current = root;
    for(int i=0; i<strlen(word); ++i){
        node* tmp = current->find(word[i]);
        void* v = tmp;
        current = tmp;
    }
    current->leaf = false;
    for(int i=(pre.size()-1); i>=0; --i){
        node* tmp = pre[i];
        if(tmp->nexts.size() == 0){
            pre.pop_back();
        }
        else
            return;
    }
}

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

vector<char> dic;
void
Trie::display(node* node){
    if(!node)
        return;
    if(node->leaf){
        dic.push_back(node->word);
        for(int i=0; i<dic.size(); ++i)
            cout << dic[i];
        cout << endl;
    }
    for(auto it:node->nexts){
        dic.push_back(it->word);
        display(it);
        dic.pop_back();
    }
}

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
            tr.display(tr.getRoot());
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
                cout << word << "Exist." << endl;
            else
                cout << word << "Isn't existent." << endl;
            break;
        case 4:
            dic.clear();
            tr.display(tr.getRoot());
            break;
        default:
            cout << "Command not known" << endl;
            break;
        }
    }
    cout << "program terminated." << endl;
    return 0;
}
