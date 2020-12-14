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
    // the first item
    std::unique_ptr<ListItemBi<T>> head_;
    // the last item
    ListItemBi<T>* last_;

 public:
    // Constructor
    explicit TwoWayList(std::function<bool(const T&, const T&)> is_equal) :
            Parent(is_equal),
            last_(nullptr) {
    }

    // Push data to the end
    void push(T data) override {
        if (!head_) {  // empty ?
            head_ = std::make_unique<ListItemBi<T>>(std::move(data));
            last_ = head_.get();
        } else {
            auto new_item = std::make_unique<ListItemBi<T>>(std::move(data));
            // add the new item after the current last item
            ListItemBi<T>* prev = last_;
            last_ = new_item.get();
            last_->prev_ = prev;
            prev->next_ = std::move(new_item);
        }
    }

    // Erase item by index
    void erase_by_index(int index) override {
        int pos = 0;
        if (!head_)
            return;
        // go through all items from the first
        ListItemBi<T>* prev = nullptr;
        ListItemBi<T>* cur = head_.get();
        while (cur) {
            if (pos == index) {
                if (pos == 0) {
                    head_ = std::move(cur->next_);
                    if (head_)
                        head_->prev_ = nullptr;
                    else
                        last_ = nullptr;
                } else {
                    if (cur->next_) {
                        cur->next_->prev_ = prev;
                        prev->next_ = std::move(cur->next_);
                    } else {
                        last_ = prev;
                        prev->next_ = nullptr;
                    }
                }
                break;
            }
            pos++;
            prev = cur;
            cur = cur->next_.get();
        }
    }

    // Erase all item with the specified data
    void erase_by_value(const T& data) override {
        if (!head_)
            return;
        ListItemBi<T>* prev = nullptr;
        ListItemBi<T>* cur = head_.get();
        // process head
        while (cur) {
            if (Parent::is_equal_(cur->data_, data)) {
                head_ = std::move(cur->next_);
                if (head_)
                    head_->prev_ = nullptr;
                else
                    last_ = nullptr;
                cur = head_.get();
            } else {
                prev = cur;
                cur = cur->next_.get();
                break;
            }
        }
        // process all other items
        while (cur) {
            if (Parent::is_equal_(cur->data_, data)) {
                if (cur->next_) {
                    cur->next_->prev_ = prev;
                    prev->next_ = std::move(cur->next_);
                    cur = prev->next_.get();
                } else {
                    last_ = prev;
                    prev->next_ = nullptr;
                    cur = nullptr;
                }
            } else {
                prev = cur;
                cur = cur->next_.get();
            }
        }
    }

    // Push data to the head
    void push_head(T data) {
        if (!head_) {  // empty ?
            head_ = std::make_unique<ListItemBi<T>>(std::move(data));
            last_ = head_.get();
        } else {
            auto new_item = std::make_unique<ListItemBi<T>>(std::move(data));
            // add the new item before the first item
            head_->prev_ = new_item.get();
            new_item->next_ = std::move(head_);
            head_ = std::move(new_item);
        }
    }

    // Find all item with the specified data - return the number of such items
    int find(const T& data) override {
        return List<T>::template find<ListItemBi<T>>(data, head_);
    }

    // Apply the specified function to all item
    void apply(std::function<void(const T&)> callback) override {
        List<T>::template apply<ListItemBi<T>>(callback, head_);
    }

    // Apply the specified function to all item from the last to the first
    void apply_reverse(std::function<void(const T&)> callback) {
        if (!last_)
            return;
        ListItemBi<T>* cur = last_;
        while (cur) {
            callback(cur->data_);
            cur = cur->prev_;
        }
    }
};
