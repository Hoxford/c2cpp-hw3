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

//class point
//{
//public:
//	point operator+(point p)
//	{
//		return point(x+p.x_,y+p.y_);
//	}
//
//	point(double x = 0.0, double y = 0.0)
//	{
//		x_ = x;
//		y_ = y;
//	}
//private:
//	double x_, y_;
//};

template <class T>
class get_stuff
{
public:
    get_stuff(T a, T b)
    {
        a_ = a;
        b_ = b;
    }
    T biggest();
    T smallest();
    T diff();
    T sum();
private:
    T a_;
    T b_;
};

template <class T>
T get_stuff<T>::biggest()
{
    return(a_>b_)?a_:b_;
}

template <class T>
T get_stuff<T>::smallest()
{
    return(a_>b_)?b_:a_;
}

template <class T>
T get_stuff<T>::diff()
{
    if(a_>=b_)
    {
        return(a_ - b_);
    }
    else
    {
        return(b_ - a_);
    }
}

template <class T>
T get_stuff<T>::sum()
{
    return(a_ + b_);
}

class my_class
{
public:
    my_class(int x, int y)
    {
        x_ = x;
        y_ = y;
        pMy_stuff = new get_stuff<int>(x,y);
    };

    get_stuff<int> * pMy_stuff;
private:
    int x_,y_;
};

int main() {
    int verticies = 50;
    float max_range = 9.5;
    float density = 0.2;
//    point a, b(2,1), c(0.5,6);
    Graph * graph = new Graph(verticies, max_range, density);
    my_class * a_class = new my_class(2,4);

    cout << a_class->pMy_stuff->biggest() << endl;

//    a = b + c;
    Shortest_Path * Path = new Shortest_Path(graph, START_NODE, END_NODE);
    for(int x = 0; x < verticies; x++)
    {
        for(int y = 0; y < verticies; y++)
        {
//            Path->path();
        }
    }
    cout << "-fin-" << endl;
    return 0;
}
