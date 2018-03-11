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
#include <cassert>

#include "graph.hpp"
#include "priority_queue.hpp"
#include "shortest_path.hpp"

using namespace std;

const unsigned int START_NODE   = 10;
const unsigned int END_NODE     = 10;



template <class L, class U>
class order_stuff
{
public:
    order_stuff(L length)
    {
        order.resize(length);
    }

    bool put_on(U thing)
    {
        order.push_back(thing);
        return true;
    }

private:
    vector<U>order;
};

template<typename item>
struct items
{
    item index;
    item value;
};

//struct item
//{
//    item index;
//    item value;
//};

template <class T>
class do_stuff
{
public:
    do_stuff(vector<T>n, T a, T b)
    {
        a_ = a;
        b_ = b;
        n_ = n;
    }
    T biggest();
    T smallest();
    T diff();
    T sum();
    T orderly_sum(T start, T end);

//    template<typename items>
//    struct item
//    {
//        T index;
//        T value;
//    };

private:
    T a_;
    T b_;
    vector<T>n_;
};

template <class T>
T do_stuff<T>::orderly_sum(T start, T end)
{
    assert(start != end);
    assert(start < end);
//    assert(start >= a_);  todo a and b will need to represent beginning and end of vector
//    assert(end <= b_);
    vector<items<T>>stuff;
    T i;
    unsigned int n;

    //fill the vector list with items from stuffs vector
    for(i = start, n = 0; i <= end; i++, n++)
    {
        stuff.push_back(items<T>());
        stuff[n].index = i;
        stuff[n].value = n_[i];
    }

    order_stuff<T,items<T>> * pOrder = new order_stuff<T,items<T>>((start - end) + 1);
//    pOrder->put_on()
    //    pOrder->put_on(n_[start]);
//    for(T i = start; i <= end; i++)
//    {
//        pOrder;
//    }

    return 0;
}

template <class T>
T do_stuff<T>::biggest()
{
    return(a_>b_)?a_:b_;
}

template <class T>
T do_stuff<T>::smallest()
{
    return(a_>b_)?b_:a_;
}

template <class T>
T do_stuff<T>::diff()
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
T do_stuff<T>::sum()
{
    return(a_ + b_);
}

class the_stuff
{
public:
    the_stuff(int x, int y)
    {
        x_ = x;
        y_ = y;
        srand(y_);
        for(int i = 0; i < x_; i++)
        {
            my_vector_of_stuff.push_back(rand());
        }
        pDo_Stuff = new do_stuff<int>(my_vector_of_stuff, x_, y_);
    };

    do_stuff<int> * pDo_Stuff;
private:
    int x_,y_;
    vector<int> my_vector_of_stuff;
};

int main() {
//    int verticies = 50;
//    float max_range = 9.5;
//    float density = 0.2;
//    point a, b(2,1), c(0.5,6);
//    Graph * graph = new Graph(verticies, max_range, density);
    the_stuff * Stuff = new the_stuff(10,4);

    Stuff->pDo_Stuff->orderly_sum(3,8);

//    a = b + c;
//    Shortest_Path * Path = new Shortest_Path(graph, START_NODE, END_NODE);
//    for(int x = 0; x < verticies; x++)
//    {
//        for(int y = 0; y < verticies; y++)
//        {
////            Path->path();
//        }
//    }
    cout << "-fin-" << endl;
    return 0;
}
