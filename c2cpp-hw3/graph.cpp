/*
 * graph.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: storm
 */

#include <iostream>
#include <chrono>
#include <ctime>
#include <cassert>

#include "graph.hpp"

using namespace std;

Graph::Graph(unsigned int verticies, float max_range, double density)
{
    assert(density <= 1);
    assert((max_range >= 1.0)&(max_range <= 10.0));
    density_ = density;
    total_vertices_ = verticies;
    total_edges_ = 0;
    max_range_ = max_range;
    graph_.resize(verticies, vector<double>(verticies,-1));
    values_.resize(verticies, 0);

    srand(time(nullptr));

    for(unsigned int y = 0; y < total_vertices_; y++)
    {
        for(unsigned int x = 0; x < total_vertices_; x++)
        {
            if(y == x)
            {
                continue;
            }
            else
            {
                double random = rand() % 10;
                double edge_probability = random/10.0;
                if(edge_probability <= density_)
                {
                    int mod = max_range * 10;
                    float random = rand() % mod;
                    float edge_range = random/(10.0) + 0.1;
                    add_edge(x,y,edge_range);
                }
            }
        }
    }
}

Graph::~Graph()
{
    graph_.clear();
    graph_.shrink_to_fit();
    values_.clear();
    values_.shrink_to_fit();
}
