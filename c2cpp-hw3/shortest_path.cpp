/*
 * shortest_path.cpp
 *
 *  Created on: Mar 8, 2018
 *      Author: storm
 */

#include <list>
#include "shortest_path.hpp"
#include "graph.hpp"
#include "priority_queue.hpp"

using namespace std;

Shortest_Path::Shortest_Path(Graph * graph, const unsigned int start, const unsigned int end)
{
//    shortest_path_ = NULL;

    start_ = start;
    end_ = end;
    graph_ = graph;


}

Shortest_Path::~Shortest_Path()
{

}

inline list<unsigned int> *Shortest_Path::path()
{
//    for(unsigned int i = 0; i < graph_->total_vertices_; i++)
//    {
//        if(graph_->)
//    }
    return &shortest_path_;
}

unsigned int Shortest_Path::path_size(int u, int w)
{
    return 0;
}

unsigned int Shortest_Path::path_exists(unsigned int node_a, unsigned int node_b)
{
    return 0;
}
