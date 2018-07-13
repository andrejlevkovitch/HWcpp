//avl_tree.hpp

#pragma once

#include<cstddef>
#include<cstdbool>
#include<functional>
#include<memory>
#include<fstream>
#include<cmath>
#include<stdexcept>

#include"stack.hpp"

template<typename T, typename Compare = std::less<T>>
class AVL_tree {
    public:
        static const size_t max_size();
        static const bool LEFT {0};
        static const bool RIGHT {1};
    private:
        class Node {
            private:
                static const short N_NODE {2};
            public:
                std::shared_ptr<Node> child_[N_NODE];
                const T key_;
                signed char balance_;
            public:
                Node (const T & value);
                Node (const T && value);
        };
        struct Step {
            std::shared_ptr<Node> * node;
            bool direction;
            Step (bool d, std::shared_ptr<Node> * const n)
                : node {n}, direction {d} {}
        };
    public:
        class IteratorConst {
            private:
                struct StepI {
                    std::shared_ptr<const Node> node;
                    bool direction;
                    StepI (bool d, std::shared_ptr<const Node> n)
                        : node {n}, direction {d} {}
                };
            private:
                std::shared_ptr<const Node> pointer_;
                Stack<StepI> way_;
            public:
                IteratorConst ();
                IteratorConst (std::shared_ptr<Node> &);
                IteratorConst & operator++();
                IteratorConst & operator--();
                const T & operator*() const;
                const T * operator->() const;
                bool operator==(const IteratorConst &) const;
                bool operator!=(const IteratorConst &) const;
        };
    private:
        std::shared_ptr<Node> root_;
        size_t size_;
        std::shared_ptr<Node> end_;
        const Compare compare_;
    public:
        AVL_tree ();
        size_t size() const;
        bool empty() const;
        bool insert(T &value);//generated length error
        bool insert(T &&value);//generated length error
        bool find(T &value) const;
        bool find(T &&value) const;
        bool erase(T &value);
        bool erase(T &&value);
        Compare key_comp() const;

        const IteratorConst end();
        const IteratorConst begin();

        AVL_tree (const AVL_tree &) = delete;
        AVL_tree (const AVL_tree &&) = delete;
        AVL_tree &operator=(const AVL_tree &) = delete;
        AVL_tree &operator=(const AVL_tree &&) = delete;
    private:
        void turn(std::shared_ptr<Node> * node);
};

#include"avl_tree.cpp"
#include"node_avl.cpp"
#include"iterator.cpp"
