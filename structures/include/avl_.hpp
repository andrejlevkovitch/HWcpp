//avl_.hpp

#pragma once

#include"avl.hpp"

template<typename T, typename Compare>
size_t AVL_tree<T, Compare>::max_size()
{
    static const size_t retvalue {1000000};
    return retvalue;
}


template<typename T, typename Compare>
typename AVL_tree<T, Compare>::IteratorBi
AVL_tree<T, Compare>::end() const
{
    void_end_node_->child_[0] = root_;
    IteratorBi endIter;
    endIter.pointer_ = void_end_node_;
    return endIter;
}

template<typename T, typename Compare>
typename AVL_tree<T, Compare>::IteratorBi
AVL_tree<T, Compare>::begin() const
{
    IteratorBi beginIter {end()};
    beginIter.first();
    return beginIter;
}

template<typename T, typename Compare>
typename AVL_tree<T, Compare>::IteratorBiRev
AVL_tree<T, Compare>::rend() const
{
    void_begin_node_->child_[1] = root_;
    IteratorBiRev endIter;
    endIter.pointer_ = void_begin_node_;
    return endIter;
}

template<typename T, typename Compare>
typename AVL_tree<T, Compare>::IteratorBiRev
AVL_tree<T, Compare>::rbegin() const
{
    IteratorBiRev beginIter {rend()};
    beginIter.last();
    return beginIter;
}


template<typename T, typename Compare>
size_t AVL_tree<T, Compare>::size() const
{
    return size_;
}

template<typename T, typename Compare>
bool AVL_tree<T, Compare>::empty() const
{
    return (root_) ? false : true;
}

template<typename T, typename Compare>
AVL_tree<T, Compare>::AVL_tree () : root_ {nullptr}, size_ {0}
{
    void_end_node_ = std::make_shared<Node>();
    void_begin_node_ = std::make_shared<Node>();
}

template<typename T, typename Compare>
AVL_tree<T, Compare>::AVL_tree (const Compare & comp) :
    root_ {nullptr}, size_ {0}, compare_ {comp}
{
    void_end_node_ = std::make_shared<Node>();
    void_begin_node_ = std::make_shared<Node>();
}

template<typename T, typename Compare>
AVL_tree<T, Compare>::AVL_tree (const AVL_tree & in) :
    root_ {nullptr}, size_ {0}, void_end_node_ {in.void_end_node_},
    void_begin_node_ {in.void_begin_node_}
{
    for (auto & i : in) {
        insert(i);
    }
}

template<typename T, typename Compare>
AVL_tree<T, Compare> & AVL_tree<T, Compare>::operator=(const AVL_tree & in)
{
    root_ = nullptr;
    size_ = 0;
    void_end_node_ = in.void_end_node_;
    void_begin_node_ = in.void_begin_node_;
    for (auto & i : in) {
        insert(i);
    }
    return *this;
}

template<typename T, typename Compare>
AVL_tree<T, Compare>::AVL_tree (AVL_tree && in) :
    root_ {in.root_}, size_ {in.size_}, void_end_node_ {in.void_end_node_},
    void_begin_node_ {in.void_begin_node_}
{
    in.root_ = nullptr;
    in.size_ = 0;
}

template<typename T, typename Compare>
AVL_tree<T, Compare> & AVL_tree<T, Compare>::operator=(AVL_tree && in)
{
    root_ = in.root_;
    size_ = in.size_;
    void_end_node_ = in.void_end_node_;
    void_begin_node_ = in.void_begin_node_;
    in.root_ = nullptr;
    in.size_ = 0;
    return *this;
}


