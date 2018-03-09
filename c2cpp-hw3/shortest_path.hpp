/*
 * shortest_path.hpp
 *
 *  Created on: Mar 4, 2018
 *      Author: storm
 */

#ifndef SHORTEST_PATH_HPP_
#define SHORTEST_PATH_HPP_

#include <list>
#include "graph.hpp"

using namespace std;

class Shortest_Path
{
public:
    //the constructor will determine the shortest path between start and end
    Shortest_Path(Graph * graph, unsigned int start, unsigned int end);
    ~Shortest_Path();
    //returns the shortest path between start and end
    list<unsigned int> *path();
    //return the path cost associated with the shortest path.
    unsigned int path_size(int u, int w);
private:
    unsigned int path_exists(unsigned int node_a, unsigned int node_b);
    Priority_Queue<unsigned int, float> pQueue;
    list<unsigned int> shortest_path_;
    unsigned int start_;
    unsigned int end_;
    Graph * graph_;
};

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

}

#endif /* SHORTEST_PATH_HPP_ */
