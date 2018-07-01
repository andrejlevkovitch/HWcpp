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
        static const size_t &max_size();
    public:
        class Node {
            private:
                static const short N_NODE {2};
            public:
                std::shared_ptr<Node> child_[N_NODE];
                signed char balance_;
                T info_;
            public:
                Node (T &value);
                ~Node();
        };
        struct Way {
            bool direction;
            std::shared_ptr<Node> *node;
            Way (bool d, decltype (node) n) : direction {d}, node {n} {}
        };
    private:
        std::shared_ptr<Node> root_;
        size_t size_;
        const Compare compare_;
    public:
        AVL_tree ();
        ~AVL_tree();
        size_t size() const;
        bool insert(T &value);//generated length error
        bool insert(T &&value);//generated length error
        bool find(T &value) const;
        bool find(T &&value) const;
        bool erase(T &value);
        bool erase(T &&value);
        template<typename C>
            friend std::ofstream &operator<<(std::ofstream &, const C &);
        template<typename C>
            friend void walk(std::ofstream &, const C);
        auto get_root() const -> const decltype(root_);
        Compare key_comp() const;

        AVL_tree (AVL_tree &) = delete;
        AVL_tree (AVL_tree &&) = delete;
        AVL_tree &operator=(AVL_tree &) = delete;
        AVL_tree &operator=(AVL_tree &&) = delete;
    private:
        void turn(decltype(root_) *node);
};

template<typename T, typename Compare>
const size_t &AVL_tree<T, Compare>::max_size()
{
    static const size_t retvalue {1000000};
    return retvalue;
}

template<typename T, typename Compare>
AVL_tree<T, Compare>::Node::Node (T &value) : balance_ {0}, info_ {value}
{
    for (int i {}; i < N_NODE; ++i) {
        child_[i] = nullptr;
    }
}

template<typename T, typename Compare>
AVL_tree<T, Compare>::Node::~Node()
{
}

template<typename T, typename Compare>
size_t AVL_tree<T, Compare>::size() const
{
    return size_;
}

template<typename T, typename Compare>
AVL_tree<T, Compare>::AVL_tree () : root_ {nullptr}, size_ {0}
{
}

template<typename T, typename Compare>
AVL_tree<T, Compare>::~AVL_tree()
{
}

template<typename T, typename Compare>
bool AVL_tree<T, Compare>::insert(T &value)
{
    if (size_ >= max_size()) {
        throw std::length_error("more than max size");
    }

    auto in_node{root_};
    auto q_node{&root_};
    Stack<Way> stack;
    for(;;) {
        if (!in_node) {
            in_node = *q_node = std::make_shared<Node>(Node{value});
            break;
        }
        else {
            if (in_node->info_ == value) {
                return false;
            }
            else {
                stack.push(Way {compare_(in_node->info_, value), q_node});
                q_node = &in_node->child_[stack.head().direction];
                in_node = *q_node;
            }
        }
    }

    if (in_node && stack.size()) {
        while (stack.size()) {
            if ((*stack.head().node)->balance_) {
                (*stack.head().node)->balance_ = (stack.head().direction) ? 
                    (*stack.head().node)->balance_ - 1 :
                    (*stack.head().node)->balance_ + 1;
                if (abs ((*stack.head().node)->balance_) == 2) {
                    turn(stack.head().node);
                }
            }
            else {
                (*stack.head().node)->balance_ =
                    (stack.head().direction) ? -1 : 1;
            }

            if (!(*stack.head().node)->balance_) {
                break;
            }
            else {
                stack.pop();
            }
        }
    }

    size_++;
    return true;
}