template<typename T, typename Compare>
void AVL_tree<T, Compare>::insert(const T & value)
{
    if (size_ >= max_size()) {
        throw std::length_error("more than max size tree");
    }

    auto in_node{root_};
    auto q_node{&root_};
    Stack<Step> way;
    for(;;) {
        if (!in_node) {
            in_node = *q_node = std::make_shared<Node>(value);
            break;
        }
        else {
            if (in_node->key_ == value) {
                if (++(in_node->counter_) == 0) {
                    throw std::length_error("more than max size element");
                }
                ++size_;
                return;
            }
            else {
                way.push(Step {compare_(in_node->key_, value), q_node});
                q_node = &in_node->child_[way.head().direction];
                in_node = *q_node;
            }
        }
    }

    if (in_node && !way.empty()) {
        while (!way.empty()) {
            if ((*way.head().node)->balance_) {
                (*way.head().node)->balance_ = (way.head().direction) ? 
                    (*way.head().node)->balance_ - 1 :
                    (*way.head().node)->balance_ + 1;
                if (abs ((*way.head().node)->balance_) == 2) {
                    turn(way.head().node);
                }
            }
            else {
                (*way.head().node)->balance_ =
                    (way.head().direction) ? -1 : 1;
            }

            if (!(*way.head().node)->balance_) {
                break;
            }
            else {
                way.pop();
            }
        }
    }

    ++size_;
    return;
}

template<typename T, typename Compare>
void AVL_tree<T, Compare>::insert(const T && value)
{
    if (size_ >= max_size()) {
        throw std::length_error("more than max size tree");
    }

    auto in_node{root_};
    auto q_node{&root_};
    Stack<Step> way;
    for(;;) {
        if (!in_node) {
            in_node = *q_node = std::make_shared<Node>(value);
            break;
        }
        else {
            if (in_node->key_ == value) {
                if (++(in_node->counter_) == 0) {
                    throw std::length_error("more than max size element");
                }
                ++size_;
                return;
            }
            else {
                way.push(Step {compare_(in_node->key_, value), q_node});
                q_node = &in_node->child_[way.head().direction];
                in_node = *q_node;
            }
        }
    }

    if (in_node && !way.empty()) {
        while (!way.empty()) {
            if ((*way.head().node)->balance_) {
                (*way.head().node)->balance_ = (way.head().direction) ? 
                    (*way.head().node)->balance_ - 1 :
                    (*way.head().node)->balance_ + 1;
                if (abs ((*way.head().node)->balance_) == 2) {
                    turn(way.head().node);
                }
            }
            else {
                (*way.head().node)->balance_ =
                    (way.head().direction) ? -1 : 1;
            }

            if (!(*way.head().node)->balance_) {
                break;
            }
            else {
                way.pop();
            }
        }
    }

    ++size_;
    return;
}

template<typename T, typename Compare>
typename AVL_tree<T, Compare>::IteratorBi
AVL_tree<T, Compare>::find(const T & value) const
{
    if (!root_) {
        return end();
    }
    auto s_node {root_};
    while (value != s_node->key_) {
        s_node = s_node->child_[compare_(s_node->key_, value)];
        if (!s_node) {
            return end();
        }
    }
    IteratorBi iterator;
    iterator.pointer_ = s_node;
    return iterator;
}

template<typename T, typename Compare>
typename AVL_tree<T, Compare>::IteratorBi
AVL_tree<T, Compare>::find(const T && value) const
{
    if (!root_) {
        return end();
    }
    auto s_node {root_};
    while (value != s_node->key_) {
        s_node = s_node->child_[compare_(s_node->key_, value)];
        if (!s_node) {
            return end();
        }
    }
    IteratorBi iterator;
    iterator.pointer_ = s_node;
    return iterator;
}

template<typename T, typename Compare>
unsigned short AVL_tree<T, Compare>::count(const T & value) const
{
    auto it {find(value)};
    return (it != end()) ? it.pointer_->counter_ : 0;
}

template<typename T, typename Compare>
unsigned short AVL_tree<T, Compare>::count(const T && value) const
{
    auto it {find(value)};
    return (it != end()) ? it.pointer_->counter_ : 0;
}

