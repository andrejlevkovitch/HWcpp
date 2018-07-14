//avl_node.hpp

#pragma once

#include"avl.hpp"

template<typename T, typename Compare>
AVL_tree<T, Compare>::Node::Node () :  key_ {}
{
}

template<typename T, typename Compare>
AVL_tree<T, Compare>::Node::Node (const T & value) :  key_ {value}, balance_ {0}
{
    for (int i {}; i < N_NODE; ++i) {
        child_[i] = nullptr;
    }
}

template<typename T, typename Compare>
AVL_tree<T, Compare>::Node::Node (const T && value) :  key_ {value}, balance_ {0}
{
    for (int i {}; i < N_NODE; ++i) {
        child_[i] = nullptr;
    }
}
