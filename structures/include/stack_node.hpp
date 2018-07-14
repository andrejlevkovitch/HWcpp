//stack_node.hpp

#pragma once

#include"stack.hpp"

template<typename W>
Stack<W>::Node::Node (const W & value) : previous_ {nullptr}, info_ {value}
{
}

template<typename W>
Stack<W>::Node::Node (const W && value) : previous_ {nullptr}, info_ {value}
{
}
