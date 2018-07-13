//node_avl.cpp

#pragma once

#include"avl_tree.hpp"

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