template<typename T, typename Compare>
bool AVL_tree<T, Compare>::insert(T &&value)
{
    if (size_ >= max_size()) {
        throw std::length_error("more than max size");
    }

    auto in_node{root_};
    auto q_node{&root_};
    Stack<Way> stack;
    for(;;) {
        if (!in_node) {
            in_node = *q_node = std::make_shared<Node>(Node{value});
            break;
        }
        else {
            if (in_node->info_ == value) {
                return false;
            }
            else {
                stack.push(Way {compare_(in_node->info_, value), q_node});
                q_node = &in_node->child_[stack.head().direction];
                in_node = *q_node;
            }
        }
    }

    if (in_node && stack.size()) {
        while (stack.size()) {
            if ((*stack.head().node)->balance_) {
                (*stack.head().node)->balance_ = (stack.head().direction) ? 
                    (*stack.head().node)->balance_ - 1 :
                    (*stack.head().node)->balance_ + 1;
                if (abs ((*stack.head().node)->balance_) == 2) {
                    turn(stack.head().node);
                }
            }
            else {
                (*stack.head().node)->balance_ =
                    (stack.head().direction) ? -1 : 1;
            }

            if (!(*stack.head().node)->balance_) {
                break;
            }
            else {
                stack.pop();
            }
        }
    }

    size_++;
    return true;
}

template<typename T, typename Compare>
bool AVL_tree<T, Compare>::find(T &value) const
{
    auto s_node {root_};
    if (!s_node) {
        return false;
    }
    while (value != s_node->info_) {
        s_node = s_node->child_[compare_(s_node->info_, value)];
        if (!s_node) {
            break;
        }
    }
    return true;
}

template<typename T, typename Compare>
bool AVL_tree<T, Compare>::find(T &&value) const
{
    auto s_node {root_};
    if (!s_node) {
        return false;
    }
    while (value != s_node->info_) {
        s_node = s_node->child_[compare_(s_node->info_, value)];
        if (!s_node) {
            break;
        }
    }
    return true;
}

template<typename T, typename Compare>
bool AVL_tree<T, Compare>::erase(T &value)
{
    auto erase_node {root_};
    auto q_node {&root_};
    Stack<Way> stack;
    for (;;) {
        if (!erase_node) {
            return false;
        }
        else {
            if (erase_node->info_ == value) {
                break;
            }
            else {
                stack.push(Way {compare_(erase_node->info_, value), q_node});
                q_node = &erase_node->child_[stack.head().direction];
                erase_node = *q_node;
            }
        }
    }
    if (!erase_node->child_[0]) {
        *q_node = erase_node->child_[1];
    }
    else {
        auto y_node {erase_node->child_[0]};
        stack.push(Way {0, q_node});
        if (!y_node->child_[1]) {
            y_node->child_[1] = erase_node->child_[1];
            y_node->balance_ = erase_node->balance_;
            *q_node = y_node;
        }
        else {
            auto x_node {y_node->child_[1]};
            auto changed_node {Way {1, nullptr}};
            stack.push(Way {1, nullptr});
            while (x_node->child_[1]) {
                stack.push(Way {1, &y_node->child_[1]});
                y_node = x_node;
                x_node = x_node->child_[1];
            }

            y_node->child_[1] = x_node->child_[0];
            x_node->child_[0] = erase_node->child_[0];
            x_node->child_[1] = erase_node->child_[1];

            changed_node.node = &x_node->child_[0];

            x_node->balance_ = erase_node->balance_;

            *q_node = x_node;
        }
    }
    while (stack.size()) {
        if ((*stack.head().node)->balance_) {
            (*stack.head().node)->balance_ = (stack.head().direction) ? 
                (*stack.head().node)->balance_ + 1 :
                (*stack.head().node)->balance_ - 1;
            if (abs ((*stack.head().node)->balance_) == 2) {
                turn(stack.head().node);
            }
        }
        else {
            (*stack.head().node)->balance_ = (stack.head().direction) ? 1 : -1;
        }

        if (!(*stack.head().node)->balance_) {
            break;
        }
        else {
            stack.pop();
        }
    }
    erase_node.reset();
    size_--;
    return true;
}

