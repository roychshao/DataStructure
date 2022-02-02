/*
* the input data should be written in another file(.txt) and command ./Kruskal < input.txt
* Author : royshao
* Date : 2022/1/31
*/

#include <iostream>
#include <vector>
#include <queue>
#define IFN 2147483647
using namespace std;
int totalcost = 0;

// determine if all the nodes are visited
bool allVisited(vector<bool> visited){
    for(auto it = visited.begin(); it != visited.end(); ++it){
        if(*it == false)
            return false;
    }
    return true;
}

// extract min function
int extractMin(vector<int> &disToTree, vector<bool> &visited, int n){
    int min = IFN, minidx = 0;
    for(int i = 0; i < n; ++i){
        if(!visited[i] && disToTree[i] < min){
            min = disToTree[i];
            minidx = i;
        }
    }
    totalcost += min;
    return minidx;
}

// decrease key function
void decreaseKey(int **graph, int idx, vector<int> &disToTree, int n){
    for(int i = 0; i < n; ++i)
        disToTree[i] = (graph[idx][i] < disToTree[i]) ? graph[idx][i] : disToTree[i];
}

// Prim's algorithm
void Prim(int **graph, int n){
    vector<bool> visited(n, false);
    vector<int> disToTree(n, IFN);
    visited[0] = true;  // start from 0
    disToTree[0] = 0;
    decreaseKey(graph, 0, disToTree, n);
    cout << "add node 1 to the tree" << endl;
    while(!allVisited(visited)){
        int min = extractMin(disToTree, visited, n);
        cout << "add node " << min + 1 << " to the tree(cost " << disToTree[min] << " )" << endl;
        visited[min] = true;
        disToTree[min] = 0;
        decreaseKey(graph, min, disToTree, n);
    }
    cout << "Totalcost is : " << totalcost << endl;
}

int main(){
    int n = 0, m = 0;
    cin >> n >> m;
    // initialize graph
    int **graph = new int*[n];
    for(int i = 0; i < n; ++i){
        graph[i] = new int [n];
        for(int j = 0; j < n; ++j){
            if(i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = IFN;
        }
    }
    
    // constructing the graph
    for(int i = 0; i < m; ++i){
        int start = 0, end = 0, cost = 0;
        cin >> start >> end >> cost;
        while(start == 0 || end == 0){
            cout << "error : the node's order should start from 1." << endl;
            cin >> start >> end >> cost;
        }
        graph[start-1][end-1] = cost;
        graph[end-1][start-1] = cost;
    }
    Prim(graph, n);
    return 0;
}
