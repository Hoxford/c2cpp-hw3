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

//todo: "What I learned" write up
//todo: path calculation printouts
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
#include <algorithm>
#include <string>
#include <typeinfo>

#include "graph.hpp"
#include "priority_queue.hpp"
#include "shortest_path.hpp"

using namespace std;

const unsigned int DEFAULT_VERTICIES = 50;
const double       DEFAULT_RANGE     = 10.0;
const double       DEFAULT_DENSITY   = 0.04;
const unsigned int START_NODE    = 0;
const unsigned int END_NODE      = 49;

//todo: get rid of "stuff" code

template <class L, class U>
class queue_of_stuff
{
public:
    queue_of_stuff(L len)
    {
//        order.resize(length);
        queue_len = 0;
    }

    bool put_front(U thing)
    {
        queue_len++;
        queue.insert(queue.begin(), thing);

        return true;
    }

    bool pop_front(U * item)
    {
        if(queue_len > 0)
        {
            *item = queue[0].item_;
            queue_len--;
            if(queue_len == 0)
            {
                queue.clear();
            }
            else
            {
                queue.erase(queue.begin());
            }

            return true;
        }
        return false;
    }

private:
    class queue_item
    {
    public:
        queue_item(U item)
        {
            item_ = item;
        }
        U item_;
    };
    unsigned int queue_len;
    vector<queue_item>queue;
};

template<typename item>
struct items
{
    item index;
    item value;
};

template <class T>
class do_stuff
{
public:
    do_stuff(vector<T>*n, T a, T b);
    T biggest();
    T smallest();
    T diff();
    T sum();
    T orderly_sum(T start, T end);

    template<typename items>
    struct item
    {
        T index;
        T value;
    };

private:
    T a_;
    T b_;
    vector<T>*n_;
};

template <class T>
do_stuff<T>::do_stuff(vector<T>*n, T a, T b)
{
    cout << (__PRETTY_FUNCTION__) << endl;
    a_ = a;
    b_ = b;
    n_ = n;
}

template <class T>
T do_stuff<T>::orderly_sum(T start, T end)
{
    assert(start != end);
    assert(start < end);
    vector<items<T>>work_list;
    items<T> Looking_at;
    vector<items<T>>ordered_list;
    T sum = 0;
//    T diff = end - start;
//    T i;
//    unsigned int n;
//
//    //fill the vector list with items from stuffs vector
//    for(i = start, n = 0; i <= end; i++, n++)
//    {
//        work_list.push_back(items<T>());
//        work_list[n].index = i;
//        work_list[n].value = (*n_)[i];
//        cout << "work_list[" << n << "].index =" << work_list[n].index << endl;
//        cout << "work_list[" << n << "].value =" << work_list[n].value << endl;
//    }

    Priority_Queue<T,items<T>> * pOrderly_queue = new Priority_Queue<T,items<T>>();

//    if(diff == 1)
//    {
//        if(work_list[0].value < work_list[1].value)
//        {
//            sum = work_list[0].value + work_list[1].value;
//        }
//        else
//        {
//            sum = work_list[1].value + work_list[0].value;
//        }
//    }
//    else
//    {
//        //start queue list
//        pOrderly_queue->put_front(work_list[0]);
//
//        for(n = 1; n < work_list.size(); n++)
//        {
//            pOrderly_queue->pop_front(&Looking_at);
//            while(1)
//            {
//                //find in the queue where the work list item is less then the queue item
//                //signifying where the value should go
//                if(work_list[n].value > Looking_at.value)
//                {
//                    //ordered list will be in reverse order but put back in order when put in queue
//                    ordered_list.insert(ordered_list.begin(), Looking_at);
//                    bool rc;
//                    rc = pOrderly_queue->pop_front(&Looking_at);
//                    //check if the end of the queue was reached
//                    if(rc == false)
//                    {
//                        //end of queue, put work list item on the queue
//                        pOrderly_queue->put_front(work_list[n]);
//                        while(ordered_list.size() > 0)
//                        {
//                            pOrderly_queue->put_front(ordered_list[0]);
//                            ordered_list.erase(ordered_list.begin());
//                        }
//                        break;
//                    }
//                }
//                else
//                {
//                    //found spot to insert work list item into queue
//
//                    //put looking at item back in queue
//                    pOrderly_queue->put_front(Looking_at);
//
//                    //put work list item on top of the queue
//                    pOrderly_queue->put_front(work_list[n]);
//
//                    //put ordered list items on top of the queue
//                    while(ordered_list.size() > 0)
//                    {
//                        Looking_at = ordered_list[0];
//                        pOrderly_queue->put_front(Looking_at);
//                        ordered_list.erase(ordered_list.begin());
//                                //work_list[n]);
//                    }
//                    break;
//                }
//            }
//        }
//    }

    for(T i = start; i <= end; i++)
    {

    }

    //perform the orderly sum
    while(pOrderly_queue->pop_front(&Looking_at) == true)
    {
        cout << "ordered queue index =" << Looking_at.index << endl;
        cout << "ordered queue value =" << Looking_at.value << endl;
        sum += Looking_at.value;
    }

    return sum;
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
    the_stuff(unsigned int x, unsigned int y)
    {
        x_ = x;
        y_ = y;
        srand(y_);
        for(int i = 0; i < x_; i++)
        {
            int value = rand();
            my_vector_of_stuff.push_back(value);
        }
        pDo_Stuff = new do_stuff<int>(&my_vector_of_stuff, x_, y_);
    };

    do_stuff<int> * pDo_Stuff;
private:
    int x_,y_;
    vector<int> my_vector_of_stuff;
};

//todo FEATURE take input parameters
int main() {

    const unsigned int STUFF_LEN = 10;
    const unsigned int STUFF_SEED = 4;
    the_stuff * Stuff = new the_stuff(STUFF_LEN,STUFF_SEED);

    cout << "orderly sum: " << Stuff->pDo_Stuff->orderly_sum(4,6) << endl;

    //test loop to exercise the pathing algorithm
    for(int i = 0; i < 20; i ++)
    {
        Graph graph(DEFAULT_VERTICIES, DEFAULT_RANGE, DEFAULT_DENSITY);
        Shortest_Path<float> Path(&graph, START_NODE, END_NODE);
        cout << "Path cost: " << Path.path_cost() << endl;
    }


    cout << "-fin-" << endl;
    return 0;
}

