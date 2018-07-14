//iterator.cpp

#pragma once

#include"avl_tree.hpp"

template<typename T, typename Compare>
AVL_tree<T, Compare>::IteratorConst::IteratorConst () : pointer_ {nullptr}
{
}

template<typename T, typename Compare>
AVL_tree<T, Compare>::IteratorConst::IteratorConst (
        std::shared_ptr<Node> & node) : pointer_ {node}
{
}

template<typename T, typename Compare>
typename AVL_tree<T, Compare>::IteratorConst &
AVL_tree<T, Compare>::IteratorConst::operator++()
{
    if (way_.empty()) {
        if (pointer_->child_[LEFT]) {
            do {
                way_.push(StepI {LEFT, pointer_});
                pointer_ = pointer_->child_[LEFT];
            } while (pointer_->child_[LEFT]);
        }
    }
    else {
        if (pointer_->child_[RIGHT]) {
            way_.push(StepI {RIGHT, pointer_});
            pointer_ = pointer_->child_[RIGHT];
            if (pointer_->child_[LEFT]) {
                do {
                    way_.push(StepI {LEFT, pointer_});
                    pointer_ = pointer_->child_[LEFT];
                } while (pointer_->child_[LEFT]);
            }
        }
        else {
            for (;
                    (way_.size() > 1) && way_.head().direction == RIGHT;
                    way_.pop()) {
            }
            pointer_ = way_.head().node;
            way_.pop();
        }
    }
    return *this;
}

template<typename T, typename Compare>
typename AVL_tree<T, Compare>::IteratorConst &
AVL_tree<T, Compare>::IteratorConst::operator--()
{
    if (way_.empty()) {
        if (pointer_->child_[RIGHT]) {
            do {
                way_.push(StepI {RIGHT, pointer_});
                pointer_ = pointer_->child_[RIGHT];
            } while (pointer_->child_[RIGHT]);
        }
    }
    else {
        if (pointer_->child_[LEFT]) {
            way_.push(StepI {LEFT, pointer_});
            pointer_ = pointer_->child_[LEFT];
            if (pointer_->child_[RIGHT]) {
                do {
                    way_.push(StepI {RIGHT, pointer_});
                    pointer_ = pointer_->child_[RIGHT];
                } while (pointer_->child_[RIGHT]);
            }
        }
        else {
            for (;
                    (way_.size() > 1) && way_.head().direction == LEFT;
                    way_.pop()) {
            }
            pointer_ = way_.head().node;
            way_.pop();
        }
    }
    return *this;
}

template<typename T, typename Compare>
const T & AVL_tree<T, Compare>::IteratorConst::operator*() const
{
    return pointer_->key_;
}

template<typename T, typename Compare>
const T * AVL_tree<T, Compare>::IteratorConst::operator->() const
{
    return & pointer_->key_;
}

template<typename T, typename Compare>
bool AVL_tree<T, Compare>::IteratorConst::operator==(
        const IteratorConst & rhs) const
{
    return (pointer_ == rhs.pointer_) ? true : false;
}

template<typename T, typename Compare>
bool AVL_tree<T, Compare>::IteratorConst::operator!=(
        const IteratorConst & rhs) const
{
    return (pointer_ != rhs.pointer_) ? true : false;
}