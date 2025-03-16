#include "dijkstras.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
using namespace std;

struct Node {
    int vertex, weight;
    bool operator>(const Node& other) const {
        return weight > other.weight;
    }
};
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int n = G.numVertices;
    vector<int> distances(n, INF);
    vector<bool> visited(n , false);
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    if (source < 0 || source >= n){return {};}
    if (G.empty()){return {};}

    distances[source] = 0;
    pq.push({source , 0});

    while (!pq.empty()){
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;
        if(visited[u]){continue;}
        visited[u] = true;
        //if (current_distance > distances[u]) {continue;}

        //if(G[u].empty()){continue;}

        for (const Edge &e : G[u]){
            int v = e.dst;
            int weight = e.weight;
            int new_distance = distances[u] + weight;

            if (new_distance < distances[v] && !visited[v]){
                distances[v] = new_distance;
                previous[v] = u;
                pq.push({v,distances[v]});
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
    //cout << "Shortest path: ";
    for (size_t i = 0; i < v.size(); ++i){
        cout << v[i] << " ";
    }
    cout << "\nTotal cost is " << total << endl;
}
