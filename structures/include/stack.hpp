//stack.hpp

#pragma once

#include<cstddef>
#include<memory>
#include<stdexcept>

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
                Node (const W & value);
        };
    private:
        std::shared_ptr<Node> head_;
        size_t size_;
    public:
        Stack ();
        Stack (const Stack &);
        Stack & operator=(const Stack &);
        size_t size() const;
        bool empty() const;
        W & push(const W & value);//generated length error
        W & push(const W && value);//generaded length error
        bool pop();
        W & head() const;//generated domain error

        Stack (const Stack &&) = delete;
        Stack & operator=(const Stack &&) = delete;
};

#include"stack.cpp"
