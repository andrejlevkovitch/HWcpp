//stack.cpp

#pragma once

#include"stack.hpp"

template<typename W>
const size_t Stack<W>::max_size()
{
    static const size_t retvalue {1000};
    return retvalue;
}


template<typename W>
Stack<W>::Node::Node (const W &value) : previous_ {nullptr}, info_ {value}
{
}


template<typename W>
Stack<W>::Stack () :  head_ {nullptr}, size_ {0}
{
}

template<typename W>
Stack<W>::Stack (const Stack & in) : size_ {in.size_}
{
    if (!in.empty()) {
        Stack<W> temp;
        for (auto point {in.head_};
                point;
                point = point->previous_) {
            temp.push(point->info_);
        }
        while (!temp.empty()) {
            push(temp.head());
            temp.pop();
        }
    }
}

template<typename W>
Stack<W> & Stack<W>::operator=(const Stack & in)
{
    size_ = in.size_;
    if (!in.empty()) {
        Stack<W> temp;
        for (auto point {in.head_};
                point;
                point = point->previous_) {
            temp.push(point->info_);
        }
        while (!temp.empty()) {
            push(temp.head());
            temp.pop();
        }
    }
    return *this;
}


template<typename W>
size_t Stack<W>::size() const
{
    return size_;
}

template<typename W>
bool Stack<W>::empty() const
{
    return (head_) ? false : true;
}

template<typename W>
W &Stack<W>::push(const W &value)
{
    if (size_ < max_size()) {
        size_++;
        auto previous = head_;
        head_ = std::make_shared<Node>(value);
        head_->previous_ = previous;
    }
    else {
        throw std::length_error("this is more then max size");
    }
    return head_->info_;
}

template<typename W>
W & Stack<W>::push(const W &&value)
{
    if (size_ < max_size()) {
        size_++;
        auto previous = head_;
        head_ = std::make_shared<Node>(value);
        head_->previous_ = previous;
    }
    else {
        throw std::length_error("this is more then max size");
    }
    return head_->info_;
}

template<typename W>
bool Stack<W>::pop()
{
    if (head_) {
        size_--;
        auto pop = head_;
        head_ = head_->previous_;
        pop.reset();
        return true;
    }
    return false;
}

template<typename W>
W &Stack<W>::head() const
{
    if (!head_) {
        throw std::domain_error ("can't dereferention nullptr");
    }
    return head_->info_;
}
