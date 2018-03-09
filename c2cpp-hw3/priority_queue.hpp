/*
 * priority_queue.hpp
 *
 *  Created on: Mar 4, 2018
 *      Author: Matt B
 */

#ifndef PRIORITY_QUEUE_HPP_
#define PRIORITY_QUEUE_HPP_

#include <iostream>
#include <vector>
#include <list>

using namespace std;



template <typename T1, typename T2>
class Priority_Queue
{
public:
    Priority_Queue(){}
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
