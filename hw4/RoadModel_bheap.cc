/* Compile : g++ RoadModel_bheap.cc pbPlots.cpp pbPlots.hpp supportLib.cpp supportLib.hpp */
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctime>
#include "pbPlots.hpp"
#include "supportLib.hpp"

using namespace std;
int Vertex;
int citynum = 1;
int roadnum = 0;
int cn2 = 0;
int totaldis = 0;

struct City{
    int id;
    int x;
    int y;
    int ipt;
};

// A structure to represent a
// node in adjacency list
struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode* next;
};
 
// A structure to represent
// an adjacency list
struct AdjList
{
     
   // Pointer to head node of list
   struct AdjListNode *head;
};
 
// A structure to represent a graph.
// A graph is an array of adjacency lists.
// Size of array will be V (number of
// vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};
 
// A utility function to create
// a new adjacency list node
struct AdjListNode* newAdjListNode(
                   int dest, int weight)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*)
      malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
 
// A utility function that creates
// a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*)
            malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Create an array of adjacency lists. 
    // Size of array will be V
    graph->array = (struct AdjList*)
       malloc(V * sizeof(struct AdjList));
 
    // Initialize each adjacency list
    // as empty by making head as NULL
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src,
                   int dest, int weight)
{
    // Add an edge from src to dest. 
    // A new node is added to the adjacency
    // list of src.  The node is
    // added at the beginning
    struct AdjListNode* newNode =
            newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
 
    // Since graph is undirected,
    // add an edge from dest to src also
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
 
// Structure to represent a min heap node
struct MinHeapNode
{
    int  v;
    int dist;
};
 
// Structure to represent a min heap
struct MinHeap
{
     
    // Number of heap nodes present currently
    int size;    
   
    // Capacity of min heap
    int capacity; 
   
    // This is needed for decreaseKey()
    int *pos;   
    struct MinHeapNode **array;
};
 
// A utility function to create a
// new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v,
                                 int dist)
{
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*)
      malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
 
// A utility function to create a Min Heap
struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*)
      malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(
            capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**)
                 malloc(capacity *
       sizeof(struct MinHeapNode*));
    return minHeap;
}
 
// A utility function to swap two
// nodes of min heap.
// Needed for min heapify
void swapMinHeapNode(struct MinHeapNode** a,
                     struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
// A standard function to
// heapify at given idx
// This function also updates
// position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap* minHeap,
                                  int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->dist <
         minHeap->array[smallest]->dist )
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->dist <
         minHeap->array[smallest]->dist )
      smallest = right;
 
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        MinHeapNode *smallestNode =
             minHeap->array[smallest];
        MinHeapNode *idxNode =
                 minHeap->array[idx];
 
        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest],
                         &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
 
// A utility function to check if
// the given minHeap is ampty or not
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}
 
// Standard function to extract
// minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap*
                                   minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
 
    // Store the root node
    struct MinHeapNode* root =
                   minHeap->array[0];
 
    // Replace root node with last node
    struct MinHeapNode* lastNode =
         minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 
// Function to decreasy dist value
// of a given vertex v. This function
// uses pos[] of min heap to get the
// current index of node in min heap
void decreaseKey(struct MinHeap* minHeap,
                         int v, int dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];
 
    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;
 
    // Travel up while the complete
    // tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist <
           minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] =
                                      (i-1)/2;
        minHeap->pos[minHeap->array[
                             (i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], 
                 &minHeap->array[(i - 1) / 2]);
 
        // move to parent index
        i = (i - 1) / 2;
    }
}
 
// A utility function to check if a given vertex
// 'v' is in min heap or not
bool isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}
 
// A utility function used to print the solution
void printArr(int dist[], int n)
{
    //printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i){
        cn2++;
        totaldis += dist[i];
        //printf("%d \t\t %d\n", i, dist[i]);
    }
}
 
