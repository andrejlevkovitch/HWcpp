//stack.hpp

#pragma once

#include<cstddef>
#include<memory>
#include<stdexcept>

template<typename W>
class Stack {
    public:
        static size_t max_size();
    private:
        class Node {
            public:
                std::shared_ptr<Node> previous_;
                W info_;
            public:
                Node (W &value);
                ~Node();
        };
    private:
        std::shared_ptr<Node> head_;
        size_t size_;
    public:
        Stack ();
        ~Stack();
        size_t size() const;
        W &push(W &value);//generated length error
        W &push(W &&value);//generaded length error
        bool pop();
        W &head();//generated domain error

        Stack (Stack &) = delete;
        Stack (Stack &&) = delete;
        Stack &operator=(Stack &) = delete;
        Stack &operator=(Stack &&) = delete;
};

template<typename W>
Stack<W>::Node::Node (W &value) : previous_ {nullptr}, info_ {value}
{
}

template<typename W>
Stack<W>::Node::~Node()
{
}

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
Stack<W>::~Stack()
{
}

template<typename W>
size_t Stack<W>::size() const
{
    return size_;
}

template<typename W>
W &Stack<W>::push(W &value)
{
    if (size_ < max_size()) {
        size_++;
        auto previous = head_;
        head_ = std::make_shared<Node>(Node {value});
        head_->previous_ = previous;
    }
    else {
        throw std::length_error("this is more then max size");
    }
    return head_->info_;
}

template<typename W>
W &Stack<W>::push(W &&value)
{
    if (size_ < max_size()) {
        size_++;
        auto previous = head_;
        head_ = std::make_shared<Node>(Node {value});
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
W &Stack<W>::head()
{
    if (!head_) {
        throw std::domain_error ("can't dereferention nullptr");
    }
    return head_->info_;
}
