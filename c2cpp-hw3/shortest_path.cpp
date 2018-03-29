/*
 * shortest_path.cpp
 *
 *  Created on: Mar 8, 2018
 *      Author: storm
 */

#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <algorithm>

#include "priority_queue.hpp"
#include "shortest_path.hpp"

using namespace std;

//template<typename Edge_Type>
//struct Neighbor_Node
//{
//    unsigned int neighbor_node_id;
//    Edge_Type edge_distance;
//};

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//! Public Functions
//!
template <class E>
#if defined(DEBUG)
Shortest_Path<E>::Shortest_Path(Graph * graph, unsigned int start, unsigned int end, const char* calling_fcn)
{
    cout << "Shortest_Path constructor called by " << calling_fcn << "()" << endl;
    cout << (__PRETTY_FUNCTION__) << endl;
#else
Shortest_Path<E>::Shortest_Path(Graph * graph, unsigned int start, unsigned int end)
{
#endif
    unsigned int num_nodes;
    unsigned int current_node = start;
    start_ = start;
    end_ = end;
    graph_ = graph;
    cost_ = 0;
    E edge = 0;
    num_nodes = graph_->get_num_nodes();

//    Priority_Queue<E, neighbor_node> * queue = new Priority_Queue<E, neighbor_node>();
    shortest_path_.push_back(start_);

    if(graph->get_edge_value(start_, end_) > 0)
    {
        shortest_path_.push_back(end_);
        cout << "Start and end are neighbors." << endl;
    }
    else if(is_node_dead_end(start_))
    {
        cost_ = 0;
        cout << "Start node is a dead end." << endl;
    }
    else if(is_node_dead_end(end_))
    {
        cost_ = 0;
        cout << "End node is a dead end." << endl;
    }
    else
    {
        while(1)
        {
            unsigned int prev_path_len = path_len();
            Priority_Queue<E, neighbor_node> * queue = new Priority_Queue<E, neighbor_node>();
            //build the priority queue of possible nodes and edge values to jump to
            for(unsigned int i = 0; i < num_nodes; i++)
            {
                if(true == can_node_be_considered(i, current_node))
                {
                    edge = graph->get_edge_value(current_node, i);
                    if((edge > 0)&&(i != current_node))
                    {
                        if(i == end)
                        {
                            shortest_path_.push_back(end_);
                            cout << "shortest path found!: ";
                            for(list<unsigned int>::const_iterator iterator = shortest_path_.begin(), end = shortest_path_.end(); iterator != end; ++iterator)
                            {
                                cout << *iterator << ", ";
                            }
                            cout << endl;
                            return;
                        }
                        neighbor_node Node(edge,i);
                        queue->put(edge, Node);
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    if((num_nodes == (i+1)) && (0 == queue->size()))
                    {
                        //if all nodes were checked then start again
                        //save the path
                        save_attempted_path();
                        //start over
                        path_reset();
                        current_node = start_;
                        shortest_path_.push_back(start_);
                        break;
                    }
                }
            }

            //search the queue for the next possible node to jump to.
            unsigned int queue_len = queue->size();
            for(unsigned int i = 0; i < queue_len;)
            {
                neighbor_node Neighbor;
                queue->pop_front(&Neighbor);
                //check if neighbor node is a dead end
                if(false == is_node_dead_end(Neighbor.neighbor_, current_node))
                {
                    //check if the node can be considered
                    if(true == can_node_be_considered(Neighbor.neighbor_, current_node))
                    {
                        //check if the path was already attempted
                        if(false == was_path_attempted(Neighbor.neighbor_))
                        {
                            add_node_to_path(Neighbor.neighbor_);
                            current_node = Neighbor.neighbor_;
                            break;
                        }
                    }
                }

                i++;

                //check if the end of the queue was reached before finding a viable neighbor
                if(i == queue_len)
                {
                    //save the path
                    save_attempted_path();
                    //start over
                    path_reset();
                    current_node = start_;
                    shortest_path_.push_back(start_);
                    break;
                }
            }

            delete queue;

            //check if no more paths could be found by checking if the path length increased
            if(prev_path_len == path_len())
            {
                //no more paths could be found
#if defined(DEBUG)
                cout << "No connection between " << start_ << " and " << end_ << " could be found." << endl;
#endif
                return;
            }
#if defined(DEBUG)
            cout << "current working path: ";
            for(list<unsigned int>::const_iterator iterator = shortest_path_.begin(), end = shortest_path_.end(); iterator != end; ++iterator)
            {
                cout << *iterator << ", ";
            }
            cout << endl;
#endif
        }
    }
}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//! Private functions
//!
template <class E>
bool Shortest_Path<E>::is_node_dead_end(unsigned int node, unsigned int previous_node)
{
    bool is_dead_end = true;
    unsigned int num_node_possible_connections = graph_->get_num_nodes() - 1;

    for(unsigned int i = 0; (i < num_node_possible_connections)&&(is_dead_end == true); i++)
    {
        if(graph_->get_edge_value(node, i) > 0)
        {
            if(i == previous_node)
            {
                continue;
            }
            else
            {
                is_dead_end = false;
                break;
            }
        }
    }

    if(true == is_dead_end)
    {
        eliminate_node(node);
    }
    return is_dead_end;
}

template <class E>
bool Shortest_Path<E>::can_node_be_considered(unsigned int node_to_check, unsigned int node_to_check_from)
{
    for(list<unsigned int>::const_iterator iterator = eliminated_nodes_.begin(), end = eliminated_nodes_.end(); iterator != end; ++iterator)
    {
        if(node_to_check == *iterator)
        {
            return false;
        }
    }

    if(true == is_node_in_path(node_to_check))
    {
        return false;
    }

    if(0 >= graph_->get_edge_value(node_to_check_from, node_to_check))
    {
        return false;
    }

    return true;
}

template <class E>
bool Shortest_Path<E>::was_path_attempted(unsigned int possible_end)
{
    unsigned int attempted_paths_size = attempted_paths_.size();
    if(0 == attempted_paths_size)
    {
        return false;
    }
    else
    {
        for(list<list<unsigned int>>::const_iterator iterator = attempted_paths_.begin(), end = attempted_paths_.end(); iterator != end; ++iterator)
        {
            list<unsigned int> previous_path = *iterator;
            list<unsigned int> potential_shortest_path_ = shortest_path_;
            potential_shortest_path_.push_back(possible_end);
            bool match = true;
            if(previous_path.size() == shortest_path_.size() + 1)
            {
                for(
                    list<unsigned int>::const_iterator previous_iterator = previous_path.begin(),
                    previous_end = previous_path.end(),
                    shortest_iterator = potential_shortest_path_.begin(),
                    shortest_end = potential_shortest_path_.end();
                    (previous_iterator != previous_end)&&(shortest_iterator != shortest_end);
                    previous_iterator++,
                    shortest_iterator++
                    )
                {
                    if(*previous_iterator != *shortest_iterator)
                    {
                        match = false;
                        break;
                    }
                }
                if(match == true)
                {
                    return true;
                }
            }
        }
        return false;
    }
    return true;
}

template class Shortest_Path<float>;
