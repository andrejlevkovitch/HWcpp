//avl_tree.hpp

#pragma once

#include<cstddef>
#include<cstdbool>
#include<memory>
#include<stdexcept>
#include<iterator>

#include"stack.hpp"

template<typename T, typename Compare = std::less<T>>
class AVL_tree {
    public:
        static const size_t max_size();
        static const bool LEFT {0};
        static const bool RIGHT {1};
    private:
        class Node {
            friend AVL_tree;
            private:
                static const short N_NODE {2};
            private:
                std::shared_ptr<Node> child_[N_NODE];
                const T key_;
                signed char balance_;
            public:
                Node ();
                explicit Node (const T & value);
                explicit Node (const T && value);
        };
    private:
        struct Step {
            std::shared_ptr<Node> * node;
            bool direction;
            Step (bool d, std::shared_ptr<Node> * const n)
                : node {n}, direction {d} {}
        };
    public:
        class IteratorBi : public std::iterator<
                              std::bidirectional_iterator_tag, T> {
            friend AVL_tree;
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
                IteratorBi ();
                explicit IteratorBi (std::shared_ptr<Node> &);
                virtual IteratorBi & operator++();
                virtual IteratorBi & operator--();
                const T & operator*() const;
                const T * operator->() const;
                bool operator==(const IteratorBi &) const;
                bool operator!=(const IteratorBi &) const;
            private:
                IteratorBi & first();
                IteratorBi & last();
        };
        class IteratorBiRev : public IteratorBi {
            public:
                IteratorBiRev ();
                explicit IteratorBiRev (std::shared_ptr<Node> &);
                virtual IteratorBiRev & operator++();
                virtual IteratorBiRev & operator--();
        };
    private:
        std::shared_ptr<Node> root_;
        size_t size_;
        std::shared_ptr<Node> void_end_node_;
        std::shared_ptr<Node> void_begin_node_;
        const Compare compare_;
    public:
        AVL_tree ();
        const size_t size() const;
        bool empty() const;
        bool insert(const T & value);//generated length error
        bool insert(const T && value);//generated length error
        bool find(const T & value) const;
        bool find(const T && value) const;
        bool erase(const T & value);
        bool erase(const T && value);
        Compare key_comp() const;

        const IteratorBi end();
        const IteratorBi begin();
        const IteratorBiRev rend();
        const IteratorBiRev rbegin();

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
