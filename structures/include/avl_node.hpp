//avl_node.hpp

#pragma once

#include"avl.hpp"

template<typename T, typename Compare>
AVL_tree<T, Compare>::Node::Node () :
    key_ {}, counter_ {}, balance_ {}
{
}

template<typename T, typename Compare>
AVL_tree<T, Compare>::Node::Node (const T & value) :
    key_ {value}, counter_ {1}, balance_ {}
{
    for (int i {}; i < N_NODE; ++i) {
        child_[i] = nullptr;
    }
}

template<typename T, typename Compare>
AVL_tree<T, Compare>::Node::Node (const T && value) :
    key_ {value}, counter_ {1}, balance_ {}
{
    for (int i {}; i < N_NODE; ++i) {
        child_[i] = nullptr;
    }
}