// The main function that calculates
// distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void dijkstra(struct Graph* graph, int src)
{
     
    // Get the number of vertices in graph
    int V = graph->V;
   
    // dist values used to pick
    // minimum weight edge in cut
    int dist[V];    
 
    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(V);
 
    // Initialize min heap with all
    // vertices. dist value of all vertices
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v,
                                      dist[v]);
        minHeap->pos[v] = v;
    }
 
    // Make dist value of src vertex
    // as 0 so that it is extracted first
    minHeap->array[src] =
          newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
 
    // Initially size of min heap is equal to V
    minHeap->size = V;
 
    // In the followin loop,
    // min heap contains all nodes
    // whose shortest distance
    // is not yet finalized.
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with
        // minimum distance value
        struct MinHeapNode* minHeapNode =
                     extractMin(minHeap);
       
        // Store the extracted vertex number
        int u = minHeapNode->v;
 
        // Traverse through all adjacent
        // vertices of u (the extracted
        // vertex) and update
        // their distance values
        struct AdjListNode* pCrawl =
                     graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;
 
            // If shortest distance to v is
            // not finalized yet, and distance to v
            // through u is less than its
            // previously calculated distance
            if (isInMinHeap(minHeap, v) &&
                      dist[u] != INT_MAX &&
              pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;
 
                // update distance
                // value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
 
    // print the calculated shortest distances
    printArr(dist, V);
}

// print the map , use the function in the libary "pbPlots"
// if interest , the file pbPlots.hpp and supportLib.hpp have more details
void printMap(vector<City> cities, int connection[100][100]){
    bool success;
    StringReference *errorMessage = new StringReference();
    RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
    vector<double> xs;
    vector<double> ys;
    for(auto it = cities.begin(); it != cities.end(); ++it){
        xs.push_back(it->x);
        ys.push_back(it->y);
    }

    double xleftline[] = {-3, -3};
    vector<double> xll(xleftline, xleftline+sizeof(xleftline)/sizeof(double));
    double yleftline[] = {-3, 100};
    vector<double> yll(yleftline, yleftline+sizeof(yleftline)/sizeof(double));
    double xbottomline[] = {-3, 100};
    vector<double> xbl(xbottomline, xbottomline+sizeof(xbottomline)/sizeof(double));
    double ybottomline[] = {-3, -3};
    vector<double> ybl(ybottomline, ybottomline+sizeof(ybottomline)/sizeof(double));

    /* set cities */
    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = &xs;
    series->ys = &ys;
    series->linearInterpolation = false;
    series->pointType = toVector(L"dots");
    series->color = CreateRGBColor(1, 0, 0);

    /* set left support line to let it show the whole map */
    ScatterPlotSeries *leftseries = GetDefaultScatterPlotSeriesSettings();
    leftseries->xs = &xll;
    leftseries->ys = &yll;
    leftseries->linearInterpolation = true;
    leftseries->lineType = toVector(L"solid");
    leftseries->lineThickness = 2;
    leftseries->color = CreateRGBColor(1, 1, 1);

    /* set bottom support line to let it show the whole map */
    ScatterPlotSeries *bottomseries = GetDefaultScatterPlotSeriesSettings();
    bottomseries->xs = &xbl;
    bottomseries->ys = &ybl;
    bottomseries->linearInterpolation = true;
    bottomseries->lineType = toVector(L"solid");
    bottomseries->lineThickness = 2;
    bottomseries->color = CreateRGBColor(1, 1, 1);

    /* draw all the settings above */
    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->width = 1500;
    settings->height = 1000;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    settings->title = toVector(L"");
    settings->xLabel = toVector(L"");
    settings->yLabel = toVector(L"");
    settings->scatterPlotSeries->push_back(series);
    settings->scatterPlotSeries->push_back(leftseries);
    settings->scatterPlotSeries->push_back(bottomseries);

    /* set roads */
    int cnt = 0;
    vector<double> xl[roadnum+5];//(xline, xline+sizeof(xline)/sizeof(double));
    vector<double> yl[roadnum+5];//(yline, yline+sizeof(yline)/sizeof(double));
    for(int i = 0; i < Vertex; ++i){
        for(int j = i+1; j < Vertex; ++j){
            if(connection[i][j] == 0) continue;
            xl[cnt].push_back(cities[i].x);
            xl[cnt].push_back(cities[j].x);
            yl[cnt].push_back(cities[i].y);
            yl[cnt].push_back(cities[j].y);
            ScatterPlotSeries* road = GetDefaultScatterPlotSeriesSettings();
            road->xs = &xl[cnt];
            road->ys = &yl[cnt];
            road->linearInterpolation = true;
            road->lineType = toVector(L"solid");
            road->lineThickness = 2;
            road->color = CreateRGBColor(0, 0, 1);
            settings->scatterPlotSeries->push_back(road);
            cnt++;
        }
    }

    success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

    if(success){
        vector<double> *pngdata = ConvertToPNG(imageReference->image);
        WriteToFile(pngdata, "roadgraph_bheap.png");
        DeleteImage(imageReference->image);
    }else{
        cerr << "Error: ";
        for(wchar_t c : *errorMessage->string){
            cerr << c;
        }
        cerr << endl;
    }
}

