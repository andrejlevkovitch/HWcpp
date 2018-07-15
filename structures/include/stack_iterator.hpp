//stack_iterator.hpp

#pragma once

#include"stack.hpp"

template<typename W>
Stack<W>::Iterator::Iterator ()
{
}

template<typename W>
W & Stack<W>::Iterator::operator*() const
{
    return pointer_->info_;
}

template<typename W>
W * Stack<W>::Iterator::operator->() const
{
    return & pointer_->info_;
}

template<typename W>
typename Stack<W>::Iterator & Stack<W>::Iterator::operator++()
{
    pointer_ = pointer_->previous_;
    return *this;
}

template<typename W>
bool Stack<W>::Iterator::operator==(const Iterator & rhs) const
{
    return (pointer_ == rhs.pointer_) ? true : false;
}

template<typename W>
bool Stack<W>::Iterator::operator!=(const Iterator & rhs) const
{
    return (pointer_ != rhs.pointer_) ? true : false;
}
