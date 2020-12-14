// Copyright 2020 for cpplint

#pragma once

#include <memory>
#include <utility>
#include <functional>

#include "include/one_way_list.h"

// Queue of items
// we can
// - add item to the end
// - get item from the head and move it from the queue
template<typename T>
class Queue {
    List<T>& list_;
 public:
    // Constructor
    explicit Queue(List<T>& list) : list_(list) {
    }

    void enqueue(T data) {
        list_.push(std::move(data));
    }

    bool is_empty() {
        return list_.is_empty();
    }

    T dequeue() {
        T data = std::move(list_.get_first());
        list_.erase_by_index(0);
        return data;
    }
};
