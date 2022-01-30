#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n, m;

struct Node {
    int ID;
    Node* left;
    Node* right;
};
vector<Node*> nodelist;

struct Edge {
    int start;
    int end;
    int cost;
};

bool cmp(Edge a, Edge b) {
    return (a.cost > b.cost);
}

void updateRoot(Node *oldroot, Node *newroot) {
    if (oldroot == NULL)
        return;
    nodelist[oldroot->ID-1] = newroot;
    if (oldroot->left != NULL)
        updateRoot(oldroot->left, newroot);
    if (oldroot->right != NULL)
        updateRoot(oldroot->right, newroot);
}

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

void Kruskal(vector<Edge> edgelist) {
    int totalcost = 0;
    for (int i = 0; i < n; ++i) {
        Node *newnode = new Node;
        newnode->ID = i+1;
        newnode->left = NULL;
        newnode->right = NULL;
        nodelist.push_back(newnode);
    }
    while (!edgelist.empty()) {
        Edge e = edgelist.back();
        edgelist.pop_back();
        if (nodelist[e.start-1]->ID != nodelist[e.end-1]->ID) {
            insert(nodelist[e.start - 1], nodelist[e.end - 1]);
            updateRoot(nodelist[e.end-1], nodelist[e.start-1]);
            totalcost += e.cost;
            cout << e.start << " to " << e.end << " (cost " << e.cost << ")" << endl;
        }
    }
    cout << "Minimum total cost is : " << totalcost << endl;
}

int main() {
    vector<Edge> edgelist;
    int s, e, c;
    cout << "Enter how many nodes are included : ";
    cin >> n;
    cout << "Enter how many connections are included : ";
    cin >> m;
    cout << "Enter each connection's information(start end cost), nodes represent by order : ";
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
}
