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
#include <algorithm>

#include "graph.hpp"
#include "priority_queue.hpp"
#include "shortest_path.hpp"

using namespace std;

const unsigned int START_NODE   = 10;
const unsigned int END_NODE     = 10;



template <class L, class U>
class queue_of_stuff
{
public:
    queue_of_stuff()
    {
//        order.resize(length);
        queue_len = 0;
    }

    bool put_top(U thing)
    {
        queue_len++;
        queue.insert(queue.begin(), thing);

//        queue.push_back(queue_item(thing));
//        std::rotate(queue.begin(),queue.begin()+1,queue.end());

        return true;
    }

    bool pop_top(U * item)
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

//struct item
//{
//    item index;
//    item value;
//};

template <class T>
class do_stuff
{
public:
    do_stuff(vector<T>*n, T a, T b)
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
    vector<T>*n_;
};

template <class T>
T do_stuff<T>::orderly_sum(T start, T end)
{
    assert(start != end);
    assert(start < end);
//    assert(start >= a_);  todo a and b will need to represent beginning and end of vector
//    assert(end <= b_);
    vector<items<T>>work_list;
    items<T> Looking_at;
    vector<items<T>>ordered_list;
//    items<T> top;
    T diff = end - start;
    T i;
    T sum = 0;
    unsigned int n;

    //fill the vector list with items from stuffs vector
    for(i = start, n = 0; i <= end; i++, n++)
    {
        work_list.push_back(items<T>());
        work_list[n].index = i;
        work_list[n].value = (*n_)[i];
        cout << "work_list[" << n << "].index =" << work_list[n].index << endl;
        cout << "work_list[" << n << "].value =" << work_list[n].value << endl;
    }

    queue_of_stuff<T,items<T>> * pOrderly_queue = new queue_of_stuff<T,items<T>>();

    if(diff == 1)
    {
        if(work_list[0].value < work_list[1].value)
        {
            sum = work_list[0].value + work_list[1].value;
        }
        else
        {
            sum = work_list[1].value + work_list[0].value;
        }
    }
    else
    {
        pOrderly_queue->put_top(work_list[0]);

        //start queue list
//        for(int j = 0; j < diff; j++)
//        {
            for(n = 1; n < work_list.size(); n++)
            {
                pOrderly_queue->pop_top(&Looking_at);
                while(1)
                {
                    //find in the queue where the work list item is less then the queue item
                    //signifying where the value should go
                    if(work_list[n].value > Looking_at.value)
                    {
    //                    queue.insert(queue.begin(), thing);

                        //orderd list will be in reverse order but put back in order when put in queue
                        ordered_list.insert(ordered_list.begin(), Looking_at);
//                        ordered_list.push_back(Looking_at);
    //                    std::rotate(ordered_list.begin(),ordered_list.end(),ordered_list.end());
    //                    ordered_list[0] = Looking_at;
                        bool rc;
                        rc = pOrderly_queue->pop_top(&Looking_at);
                        //check if the end of the queue was reached
                        if(rc == false)
                        {
                            //end of queue, put work list item on the queue
                            pOrderly_queue->put_top(work_list[n]);
                            while(ordered_list.size() > 0)
                            {
                                pOrderly_queue->put_top(ordered_list[0]);
                                ordered_list.erase(ordered_list.begin());
                            }
                            break;
                        }
                    }
                    else
                    {
                        //found spot to insert work list item into queue

                        //put looking at item back in queue
                        pOrderly_queue->put_top(Looking_at);

                        //put work list item on top of the queue
                        pOrderly_queue->put_top(work_list[n]);

                        //put ordered list items on top of the queue
                        while(ordered_list.size() > 0)
                        {
                            Looking_at = ordered_list[0];
                            pOrderly_queue->put_top(Looking_at);
                            ordered_list.erase(ordered_list.begin());
                                    //work_list[n]);
                        }
                        break;
//                        ordered_list.push_back(items<T>());
//                        std::rotate(ordered_list.begin(),ordered_list.end(),ordered_list.end());
//                        ordered_list[0] = Looking_at;
                    }
                }
            }
//        }
    }

    while(pOrderly_queue->pop_top(&Looking_at) == true)
    {
        cout << "ordered queue index =" << Looking_at.index << endl;
        cout << "ordered queue value =" << Looking_at.value << endl;
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

int main() {
//    int verticies = 50;
//    float max_range = 9.5;
//    float density = 0.2;
//    point a, b(2,1), c(0.5,6);
//    Graph * graph = new Graph(verticies, max_range, density);
    const unsigned int STUFF_LEN = 10;
    const unsigned int STUFF_SEED = 4;
    the_stuff * Stuff = new the_stuff(STUFF_LEN,STUFF_SEED);

    cout << "orderly sum: " << Stuff->pDo_Stuff->orderly_sum(4,6) << endl;

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
