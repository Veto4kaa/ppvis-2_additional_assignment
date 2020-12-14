// Copyright 2020 for cpplint

#pragma once

#include <memory>
#include <utility>
#include <functional>
#include <exception>

#include "include/list.h"

// List of items
// we can
// - get the first item
// - add item to the end
// - erase items by index
// - erase items by value
// - find the number of items by value
// - apply the specified function to the items
template<typename T>
class OneWayList: public List<T> {
 protected:
    // the first item
    std::unique_ptr<ListItem<T>> head_;

 public:
    // Constructor
    explicit OneWayList(std::function<bool(const T&, const T&)> is_equal) :
            List<T>(is_equal) {
    }

    bool is_empty() override {
        return !head_;
    }

    T& get_first() override {
        if (!head_)
            throw std::runtime_error("List is empty");
        return head_->data_;
    }

    // Push data to the end
    void push(T data) override {
        if (!head_) {  // empty ?
            head_ = std::make_unique<ListItem<T>>(std::move(data));
        } else {
            auto new_item = std::make_unique<ListItem<T>>(std::move(data));
            // add the new item after the last item
            ListItem<T>* last = head_.get();
            while (last) {
                if (last->next_)
                    last = last->next_.get();
                else
                    break;
            }
            last->next_ = std::move(new_item);
        }
    }

    // Erase item by index
    void erase_by_index(int index) override {
        int pos = 0;
        if (!head_)
            return;
        // go through all items from the first
        ListItem<T>* prev = nullptr;
        ListItem<T>* cur = head_.get();
        while (cur) {
            if (pos == index) {
                if (pos == 0) {
                    head_ = std::move(cur->next_);
                } else {
                    if (cur->next_) {
                        prev->next_ = std::move(cur->next_);
                    } else {
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
        ListItem<T>* prev = nullptr;
        ListItem<T>* cur = head_.get();
        // process head
        while (cur) {
            if (List<T>::is_equal_(cur->data_, data)) {
                head_ = std::move(cur->next_);
                cur = head_.get();
            } else {
                prev = cur;
                cur = cur->next_.get();
                break;
            }
        }
        // process all other items
        while (cur) {
            if (List<T>::is_equal_(cur->data_, data)) {
                if (cur->next_) {
                    prev->next_ = std::move(cur->next_);
                    cur = prev->next_.get();
                } else {
                    prev->next_ = nullptr;
                    cur = nullptr;
                }
            } else {
                prev = cur;
                cur = cur->next_.get();
            }
        }
    }

    // Find all item with the specified data - return the number of such items
    int find(const T& data) override {
        return List<T>::template find<ListItem<T>>(data, head_);
    }

    // Apply the specified function to all item
    void apply(std::function<void(const T&)> callback) override {
        List<T>::template apply<ListItem<T>>(callback, head_);
    }
};
