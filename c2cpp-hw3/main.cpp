//============================================================================
// Name        : main.cpp
// Author      : Matt B
// Version     :
// Copyright   : Coursera HW
// Description : Dijkstra's Algorithm for a map graph assignment
//============================================================================

/* Basic problem:
 * Write a set of constructors for declaring and initializing
 * a graph. An edge will have a positive cost that is its distance. Have a
 * procedure that produces a randomly generated set of edges with positive
 * distances. Assume the graphs are undirected. The random graph procedure
 * should have edge density as a parameter and distance range as a parameter.
 * So a graph whose density is 0.1 would have 10% of its edges picked at random
 * and its edge distance would be selected at random from the distance range.
 * The procedure should run through all possible undirected edges, say (i,j)
 * and place the edge in the graph if a random probability calculation is less
 * than the density. Compute for a set of randomly generated graphs an average
 * shortest path.
 */

/* Turn in:
 * Printout of program, 200 words on what you learned, and output showing the average
 * path length calculation. Use densities: 20% and 40% on a graph of 50 nodes with
 * a distance range of 1.0 to 10.0. To get an average path length, compute the
 * 49 paths.
 */


#include <iostream>
#include <vector>
#include <list>

#include "graph.hpp"
#include "priority_queue.hpp"
#include "shortest_path.hpp"

using namespace std;

const unsigned int START_NODE   = 10;
const unsigned int END_NODE     = 10;

int main() {
    int verticies = 50;
    float max_range = 9.5;
    float density = 0.2;
    Graph * graph = new Graph(verticies, max_range, density);

    Shortest_Path * Path = new Shortest_Path(graph, START_NODE, END_NODE);
    for(int x = 0; x < verticies; x++)
    {
        for(int y = 0; y < verticies; y++)
        {
            Path->path();
        }
    }
    cout << "-fin-" << endl;
    return 0;
}
