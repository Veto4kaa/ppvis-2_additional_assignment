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
};

// Item
template<typename T>
struct ListItem {
    // next item
    std::unique_ptr<ListItem> next_;
    // prev item
    ListItem* prev_;
    // data
    T data_;
    // Constructor
    explicit ListItem(T data) :
            next_(nullptr),
            prev_(nullptr),
            data_(std::move(data)) {
    }
};
