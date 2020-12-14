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
    // the last item
    ListItem<T>* last_;
    // function to compare two data
    std::function<bool(const T&, const T&)> is_equal_;

 public:
    // Constructor
    explicit OneWayList(std::function<bool(const T&, const T&)> is_equal) :
        last_(nullptr),
        is_equal_(is_equal) {
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
            last_ = head_.get();
        } else {
            auto new_item = std::make_unique<ListItem<T>>(std::move(data));
            // add the new item after the current last item
            ListItem<T>* prev = last_;
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
        ListItem<T>* prev = nullptr;
        ListItem<T>* cur = head_.get();
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
        ListItem<T>* prev = nullptr;
        ListItem<T>* cur = head_.get();
        // process head
        while (cur) {
            if (is_equal_(cur->data_, data)) {
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
            if (is_equal_(cur->data_, data)) {
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

    // Find all item with the specified data - return the number of such items
    int find(const T& data) override {
        int count = 0;
        if (!head_)
            return count;
        // go through all items from the first
        ListItem<T>* cur = head_.get();
        while (cur) {
            if (is_equal_(cur->data_, data))
                count++;
            cur = cur->next_.get();
        }
        return count;
    }

    // Apply the specified function to all item
    void apply(std::function<void(const T&)> callback) override {
        if (!head_)
            return;
        // go through all items from the first
        ListItem<T>* cur = head_.get();
        while (cur) {
            callback(cur->data_);
            cur = cur->next_.get();
        }
    }
};