template<typename T, typename Compare>
bool AVL_tree<T, Compare>::erase(T &&value)
{
    auto erase_node {root_};
    auto q_node {&root_};
    Stack<Way> stack;
    for (;;) {
        if (!erase_node) {
            return false;
        }
        else {
            if (erase_node->info_ == value) {
                break;
            }
            else {
                stack.push(Way {compare_(erase_node->info_, value), q_node});
                q_node = &erase_node->child_[stack.head().direction];
                erase_node = *q_node;
            }
        }
    }
    if (!erase_node->child_[0]) {
        *q_node = erase_node->child_[1];
    }
    else {
        auto y_node {erase_node->child_[0]};
        stack.push(Way {0, q_node});
        if (!y_node->child_[1]) {
            y_node->child_[1] = erase_node->child_[1];
            y_node->balance_ = erase_node->balance_;
            *q_node = y_node;
        }
        else {
            auto x_node {y_node->child_[1]};
            auto changed_node {Way {1, nullptr}};
            stack.push(Way {1, nullptr});
            while (x_node->child_[1]) {
                stack.push(Way {1, &y_node->child_[1]});
                y_node = x_node;
                x_node = x_node->child_[1];
            }

            y_node->child_[1] = x_node->child_[0];
            x_node->child_[0] = erase_node->child_[0];
            x_node->child_[1] = erase_node->child_[1];

            changed_node.node = &x_node->child_[0];

            x_node->balance_ = erase_node->balance_;

            *q_node = x_node;
        }
    }
    while (stack.size()) {
        if ((*stack.head().node)->balance_) {
            (*stack.head().node)->balance_ = (stack.head().direction) ? 
                (*stack.head().node)->balance_ + 1 :
                (*stack.head().node)->balance_ - 1;
            if (abs ((*stack.head().node)->balance_) == 2) {
                turn(stack.head().node);
            }
        }
        else {
            (*stack.head().node)->balance_ = (stack.head().direction) ? 1 : -1;
        }

        if (!(*stack.head().node)->balance_) {
            break;
        }
        else {
            stack.pop();
        }
    }
    erase_node.reset();
    size_--;
    return true;
}

template<typename T, typename Compare>
void AVL_tree<T, Compare>::turn(decltype(root_) *t_node)
{
    decltype(root_) B = nullptr;//balansed node
    decltype(root_) A = nullptr;//child of balansed node
    decltype(root_) C = nullptr;//child of A node
    decltype(root_) beta = nullptr;
    decltype(root_) hama = nullptr;

    B = *t_node;

    auto direction {B->balance_ < 0};
    auto mod {(direction) ? 1 : -1};//modify depended on direction

    switch (B->child_[direction]->balance_ * mod) {
        case -1: case 0:
            A = B->child_[direction];
            hama = A->child_[!direction];
            A->child_[!direction] = B;
            B->child_[direction] = hama;
            *t_node = A;

            switch (A->balance_ * mod) {
                case -1:
                    B->balance_ = 0;
                    A->balance_ = 0;
                    break;
                case 0:
                    B->balance_ = -1 * mod;
                    A->balance_ = 1 * mod;
                    break;
            }
            break;
        case 1:
            A = B->child_[direction];
            C = A->child_[!direction];
            beta = C->child_[!direction];
            hama = C->child_[direction];
            C->child_[direction] = A;
            C->child_[!direction] = B;
            A->child_[!direction] = hama;
            B->child_[direction] = beta;
            *t_node = C;

            switch (C->balance_ * mod) {
                case -1:
                    B->balance_ = 1 * mod;
                    A->balance_ = 0;
                    C->balance_ = 0;
                    break;
                case 0:
                    B->balance_ = 0;
                    A->balance_ = 0;
                    C->balance_ = 0;
                    break;
                case 1:
                    B->balance_ = 0;
                    A->balance_ = -1 * mod;
                    C->balance_ = 0;
                    break;
            }
            break;
    }

    return;
}

template<typename C>
void walk(std::ofstream &fout, const C node)
{
    if (node->child_[0]) {
        walk(fout, node->child_[0]);
    }
    fout << node->info_ << " " ;
    if (node->child_[1]) {
        walk(fout, node->child_[1]);
    }
    return;
}

template<typename C>
std::ofstream &operator<<(std::ofstream &fout, C &tree)
{
    if (tree.get_root()) {
        walk(fout, tree.get_root());
    }
    return fout;
}

template<typename T, typename Compare>
auto AVL_tree<T, Compare>::get_root() const -> const decltype(root_)
{
    return root_;
}

template<typename T, typename Compare>
Compare AVL_tree<T, Compare>::key_comp() const
{
    return compare_;
}
