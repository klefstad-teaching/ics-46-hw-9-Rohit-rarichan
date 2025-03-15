#include "dijkstras.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int n = G.numVertices;
    vector<int> distances(n , INF);
    previous.assign(n, -1);

    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int, int>>> pq;
    distances[source] = 0;
    pq.push({0, source});

    while (!pq.empty()){
        int current_distance = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (current_distance > distances[u]) {continue;}

        for (const Edge &e : G[u]){
            int v = e.dst;
            int weight = e.weight;
            int new_distance = distances[u] + weight;

            if (new_distance < distances[v]){
                distances[v] = new_distance;
                previous[v] = u;
                pq.push({new_distance, v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    vector<int> path;
    if (distances[destination] == INF){
        return path;
    }
    for (int v = destination; v != -1; v = previous[v]){
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total)
{
    if (v.empty()){
        cout << "No path found." << endl;
        return;
    }
    cout << "Shortest path: ";
    for (size_t i = 0; i < v.size(); ++i){
        cout << v[i] << " ";
    }
    cout << "\nTotal cost is " << total << endl;
}
