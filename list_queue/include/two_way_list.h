// Copyright 2020 for cpplint

#pragma once

#include <memory>
#include <utility>
#include <functional>

#include "include/one_way_list.h"

// List of items
// we can
// - add item to the end
// - add item to the head
// - erase items by index
// - erase items by value
// - find the number of items by value
// - apply the specified function to the items from the first to the last
// - apply the specified function to the items from the last to the first
template<typename T>
class TwoWayList : public OneWayList<T> {
    using Parent = OneWayList<T>;

 public:
    // Constructor
    explicit TwoWayList(std::function<bool(const T&, const T&)> is_equal) :
            Parent(is_equal) {
    }

    // Push data to the head
    void push_head(T data) {
        if (!Parent::head_) {  // empty ?
            Parent::head_ = std::make_unique<ListItem<T>>(std::move(data));
            Parent::last_ = Parent::head_.get();
        } else {
            auto new_item = std::make_unique<ListItem<T>>(std::move(data));
            // add the new item before the first item
            Parent::head_->prev_ = new_item.get();
            new_item->next_ = std::move(Parent::head_);
            Parent::head_ = std::move(new_item);
        }
    }

    // Apply the specified function to all item from the last to the first
    void apply_reverse(std::function<void(const T&)> callback) {
        if (!OneWayList<T>::last_)
            return;
        ListItem<T>* cur = OneWayList<T>::last_;
        while (cur) {
            callback(cur->data_);
            cur = cur->prev_;
        }
    }
};
