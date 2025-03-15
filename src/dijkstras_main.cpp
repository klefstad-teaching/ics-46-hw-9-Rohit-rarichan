#include "dijkstras.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main (){
    Graph G;
    string filename;

    cout << "Enter the filename containing the graph: ";
    cin >> filename;

    try{
        file_to_graph(filename, G);
    }catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }
    int source, destination;
    cout << "Enter source vertex: ";
    cin >> source;
    cout << "Enter destiantion vertex: ";
    cin >> destination;

    if (source < 0 || source >= G.numVertices || destination < 0 || destination >= G.numVertices){
        cerr << "Invalid source or destination vertex" << endl;
        return 1;
    }

    vector<int> previous;
    vector<int> distance = dijkstra_shortest_path(G, source, previous);
    vector<int> path = extract_shortest_path(distance, previous, destination);

    print_path(path, distance[destination]);

    return 0;
}