/*
 * graph.hpp
 *
 *  Created on: Mar 4, 2018
 *      Author: Matt B
 */

#ifndef INC_GRAPH_HPP_
#define INC_GRAPH_HPP_

#include <iostream>
#include <vector>
#include <list>
#include <cassert>

using namespace std;

class Graph
{
public:
    Graph(unsigned int verticies, float max_range, double density);

    ~Graph();
    //todo: Priority_Queue function comment descriptions

    // returns the number of vertices in the graph
    unsigned int V();
    //returns the number of edges in the graph
    unsigned int E();
    //tests whether there is an edge from node x to node y.
    bool adjacent(unsigned int node_x, unsigned int y);
    //lists all nodes y such that there is an edge from x to y.
    vector<unsigned int>* neighbors(unsigned int node_x);
    //returns the value associated with the node x.
    int get_node_value (unsigned int node_x);
    //sets the value associated with the node x to a.
    bool set_node_value(unsigned int node_x, int a);
    //returns the value associated to the edge (x,y).
    float get_edge_value(unsigned int node_x, unsigned int node_y);
    //sets the value associated to the edge (x,y).
    bool set_edge_value(unsigned int node_x, unsigned int node_y, float value);

    unsigned int get_num_nodes()
    {
        return total_vertices_;
    }
private:
    //adds to G the edge from x to y, if it is not there, only used by the constructor.
    bool add_edge(unsigned int x, unsigned int y, float range);
    //removes the edge from x to y, if it is there, only used by the constructor.
    bool remove_edge(unsigned int node_x, unsigned int node_y);

    float density_;
    unsigned int total_vertices_;
    unsigned int total_edges_;
    float max_range_;
    vector<vector<double>>graph_;
    vector<int>values_;
};

inline unsigned int Graph::V()
{
    return total_vertices_;
}

inline unsigned int Graph::E()
{
    return total_edges_;
}

inline bool Graph::adjacent(unsigned int node_x, unsigned int node_y)
{
    return (graph_[node_y][node_x] == -1) ? false : true;
}

inline vector<unsigned int>* Graph::neighbors(unsigned int node_x)
{
    assert((node_x <= total_vertices_)&&(node_x >= 1));
    vector<unsigned int>neighbors;

    for(unsigned int y = 0; y < total_vertices_; y++)
    {
        if(graph_[node_x][y] != -1)
        {
            neighbors.push_back(y + 1);
        }
    }

    bool is_empty = neighbors.empty();
    return((is_empty == true) ? NULL : &neighbors);
}

inline bool Graph::add_edge(unsigned int node_x, unsigned int node_y, float range)
{
    if(graph_[node_y][node_x] == -1)
    {
        if(graph_[node_x][node_y] == -1)
        {
            graph_[node_y][node_x] = range;
            graph_[node_x][node_y] = range;
            cout <<"[" << node_y << "][" << node_x <<"] = "<<range<<endl;
        }
        else
        {
            cout <<"cant exist!"<<endl;
            return false;
        }
    }
    else
    {
        float existing_range = graph_[node_x][node_y];
        cout <<"[" << node_y << "][" << node_x <<"] = " << existing_range << ", existing edge"<<endl;
    }

    return true;
}

inline bool Graph::remove_edge(unsigned int node_x, unsigned int node_y)
{
    if(graph_[node_y][node_x] != -1)
    {
        if(graph_[node_x][node_y] != -1)
        {
            graph_[node_y][node_x] = -1;
            graph_[node_x][node_y] = -1;
        }
        else
        {
            cout <<"cant exist!"<<endl;
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}

inline int Graph::get_node_value(unsigned int node_x)
{
    assert((node_x <= total_vertices_)&&(node_x >= 1));
    return values_[(node_x - 1)];
}

inline bool Graph::set_node_value(unsigned int node_x, int a)
{
    assert((node_x <= total_vertices_)&&(node_x >= 1));
    values_[(node_x - 1)] = a;
    return true;
}

inline float Graph::get_edge_value(unsigned int node_x, unsigned int node_y)
{
    return graph_[node_y][node_x];
}

inline bool Graph::set_edge_value(unsigned int node_x, unsigned int node_y, float value)
{
    assert((node_x <= total_vertices_)&&(node_x >= total_vertices_));
    assert((value <= max_range_)&&(value >= 0.0));
    graph_[node_y - 1][node_x - 1] = value;
    graph_[node_x - 1][node_y - 1] = value;

    return true;
}


#endif /* INC_GRAPH_HPP_ */
