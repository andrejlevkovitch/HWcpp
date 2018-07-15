//stack.hpp

#pragma once

#include<cstddef>
#include<memory>
#include<stdexcept>
#include<iterator>

template<typename W>
class Stack {
    public:
        static const size_t max_size();
    private:
        class Node {
            public:
                std::shared_ptr<Node> previous_;
                W info_;
            public:
                explicit Node (const W & value);
                explicit Node (const W && value);
        };
    private:
        class Iterator : public std::iterator<std::output_iterator_tag, W> {
            friend Stack;
            private:
                std::shared_ptr<Node> pointer_;
            public:
                Iterator ();
                explicit Iterator (const std::shared_ptr<Node> &);
                W & operator*() const;
                W * operator->() const;
                Iterator & operator++();
                bool operator==(const Iterator &) const;
                bool operator!=(const Iterator &) const;
        };
    private:
        std::shared_ptr<Node> head_;
        size_t size_;
    public:
        Stack ();
        Stack (const Stack &);
        Stack & operator=(const Stack &);
        const size_t size() const;
        bool empty() const;
        W & push(const W & value);//generated length error
        W & push(const W && value);//generaded length error
        bool pop();
        W & head() const;//generated domain error

        Iterator begin() const;
        Iterator end() const;

        bool operator!=(const Stack &) const;
        bool operator==(const Stack &) const;

        Stack (const Stack &&) = delete;
        Stack & operator=(const Stack &&) = delete;
    private:
        void rekurs_init(std::shared_ptr<Node>);
};

#include"stack_.hpp"
#include"stack_iterator.hpp"
#include"stack_node.hpp"
