/* Compile : g++ RoadModel_array.cc pbPlots.cpp pbPlots.hpp supportLib.cpp supportLib.hpp */
#include <iostream>
#include <vector>
#include <limits.h>
#include <stdio.h>
#include <ctime>
#include "pbPlots.hpp"
#include "supportLib.hpp"

using namespace std;
// Number of vertices in the graph
int V = 0;
int citynum = 1;
int roadnum = 0;
int cn2 = 0;
int totaldis = 0;

/* City struct */
struct City {
    int id;
    int x;
    int y;
    int ipt; // indicating the city's importance 
};

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to sum the constructed distance array
void calSolution(int dist[])
{
    for (int i = 0; i < V; i++){
        if(dist[i] != INT_MAX && dist[i] != 0){
            totaldis += dist[i];
            cn2++;
        }
    }
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[100][100], int src)
{
    int dist[100]; // The output array. dist[i] will hold the shortest
    // distance from src to i

    bool sptSet[100]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                    && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // print the constructed distance array
    calSolution(dist);
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
void traversal(int i, int graph[100][100], bool checktraverse[100]){
    for(int j = 0; j < V; ++j){
        if(i == j) continue;
        // use checktraverse to record if the city has been visited 
        if(graph[i][j] != 0 && !checktraverse[j]){
            citynum++;
            checktraverse[j] = true;
            traversal(j, graph, checktraverse);
        }
    }
    return;
}

// function to generate roads between cities in a specific condition
void BuildRoad(vector<City> cities, int graph[100][100]){
    for(auto it1 = cities.begin(); it1 != cities.end(); ++it1){
        for(auto it2 = cities.begin(); it2 != cities.end(); ++it2){
            if(it1 == it2){
                graph[it1->id][it2->id] = 0;
                continue;
            }
            // there are two condition to connect two city
            // 1. distance shorter than 15
            // 2. sum of importance larger than 55
            // (15 and 55 are defined by myself , to let the graph won't be too dense or too scattered)
            if(StraightDis(*it1, *it2) < 15 || (it1->ipt + it2->ipt) > 55){
                graph[it1->id][it2->id] = int(StraightDis(*it1, *it2));
                roadnum++;
            }else
                graph[it1->id][it2->id] = 0;
        }
    }
}

// print the map , use the function in the libary "pbPlots"
// if interest , the file pbPlots.hpp and supportLib.hpp have more details
void printMap(vector<City> cities, int graph[100][100]){
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
    for(int i = 0; i < V; ++i){
        for(int j = i+1; j < V; ++j){
            if(graph[i][j] == 0) continue;
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
        WriteToFile(pngdata, "roadgraph_array.png");
        DeleteImage(imageReference->image);
    }else{
        cerr << "Error: ";
        for(wchar_t c : *errorMessage->string){
            cerr << c;
        }
        cerr << endl;
    }
}

/* main function */
int main() {
    cout << "Build road model with array and implement dijkstra's algorithm" << endl;
    cout << "==================================" << endl;
    cout << "Enter a number less than 100 : ";
    cin >> V;
    srand(unsigned(time(NULL)));
    clock_t start, end;
    cout << "executing.." << endl;
    start = clock();
    vector<City> cities;
    // graph initialization
    int graph[100][100];
    for(int i = 0; i < V; ++i){
        for(int j = 0; j < V; ++j){
            graph[i][j] = 0;
        }
    }
    /* traversal and rebuild the graph if it is not a connected graph */
    cout << "connected graph judging.." << endl;
    while(citynum != V){
        start = clock();
        cities.clear();
        citynum = 1, roadnum = 0;
        bool checktraverse[100];
        /* insert cities into vector */
        for(int i = 0; i < V; ++i){
            City *tmp = new City;
            tmp->id = i;
            tmp->x = rand() % 100;
            tmp->y = rand() % 100;
            tmp->ipt = (rand() % 30) + 1;
            cities.push_back(*tmp);
            checktraverse[i] = false;
        }
        BuildRoad(cities, graph);
        checktraverse[0] = true;
        traversal(0, graph, checktraverse);
    }
    cout << "successfully build roads.." << endl;
    // print the map after successfully build
    printMap(cities, graph);
    for(int i = 0; i < V; ++i)
        dijkstra(graph, 0);
    end = clock();
    double diff = double(end) / CLOCKS_PER_SEC - double(start) / CLOCKS_PER_SEC;
    cout << "Program complete!!\n";
    cout << "==================================" << endl;
    cout << roadnum << " road is build!" << endl;
    cout << "average distance of all cities : " << double(double(totaldis) / double(cn2)) << endl;
    cout << "spend time : " << diff << "(sec)" << endl;
    return 0;
}
