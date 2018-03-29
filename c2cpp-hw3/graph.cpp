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

#if defined(CANNED_GRAPH)
//Node 7 is completely isolated
//Node 2 is a dead end
//Node 8 & 9 connected but isolated from all others
//Node 6 & 9 has no path

static const double canned_graph[10][10] =
{
//      0,   1,   2,   3,   4,   5,   6,   7,   8,   9
    {  -1, 9.3,  -1, 4.5, 6.1, 0.3, 0.2,  -1,  -1,  -1},  //0
    { 9.3,  -1,  -1,   3, 5.6,  -1,  -1,  -1,  -1,  -1},  //1
    {  -1,  -1,  -1,  -1,  -1,  -1, 0.1,  -1,  -1,  -1},  //2
    { 4.5,   3,  -1,  -1, 6.9, 5.2, 1.2,  -1,  -1,  -1},  //3
    { 6.1, 5.6,  -1, 6.9,  -1, 1.2,  -1,  -1,  -1,  -1},  //4
    { 0.3,  -1,  -1, 5.2, 1.2,  -1,  -1,  -1,  -1,  -1},  //5
    { 0.2,  -1, 0.1, 1.2,  -1,  -1,  -1,  -1,  -1,  -1},  //6
    {  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1},  //7
    {  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 1.4},  //8
    {  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 1.4,  -1},  //9

};
#endif

Graph::Graph(unsigned int verticies, float max_range, double density)
{
    assert(density <= 1);
    assert((max_range >= 1.0)&(max_range <= 10.0));
#if defined(CANNED_GRAPH)
    density_ = density;
    total_vertices_ = 10;
    total_edges_ = 13;
    max_range_ = 10.0;
    graph_.resize(total_vertices_, vector<double>(total_vertices_,-1));
    values_.resize(total_vertices_, 0);
    for(unsigned int y = 0; y < total_vertices_; y++)
    {
        for(unsigned int x = 0; x < total_vertices_; x++)
        {
            add_edge(x,y,canned_graph[x][y]);
        }
    }
#else
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
#endif
}

Graph::~Graph()
{
    graph_.clear();
    graph_.shrink_to_fit();
    values_.clear();
    values_.shrink_to_fit();
}
