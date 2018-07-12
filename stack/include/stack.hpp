//stack.hpp

#pragma once

#include<cstddef>
#include<memory>

template<typename T>
class Stack {
    private:
        class Node {
            public:
                T info_;
                std::unique_ptr<Node> prev_;
                Node (const T &);
                ~Node();
        };
    public:
        class Iterator {
            private:
                Node * point_;
            public:
                Iterator (Node * const alfa) : point_ {alfa} {};
                Iterator () : point_ {nullptr} {};
                T & operator*() const {return point_->info_;};
                T * operator->() const {return &point_->info_;};
                Iterator & operator++ () {point_ = &(*point_->prev_); return *this;};
                Iterator & operator=(Node * const a) {this->point_ = a;return *this;};
                bool operator!=(const Iterator & rhs) const {return (point_ != rhs.point_) ? true : false;};
                bool operator==(const Iterator & rhs) const {return (point_ == rhs.point_) ? true : false;};
        };
    public:
        static const size_t max_size();
    private:
        std::unique_ptr<Node> head_;
        size_t size_;
    public:
        Stack ();
        ~Stack();
        void push(const T &);
        void pop();
        const T & head() const;
        const size_t size() const;
        const Iterator & begin() const;
        const Iterator & end() const;
};

template<typename T>
Stack<T>::Node::Node (const T & value) : info_ {value}, prev_ {nullptr}
{
}

template<typename T>
Stack<T>::Node::~Node()
{
}

template<typename T>
const typename Stack<T>::Iterator & Stack<T>::begin() const
{
    static Iterator iter;
    iter = &(*head_);
    return iter;
}

template<typename T>
const typename Stack<T>::Iterator & Stack<T>::end() const
{
    static const Iterator iter = nullptr;
    return iter;
}

template<typename T>
const size_t Stack<T>::max_size()
{
    static const size_t max_size {1000};
    return max_size;
}

template<typename T>
const size_t Stack<T>::size() const
{
    return size_;
}

template<typename T>
Stack<T>::Stack () : head_ {nullptr}, size_ {}
{
}

template<typename T>
Stack<T>::~Stack()
{
}

template<typename T>
void Stack<T>::push(const T & value)
{
    std::unique_ptr<Node> temp {std::make_unique<Node>(value)};
    temp->prev_ = std::move(head_);
    head_ = std::move(temp);
    ++size_;
    return;
}

template<typename T>
void Stack<T>::pop()
{
    if (head_) {
        auto temp {std::move(head_)};
        head_ = std::move(temp->prev_);
        --size_;
    }
    return;
}

template<typename T>
const T & Stack<T>::head() const
{
    return head_->info_;
}
