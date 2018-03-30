/*
 * priority_queue.hpp
 *
 *  Created on: Mar 4, 2018
 *      Author: Matt B
 */

/******************************************************************************
 * One important consideration for the Graph class is how to represent the
 * graph as a member ADT. Two basic implementations are generally considered:
 * adjacency list and adjacency matrix depending on the relative edge density.
 * For sparse graphs, the list approach is typically more efficient, but for
 * dense graphs, the matrix approach can be more efficient (reference an
 * Algorithm’s source for space and time analysis). Note in some cases such as
 * add(G, x, y) you may also want to have the edge carry along its cost.
 * Another approach could be to use (x, y) to index a cost stored in an
 * associated array or map.
 *
 * The value of the PriorityQueue is to always have access to the vertex with
 * the next shortest link in the shortest path calculation at the top of the
 * queue. A typically implementation is a minHeap:
 *
 * Class PriorityQueue
 * {
 * chgPrioirity(PQ, priority): changes the priority (node value) of queue element.
 * minPrioirty(PQ): removes the top element of the queue.
 * contains(PQ, queue_element): does the queue contain queue_element.
 * Insert(PQ, queue_element): insert queue_element into queue
 * top(PQ):returns the top element of the queue.
 * size(PQ): return the number of queue_elements.
 * }
 */

#ifndef PRIORITY_QUEUE_HPP_
#define PRIORITY_QUEUE_HPP_

#include <iostream>
#include <vector>
#include <list>

using namespace std;

template <class P, class I>
class Priority_Queue
{
public:
#if (defined(DEBUG) && defined(CONSTRUCTOR_TRACING))
    Priority_Queue(const char* calling_fcn = __builtin_FUNCTION())
    {
        cout << "Priority_Queue constructor called by " << calling_fcn << "()" << endl;
        cout << (__PRETTY_FUNCTION__) << endl;
#else
    Priority_Queue()
    {
#endif
        queue_len_ = 0;
    }
    ~Priority_Queue(){priority_queue.clear();}

    //todo: Priority_Queue function comment descriptions

    //chgPrioirity(PQ, priority): changes the priority (node value) of queue element.
    bool chgPrioirity(int priority);


    //put the item to the front of the queue
    bool put_front(I item)
    {
        //increase queue length
        queue_len_++;
        //create new queue element using the passed in item to queue
        queue_element * pElement = new queue_element(item);
        //put the queue element to the front of the queue vector
        priority_queue.insert(priority_queue.begin(), *pElement);
        delete pElement;

        return true;
    }

    bool put(P compare, I item)
    {
        //create new queue element using the passed in item to queue
        queue_element * pElement = new queue_element(compare, item);
        if(0 == queue_len_)
        {
            priority_queue.push_back(*pElement);
        }
        else
        {
            for(unsigned int i = 0; i < queue_len_;)
            {
                if(priority_queue[i].compare_ >= compare)
                {
                    priority_queue.insert(priority_queue.begin() + i,*pElement);
                    break;
                }

                i++;

                if(i == queue_len_)
                {
                    priority_queue.insert(priority_queue.begin() + i,*pElement);
                    break;
                }
            }
        }

        queue_len_++;
        delete pElement;
        return true;
    }

    //put the item to the back of the queue
    bool put_back(I item)
    {
        queue_len_++;
        priority_queue.push_back(item);

        return true;
    }

    //puts the higher priority item into the lower priority items spot and pushes back all lower priorities
    //todo: determine if this is needed anymore and if it can be eliminated
    bool put_insert(I higher_priority_item, I lower_priority_item)
    {
//        queue_len_++;
        //find lower_priority_item's position in the queue

        //push the queue back at the lower_priority_item's position creating an empty allocation for the higher_priority_item

        //put higher_priority_item into new allocation

        return false;
    }

    //pop the front(aka top) item off the queue. unsigned int minPrioirty();
    bool pop_front(I * item)
    {
        if(queue_len_ > 0)
        {
            *item = priority_queue[0].item_;
            queue_len_--;
            if(queue_len_ == 0)
            {
                priority_queue.clear();
            }
            else
            {
                priority_queue.erase(priority_queue.begin());
            }

            return true;
        }
        return false;
    }

    //pop the back item off the queue
    bool pop_back(I * item)
    {
        if(queue_len_ > 0)
        {
            *item = priority_queue[(queue_len_ - 1)].item_;
            queue_len_--;
            //check if queue is used up
            if(queue_len_ == 0)
            {
                //queue is empty, clear the queue vector completly
                priority_queue.clear();
            }
            else
            {
                //remove the back item off of the queue
                priority_queue.erase(priority_queue.begin() + queue_len_);
            }
            return true;
        }
        return false;
    }

    //pop an item from the queue at the specific priority
    bool pop_from(P priority, I * item)
    {
        return false;
    }

    //read an item from the queue at a specific location. Will not remove the item.
    // \param I * prev_item - NULL: read the front item from the queue
    //                      - read the item after prev_item
    bool read_from(const I * prev_item, I * item)
    {
        *item = priority_queue[(queue_len_ - 1)].item_;
        return true;
    }

    //does the queue contain queue_element.
    bool contains(unsigned int queue_element){return false;}
    //insert queue_element into queue
    bool Insert(unsigned int queue_element){return false;}
    //returns the top element of the queue.
    unsigned int top(){return 0;}
    //return the number of queue_elements.
    unsigned int size(){return queue_len_;}
private:
    class queue_element
    {
    public:
        queue_element(P compare, I item)
        {
            item_ = item;
            compare_ = compare;
        }
        queue_element(I item)
        {
            item_ = item;
            compare_ = 0;
        }
        queue_element(){}
        ~queue_element(){}
        I item_;
        P compare_;
    };
    unsigned int queue_len_;
    vector<queue_element>priority_queue;
};

//template class Priority_Queue<unsigned int, unsigned int>;
//template class Priority_Queue<int, int>;

#endif /* PRIORITY_QUEUE_HPP_ */
