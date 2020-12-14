// Copyright 2020 for cpplint

#pragma once

#include <memory>
#include <utility>
#include <functional>

// List of items
// we can
// - get the first item
// - add item to the end
// - erase items by index
// - erase items by value
// - find the number of items by value
// - apply the specified function to the items
template<typename T>
class List {
 public:
    // Constructor
    explicit List(std::function<bool(const T&, const T&)> is_equal) :
        is_equal_(is_equal) {
    }

    virtual ~List() = default;

    virtual bool is_empty() = 0;

    virtual T& get_first() = 0;

    // Push data to the end
    virtual void push(T data) = 0;

    // Erase item by index
    virtual void erase_by_index(int index) = 0;

    // Erase all item with the specified data
    virtual void erase_by_value(const T& data) = 0;

    // Find all item with the specified data - return the number of such items
    virtual int find(const T& data) = 0;

    // Apply the specified function to all item
    virtual void apply(std::function<void(const T&)> callback) = 0;

 protected:
    // function to compare two data
    std::function<bool(const T&, const T&)> is_equal_;

    // Find all item with the specified data - return the number of such items
    template<typename L>
    int find(const T& data, const std::unique_ptr<L>& head) {
        int count = 0;
        if (!head)
            return count;
        // go through all items from the first
        L* cur = head.get();
        while (cur) {
            if (is_equal_(cur->data_, data))
                count++;
            cur = cur->next_.get();
        }
        return count;
    }

    // Apply the specified function to all item
    template<typename L>
    void apply(std::function<void(const T&)> callback,
               const std::unique_ptr<L>& head) {
        if (!head)
            return;
        // go through all items from the first
        L* cur = head.get();
        while (cur) {
            callback(cur->data_);
            cur = cur->next_.get();
        }
    }
};

// Item for one way list
template<typename T>
struct ListItem {
    // next item
    std::unique_ptr<ListItem> next_;
    // data
    T data_;
    // Constructor
    explicit ListItem(T data) :
            next_(nullptr),
            data_(std::move(data)) {
    }
};

// Item for two way list
template<typename T>
struct ListItemBi {
    // next item
    std::unique_ptr<ListItemBi> next_;
    // data
    T data_;
    // prev item
    ListItemBi* prev_;
    // Constructor
    explicit ListItemBi(T data) :
        next_(nullptr),
        data_(std::move(data)),
        prev_(nullptr) {
    }
};
