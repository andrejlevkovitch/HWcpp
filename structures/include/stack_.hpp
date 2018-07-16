//stack_.hpp

#pragma once

#include"stack.hpp"

template<typename W>
size_t Stack<W>::max_size()
{
    static const size_t retvalue {1000};
    return retvalue;
}


template<typename W>
Stack<W>::Stack () :  head_ {nullptr}, size_ {0}
{
}

template<typename W>
void Stack<W>::rekurs_init(std::shared_ptr<Node> in)
{
    if (in) {
        rekurs_init(in->previous_);
        push(in->info_);
    }
    return;
}

template<typename W>
Stack<W>::Stack (const Stack & in) : size_ {0}
{
    if (!in.empty()) {
        rekurs_init(in.head_);
    }
}

template<typename W>
Stack<W> & Stack<W>::operator=(const Stack & in)
{
    if (*this != in) {
        while (!empty()) {
            pop();
        }
        if (!in.empty()) {
            rekurs_init(in.head_);
        }
    }
    return *this;
}

template<typename W>
Stack<W>::Stack (const Stack && in) : size_ {0}
{
    if (!in.empty()) {
        rekurs_init(in.head_);
    }
}

template<typename W>
Stack<W> & Stack<W>::operator=(const Stack && in)
{
    if (*this != in) {
        while (!empty()) {
            pop();
        }
        if (!in.empty()) {
            rekurs_init(in.head_);
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

template<typename W>
typename Stack<W>::Iterator Stack<W>::begin() const
{
    Iterator begin_node {head_};
    return begin_node;
}

template<typename W>
typename Stack<W>::Iterator Stack<W>::end() const
{
    Iterator void_end_node;
    void_end_node.pointer_ = nullptr;
    return void_end_node;
}


template<typename W>
bool Stack<W>::operator!=(const Stack & rhs) const
{
    return (head_ != rhs.head_) ? true : false;
}

template<typename W>
bool Stack<W>::operator==(const Stack & rhs) const
{
    return (head_ == rhs.head_) ? true : false;
}
