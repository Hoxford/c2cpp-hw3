//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!
//! shortest_path.hpp
//!
//!  Created on: Mar 4, 2018
//!      Author: Matt B
//!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef SHORTEST_PATH_HPP_
#define SHORTEST_PATH_HPP_

#include <list>
#include "graph.hpp"
#include "priority_queue.hpp"

using namespace std;

enum class Path_Type : int
{
    eSHORTEST,
    eLONGEST,
    NUM_PATH_TYPES
};

template <class E>
class Shortest_Path
{
public:
    //the constructor will determine the shortest path between start and end
#if (defined(DEBUG) && defined(CONSTRUCTOR_TRACING))
    Shortest_Path(Graph * graph, unsigned int start, unsigned int end, const char* calling_fcn = __builtin_FUNCTION());
#else
    Shortest_Path(Graph * graph, unsigned int start, unsigned int end);
#endif
    ~Shortest_Path()
    {
        shortest_path_.clear();
        attempted_paths_.clear();
        visited_nodes_.clear();
        eliminated_nodes_.clear();
    }

    //todo: Shortest_Path function comment descriptions

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //! path
    //!
    //! \brief returns the path requested by the parameter
    //!
    //! \param
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    inline list<unsigned int> *path(Path_Type eType = Path_Type::eSHORTEST)
    {
        //todo: have a pointer to path to fill as a parameter, and return error code instead
        //todo FEATURE: return request path type
        return &shortest_path_;
    }

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //! path_cost
    //!
    //! \brief  returns the path cost requested by the parameter.
    //!
    //! \param
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    inline E path_cost(Path_Type eType = Path_Type::eSHORTEST)
    {
        //todo FEATURE: return request path cost type
        return cost_;
    }

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //! path_len
    //!
    //! \brief  returns the number of nodes in the path requested by the parameter.
    //!
    //! \param
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    inline unsigned int path_len(Path_Type eType = Path_Type::eSHORTEST)
    {
        //todo FEATURE: return requested path size  type
        return shortest_path_.size();
    }

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //! path_exists
    //!
    //! \brief  returns if a path exists between the start and end nodes
    //!
    //! \param
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    inline bool path_exists()
    {
        return ((0 == cost_)? false:true);
    }

private:
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //! is_node_dead_end
    //!
    //! \brief checks if the node is a dead end and/or isolated
    //!
    //! \param [in] unsigned int node: node to check if it is a dead end or isolated.
    //! \param [in] unsigned int previous_node(optional): Previous node that
    //!               this check is being done with respect to. It is optional
    //!               and helps with context in terms of if the node is a dead
    //!               end or completely isolated.
    //!
    //! \return true    node is a dead end or isolated.
    //! \return false   node is not a dead end and has 1 or more neighbor nodes
    //!                 other then the previous node.
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    bool is_node_dead_end(unsigned int node, unsigned int previous_node = 0);

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //! can_node_be_considered
    //!
    //! \brief As the path is being created, possible nodes that had an edge
    //!        distance greater then the one chosen will be remembered. When a
    //!        new node edge is being evaluated for the next possible path link,
    //!        this function will determine if the next node was previously
    //!        considered and therefore not a valid candidate.
    //!
    //! \param
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    bool can_node_be_considered(unsigned int node_to_check, unsigned int node_to_check_from);

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //! is_node_in_path
    //!
    //! \brief
    //!
    //! \param
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    inline bool is_node_in_path(unsigned int node)
    {
        for(list<unsigned int>::const_iterator iterator = shortest_path_.begin(), end = shortest_path_.end(); iterator != end; ++iterator)
        {
            if(node == *iterator)
            {
                return true;
            }
        }
        return false;
    }

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //! eliminate_node
    //!
    //! \brief
    //!
    //! \param
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    inline void eliminate_node(unsigned int node)
    {
        //make sure the node is not already in the eliminated list
        for(list<unsigned int>::const_iterator iterator = eliminated_nodes_.begin(), end = eliminated_nodes_.end(); iterator != end; ++iterator)
        {
            if(node == *iterator)
            {
                return;
            }
        }

        //add the node to the eliminated list
        eliminated_nodes_.push_back(node);
    }

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //! add_node_to_path
    //!
    //! \brief
    //!
    //! \param
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    inline void add_node_to_path(unsigned int node)
    {
        shortest_path_.push_back(node);
    }

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //! is_node_in_path
    //!
    //! \brief
    //!
    //! \param
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    inline void save_attempted_path()
    {
#if defined(DEBUG)
        cout << "Path saved: ";
        for(list<unsigned int>::const_iterator iterator = shortest_path_.begin(), end = shortest_path_.end(); iterator != end; ++iterator)
        {
            cout << *iterator << ", ";
        }
        cout << endl;
#endif
        attempted_paths_.push_back(shortest_path_);
        queue_attempted_paths_.put(shortest_path_.size(), shortest_path_);
    }

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //! path_reset
    //!
    //! \brief
    //!
    //! \param
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    inline void path_reset()
    {
        shortest_path_.clear();
        visited_nodes_.clear();
//        eliminated_nodes_.clear();
        cost_ = 0;
    }

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //! was_path_attempted
    //!
    //! \brief
    //!
    //! \param
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    bool was_path_attempted(unsigned int possible_end);

    E calculate_cost(list<unsigned int> * pPath)
    {
        assert(pPath != NULL);
        if(1 == pPath->size()){return 0;}

        E calculated_cost = 0;
        unsigned int node_a, node_b;
        node_a = node_b = 0;
        for(list<unsigned int>::const_iterator iterator = pPath->begin(), end = pPath->end(); iterator != end;)// ++iterator)
        {
            node_a = *iterator;
            ++iterator;
            if(iterator == end){break;}
            node_b = *iterator;
            calculated_cost += graph_->get_edge_value(node_a, node_b);
        }
        return calculated_cost;
    }

    class neighbor_node
    {
    public:
        neighbor_node(E edge, unsigned int neighbor)
        {
            edge_ = edge;
            neighbor_ = neighbor;
        }
        neighbor_node()
        {
            edge_= 0;
            neighbor_ = 0;
        }
        E edge_;
        unsigned int neighbor_;
    };

    list<unsigned int> shortest_path_;
    list<list<unsigned int>> attempted_paths_;
    Priority_Queue<E, list<unsigned int>> queue_attempted_paths_;
    list<unsigned int> visited_nodes_;
    list<unsigned int> eliminated_nodes_;
    E cost_;
    unsigned int start_;
    unsigned int end_;
    Graph * graph_;
};

#endif /* SHORTEST_PATH_HPP_ */