// function to get the straight distance
// between two cities
double StraightDis(City a, City b) {
    double xdis = abs(double(a.x) - double(b.x));
    double ydis = abs(double(a.y) - double(b.y));
    return (sqrt((xdis * xdis) + (ydis * ydis)));
}

// dfs traverse and add citynum
// if citynum equal to Vertex , means a city
// can get to all the other cities
void traversal(int i, int connection[100][100], bool checktraverse[100]){
    for(int j = 0; j < Vertex; ++j){
        if(i == j) continue;
        if(connection[i][j] != 0 && !checktraverse[j]){
            citynum++;
            checktraverse[j] = true;
            traversal(j, connection, checktraverse);
        }
    }
    return;
}

// function to generate roads between cities in a specific condition
void BuildRoad(vector<City> cities, struct Graph* graph, int connection[100][100]){
    for(auto it1 = cities.begin(); it1 != cities.end(); ++it1){
        for(auto it2 = cities.begin(); it2 != cities.end(); ++it2){
            int dis = int(StraightDis(*it1, *it2));
            if(it1 == it2){
                connection[it1->id][it2->id] = 0;
                continue;
            }
            else if(dis < 15 || (it1->ipt + it2->ipt) > 55){
                if(connection[it2->id][it1->id] == 0){
                    addEdge(graph,(it1->id), (it2->id), dis);
                }
                connection[it1->id][it2->id] = dis;
                roadnum++;
            }else
                connection[it1->id][it2->id] = 0;
        }
    }
}

// Driver program to test above functions
int main()
{
    // create the graph given in above fugure
    cout << "Build road model with binary heap and implement dijkstra's algorithm" << endl;
    cout << "==================================" << endl;
    cout << "Enter a number less than 100 : ";
    cin >> Vertex;
    srand(unsigned(time(NULL)));
    clock_t start, end;
    cout << "executing.." << endl;
    start = clock();
    vector<City> cities;
    // connection to record the status of connection
    // connection initialization
    int connection[100][100];
    for(int i=0;i<Vertex;++i){
        for(int j=0;j<Vertex;++j)
            connection[i][j] = 0;
    }
    /* traversal and rebuild the graph if it is not a connected graph */
    cout << "connected graph judging.." << endl;
    while(citynum != Vertex){
        struct Graph* graph = createGraph(Vertex);
        start = clock();
        cities.clear();
        citynum = 1, roadnum = 0;
        bool checktraverse[100];
        /* insert cities into vector */
        for(int i = 0; i < Vertex; ++i){
            City *tmp = new City;
            tmp->id = i;
            tmp->x = rand() % 100;
            tmp->y = rand() % 100;
            tmp->ipt = (rand() % 30) + 1;
            cities.push_back(*tmp);
            checktraverse[i] = false;
        }
        BuildRoad(cities, graph, connection);
        checktraverse[0] = true;
        traversal(0, connection, checktraverse);
        // if all connected , do dijkstra's algorithm
        if(citynum == Vertex){
        cout << "successfully build roads.." << endl;
        printMap(cities, connection);
        for(int i = 0; i < Vertex; ++i)
            dijkstra(graph, i);
        }
    }
    end = clock();
    double diff = double(end) / CLOCKS_PER_SEC - double(start) / CLOCKS_PER_SEC;
    cout << "Program complete!!\n";
    cout << "==================================" << endl;
    cout << roadnum << " road is build!" << endl;
    cout << "average distance of all cities : " << double(double(totaldis) / double(cn2)) << endl;
    cout << "spend time : " << diff << "(sec)" << endl;
    return 0;
}