template<typename T, typename Compare>
void AVL_tree<T, Compare>::erase(const T & value)
{
    auto erase_node {root_};
    auto q_node {&root_};
    Stack<Step> way;
    for (;;) {
        if (!erase_node) {
            return;
        }
        else {
            if (erase_node->key_ == value) {
                break;
            }
            else {
                way.push(Step {compare_(erase_node->key_, value), q_node});
                q_node = &erase_node->child_[way.head().direction];
                erase_node = *q_node;
            }
        }
    }
    if (--(erase_node->counter_) == 0) {
        if (!erase_node->child_[0]) {
            *q_node = erase_node->child_[1];
        }
        else {
            auto y_node {erase_node->child_[0]};
            way.push(Step {0, q_node});
            if (!y_node->child_[1]) {
                y_node->child_[1] = erase_node->child_[1];
                y_node->balance_ = erase_node->balance_;
                *q_node = y_node;
            }
            else {
                auto x_node {y_node->child_[1]};
                auto changed_node {Step {1, nullptr}};
                way.push(Step {1, nullptr});
                while (x_node->child_[1]) {
                    way.push(Step {1, &y_node->child_[1]});
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
        while (!way.empty()) {
            if ((*way.head().node)->balance_) {
                (*way.head().node)->balance_ = (way.head().direction) ? 
                    (*way.head().node)->balance_ + 1 :
                    (*way.head().node)->balance_ - 1;
                if (abs ((*way.head().node)->balance_) == 2) {
                    turn(way.head().node);
                }
            }
            else {
                (*way.head().node)->balance_ = (way.head().direction) ? 1 : -1;
            }

            if (!(*way.head().node)->balance_) {
                break;
            }
            else {
                way.pop();
            }
        }
    }
    erase_node.reset();
    --size_;
    return;
}

template<typename T, typename Compare>
void AVL_tree<T, Compare>::erase(const T && value)
{
    auto erase_node {root_};
    auto q_node {&root_};
    Stack<Step> way;
    for (;;) {
        if (!erase_node) {
            return;
        }
        else {
            if (erase_node->key_ == value) {
                break;
            }
            else {
                way.push(Step {compare_(erase_node->key_, value), q_node});
                q_node = &erase_node->child_[way.head().direction];
                erase_node = *q_node;
            }
        }
    }
    if (--(erase_node->counter_) == 0) {
        if (!erase_node->child_[0]) {
            *q_node = erase_node->child_[1];
        }
        else {
            auto y_node {erase_node->child_[0]};
            way.push(Step {0, q_node});
            if (!y_node->child_[1]) {
                y_node->child_[1] = erase_node->child_[1];
                y_node->balance_ = erase_node->balance_;
                *q_node = y_node;
            }
            else {
                auto x_node {y_node->child_[1]};
                auto changed_node {Step {1, nullptr}};
                way.push(Step {1, nullptr});
                while (x_node->child_[1]) {
                    way.push(Step {1, &y_node->child_[1]});
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
        while (!way.empty()) {
            if ((*way.head().node)->balance_) {
                (*way.head().node)->balance_ = (way.head().direction) ? 
                    (*way.head().node)->balance_ + 1 :
                    (*way.head().node)->balance_ - 1;
                if (abs ((*way.head().node)->balance_) == 2) {
                    turn(way.head().node);
                }
            }
            else {
                (*way.head().node)->balance_ = (way.head().direction) ? 1 : -1;
            }

            if (!(*way.head().node)->balance_) {
                break;
            }
            else {
                way.pop();
            }
        }
    }
    erase_node.reset();
    --size_;
    return;
}

template<typename T, typename Compare>
void AVL_tree<T, Compare>::turn(std::shared_ptr<Node> * t_node)
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

template<typename T, typename Compare>
Compare AVL_tree<T, Compare>::key_comp() const
{
    return compare_;
}

template<typename T, typename Compare>
void AVL_tree<T, Compare>::clear()
{
    if (!empty()) {
        size_ = 0;
        walk(root_);
    }
    return;
}

template<typename T, typename Compare>
void AVL_tree<T, Compare>::walk(std::shared_ptr<Node> & in)
{
    if (in) {
        walk(in->child_[0]);
        walk(in->child_[1]);
        in.reset();
    }
    return;
}
