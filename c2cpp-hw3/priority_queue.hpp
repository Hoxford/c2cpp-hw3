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



template <class T1, class T2>
class Priority_Queue
{
public:
    Priority_Queue(T1 index, T2 start);
    ~Priority_Queue(){}
    //chgPrioirity(PQ, priority): changes the priority (node value) of queue element.
    bool chgPrioirity(int priority);
    //removes the top element of the queue.
    unsigned int minPrioirty();
    //does the queue contain queue_element.
    bool contains(unsigned int queue_element);
    //insert queue_element into queue
    bool Insert(unsigned int queue_element);
    //returns the top element of the queue.
    unsigned int top();
    //return the number of queue_elements.
    unsigned int size();
};

template <typename T1, typename T2>
inline bool Priority_Queue<T1, T2>::chgPrioirity(int priority)
{
    return false;
}

template <typename T1, typename T2>
inline unsigned int Priority_Queue<T1, T2>::minPrioirty()
{
    return false;
}

template <typename T1, typename T2>
inline bool Priority_Queue<T1, T2>::contains(unsigned int queue_element)
{
    return false;
}

template <typename T1, typename T2>
inline bool Priority_Queue<T1, T2>::Insert(unsigned int queue_element)
{
    return false;
}

template <typename T1, typename T2>
inline unsigned int Priority_Queue<T1, T2>::top()
{
    return false;
}

template <typename T1, typename T2>
inline unsigned int Priority_Queue<T1, T2>::size()
{
    return false;
}

#endif /* PRIORITY_QUEUE_HPP_ */
