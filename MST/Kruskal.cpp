/*
 * the input data should be written in another file(.txt) and command ./Kruskal < input.txt
 * Author : royshao
 * Date : 2022/1/31
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n, m;

/* node structure definition */
struct Node {
    int ID;
    Node* left;
    Node* right;
};
vector<Node*> nodelist; // list to store the root that contains the node

/* edge structure definition */
struct Edge {
    int start;
    int end;
    int cost;
};

/* compare function */
bool cmp(Edge a, Edge b) {
    return (a.cost > b.cost);
}

/* recursive function to update the root in nodelist */
void updateRoot(Node *oldroot, Node *newroot) {
    if (oldroot == NULL)
        return;
    nodelist[oldroot->ID] = newroot;
    if (oldroot->left != NULL)
        updateRoot(oldroot->left, newroot);
    if (oldroot->right != NULL)
        updateRoot(oldroot->right, newroot);
}

/* recursive function to insert a root to another root */
void insert(Node *root, Node *leaf) {
    if (root == NULL)
        return;
    if (root->left != NULL && leaf->ID <= root->ID)
        insert(root->left, leaf);
    if (root->right != NULL && leaf->ID > root->ID)
        insert(root->right, leaf);
    if (root->left == NULL && leaf->ID <= root->ID)
        root->left = leaf;
    else if (root->right == NULL && leaf->ID > root->ID)
        root->right = leaf;
}

/* Kruskal's algorithm */
void Kruskal(vector<Edge> edgelist) {
    int totalcost = 0;
    nodelist.push_back(NULL);
    for (int i = 1; i <= n; ++i) {
        Node *newnode = new Node;
        newnode->ID = i;
        newnode->left = NULL;
        newnode->right = NULL;
        nodelist.push_back(newnode);
    }
    while (!edgelist.empty()) {
        Edge e = edgelist.back();
        edgelist.pop_back();
        if (nodelist[e.start]->ID != nodelist[e.end]->ID) {
            insert(nodelist[e.start], nodelist[e.end]);
            updateRoot(nodelist[e.end], nodelist[e.start]);
            totalcost += e.cost;
            cout << e.start << " to " << e.end << " (cost " << e.cost << ")" << endl;
        }
    }
    cout << "Minimum total cost is : " << totalcost << endl;
}

/* main function */
int main() {
    vector<Edge> edgelist;
    int s, e, c;
    cin >> n;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> s >> e >> c;
        Edge newroad;
        newroad.start = s;
        newroad.end = e;
        newroad.cost = c;
        edgelist.push_back(newroad);
    }
    sort(edgelist.begin(), edgelist.end(), cmp);
    Kruskal(edgelist);
    return 0;
}
