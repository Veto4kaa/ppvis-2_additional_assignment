// Copyright 2020 for cpplint

#include <iostream>
#include "include/queue.h"
#include "include/one_way_list.h"
#include "include/two_way_list.h"

class Foo {
    int a_;
 public:
    explicit Foo(int a) : a_(a) {
    }

    Foo(Foo&&) = default;

    bool operator==(const Foo& rhs) const {
        return a_ == rhs.a_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Foo& a);
};

std::ostream& operator<<(std::ostream& os, const Foo& a) {
    os << a.a_;
    return os;
}

template<typename T>
void print_data(const T& data) {
    std::cout << data << " ";
}

template<typename T>
void print_pointer(const T& data) {
    std::cout << *data << " ";
}

template<typename T>
bool is_equal(const T& data1, const T& data2) {
    return data1 == data2;
}

template<typename T>
bool is_equal_pointers(const T& data1, const T& data2) {
    return *data1 == *data2;
}

void test_QueueInt_OneWayList() {
    typedef int DataType;
    // create list
    OneWayList<DataType> one_list(is_equal<DataType>);
    // create queue
    Queue<DataType> queue(one_list);
    // enqueue
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    // dequeue
    try {
        std::cout << "dequeue: \t" << queue.dequeue();
        std::cout << ", " << queue.dequeue();
        std::cout << ", " << queue.dequeue();
        std::cout << ", " << queue.dequeue() << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}

void test_QueueInt_TwoWayList() {
    typedef int DataType;
    // create list
    TwoWayList<DataType> two_list(is_equal<DataType>);
    // create queue
    Queue<DataType> queue(two_list);
    // enqueue
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    // dequeue
    try {
        std::cout << "dequeue: \t" << queue.dequeue();
        std::cout << ", " << queue.dequeue();
        std::cout << ", " << queue.dequeue();
        std::cout << ", " << queue.dequeue() << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}

void test_QueueFoo_OneWayList() {
    typedef Foo DataType;
    // create list
    OneWayList<DataType> one_list(is_equal<DataType>);
    // create queue
    Queue<DataType> queue(one_list);
    // enqueue
    queue.enqueue(Foo(1));
    queue.enqueue(Foo(2));
    queue.enqueue(Foo(3));
    // dequeue
    try {
        std::cout << "dequeue: \t" << queue.dequeue();
        std::cout << ", " << queue.dequeue();
        std::cout << ", " << queue.dequeue();
        std::cout << ", " << queue.dequeue() << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}

void test_QueueFoo_TwoWayList() {
    typedef Foo DataType;
    // create list
    TwoWayList<DataType> two_list(is_equal<DataType>);
    // create queue
    Queue<DataType> queue(two_list);
    // enqueue
    queue.enqueue(Foo(1));
    queue.enqueue(Foo(2));
    queue.enqueue(Foo(3));
    // dequeue
    try {
        std::cout << "dequeue: \t" << queue.dequeue();
        std::cout << ", " << queue.dequeue();
        std::cout << ", " << queue.dequeue();
        std::cout << ", " << queue.dequeue() << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}

void test_QueuePointer_OneWayList() {
    typedef std::unique_ptr<Foo> DataType;
    // create list
    OneWayList<DataType> one_list(is_equal_pointers<DataType>);
    // create queue
    Queue<DataType> queue(one_list);
    // enqueue
    queue.enqueue(std::make_unique<Foo>(1));
    queue.enqueue(std::make_unique<Foo>(2));
    queue.enqueue(std::make_unique<Foo>(3));
    // dequeue
    try {
        std::cout << "dequeue: \t" << *queue.dequeue();
        std::cout << ", " << *queue.dequeue();
        std::cout << ", " << *queue.dequeue();
        std::cout << ", " << *queue.dequeue() << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}

void test_QueuePointer_TwoWayList() {
    typedef std::unique_ptr<Foo> DataType;
    // create list
    TwoWayList<DataType> two_list(is_equal_pointers<DataType>);
    // create queue
    Queue<DataType> queue(two_list);
    // enqueue
    queue.enqueue(std::make_unique<Foo>(1));
    queue.enqueue(std::make_unique<Foo>(2));
    queue.enqueue(std::make_unique<Foo>(3));
    // dequeue
    try {
        std::cout << "dequeue: \t" << *queue.dequeue();
        std::cout << ", " << *queue.dequeue();
        std::cout << ", " << *queue.dequeue();
        std::cout << ", " << *queue.dequeue() << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}

void test_OneWayList_Int() {
    typedef int DataType;
    // create list
    OneWayList<DataType> one_list(is_equal<DataType>);
    // add 1 and 2
    one_list.push(1);
    one_list.push(1);
    one_list.push(1);
    one_list.push(2);
    // apply
    std::cout << "List has: \t";
    one_list.apply(print_data<DataType>);
    // find
    std::cout << std::endl << "The 1 found " <<
                 one_list.find(1) << " times" << std::endl;
    // erase 2 and 1
    one_list.erase_by_value(2);
    one_list.erase_by_value(1);
    // add 1 and 2
    one_list.push(1);
    one_list.push(2);
    // erase 2 and 1
    one_list.erase_by_index(1);
    one_list.erase_by_index(0);
}

void test_TwoWayList_Int() {
    typedef int DataType;
    // create list
    TwoWayList<DataType> two_list(is_equal<DataType>);
    // add 1 and 2
    two_list.push(1);
    two_list.push(1);
    two_list.push_head(2);
    two_list.push_head(2);
    // apply
    std::cout << "List has: \t";
    two_list.apply(print_data<DataType>);
    std::cout << std::endl << "Reversed List has: \t";
    two_list.apply_reverse(print_data<DataType>);
    // find
    std::cout << std::endl << "The 1 found " <<
                 two_list.find(1) << " times" << std::endl;
    // erase 2 and 1
    two_list.erase_by_value(2);
    two_list.erase_by_value(1);
    // add 1 and 2
    two_list.push(1);
    two_list.push(2);
    // erase 2 and 1
    two_list.erase_by_index(1);
    two_list.erase_by_index(0);
}

void test_OneWayList_Foo() {
    typedef Foo DataType;
    // create list
    OneWayList<DataType> one_list(is_equal<DataType>);
    // add 1 and 2
    one_list.push(Foo(1));
    one_list.push(Foo(1));
    one_list.push(Foo(2));
    one_list.push(Foo(2));
    // apply
    std::cout << "List has: \t";
    one_list.apply(print_data<DataType>);
    // find
    std::cout << std::endl << "The Foo(1) found " <<
              one_list.find(Foo(1)) << " times" << std::endl;
    // erase 2 and 1
    one_list.erase_by_value(Foo(2));
    one_list.erase_by_value(Foo(1));
    // add 1 and 2
    one_list.push(Foo(1));
    one_list.push(Foo(2));
    // erase 2 and 1
    one_list.erase_by_index(1);
    one_list.erase_by_index(0);
}

void test_TwoWayList_Foo() {
    typedef Foo DataType;
    // create list
    TwoWayList<DataType> two_list(is_equal<DataType>);
    // add 1 and 2
    two_list.push(Foo(1));
    two_list.push(Foo(1));
    two_list.push_head(Foo(2));
    two_list.push_head(Foo(2));
    // apply
    std::cout << "List has: \t";
    two_list.apply(print_data<DataType>);
    std::cout << std::endl << "Reversed List has: \t";
    two_list.apply_reverse(print_data<DataType>);
    // find
    std::cout << std::endl << "The Foo(1) found " <<
              two_list.find(Foo(1)) << " times" << std::endl;
    // erase 2 and 1
    two_list.erase_by_value(Foo(2));
    two_list.erase_by_value(Foo(1));
    // add 1 and 2
    two_list.push(Foo(1));
    two_list.push(Foo(2));
    // erase 2 and 1
    two_list.erase_by_index(1);
    two_list.erase_by_index(0);
}

void test_OneWayList_Pointer() {
    typedef std::unique_ptr<Foo> DataType;
    // create list
    OneWayList<DataType> one_list(is_equal_pointers<DataType>);
    // add 1 and 2
    one_list.push(std::make_unique<Foo>(1));
    one_list.push(std::make_unique<Foo>(1));
    one_list.push(std::make_unique<Foo>(2));
    one_list.push(std::make_unique<Foo>(2));
    // apply
    std::cout << "List has: \t";
    one_list.apply(print_pointer<DataType>);
    // find
    std::cout << std::endl << "The pointer to Foo(1) found " <<
              one_list.find(std::make_unique<Foo>(1)) << " times" << std::endl;
    // erase 2 and 1
    one_list.erase_by_value(std::make_unique<Foo>(2));
    one_list.erase_by_value(std::make_unique<Foo>(1));
    // add 1 and 2
    one_list.push(std::make_unique<Foo>(1));
    one_list.push(std::make_unique<Foo>(2));
    // erase 2 and 1
    one_list.erase_by_index(1);
    one_list.erase_by_index(0);
}

void test_TwoWayList_Pointer() {
    typedef std::unique_ptr<Foo> DataType;
    // create list
    TwoWayList<DataType> two_list(is_equal_pointers<DataType>);
    // add 1 and 2
    two_list.push(std::make_unique<Foo>(1));
    two_list.push(std::make_unique<Foo>(1));
    two_list.push_head(std::make_unique<Foo>(2));
    two_list.push_head(std::make_unique<Foo>(2));
    // apply
    std::cout << "List has: \t";
    two_list.apply(print_pointer<DataType>);
    std::cout << std::endl << "Reversed List has: \t";
    two_list.apply_reverse(print_pointer<DataType>);
    // find
    std::cout << std::endl << "The pointer to Foo(1) found " <<
              two_list.find(std::make_unique<Foo>(1)) << " times" << std::endl;
    // erase 2 and 1
    two_list.erase_by_value(std::make_unique<Foo>(2));
    two_list.erase_by_value(std::make_unique<Foo>(1));
    // add 1 and 2
    two_list.push(std::make_unique<Foo>(1));
    two_list.push(std::make_unique<Foo>(2));
    // erase 2 and 1
    two_list.erase_by_index(1);
    two_list.erase_by_index(0);
}

int main() {
    std::cout << "------ test_QueueInt_OneWayList ------" << std::endl;
    test_QueueInt_OneWayList();
    std::cout << "------ test_QueueInt_TwoWayList ------" << std::endl;
    test_QueueInt_TwoWayList();
    std::cout << "------ test_QueueFoo_OneWayList ------" << std::endl;
    test_QueueFoo_OneWayList();
    std::cout << "------ test_QueueFoo_TwoWayList ------" << std::endl;
    test_QueueFoo_TwoWayList();
    std::cout << "------ test_QueuePointer_OneWayList ------" << std::endl;
    test_QueuePointer_OneWayList();
    std::cout << "------ test_QueuePointer_TwoWayList ------" << std::endl;
    test_QueuePointer_TwoWayList();

    std::cout << "------ test_OneWayList_Int ------" << std::endl;
    test_OneWayList_Int();
    std::cout << "------ test_TwoWayList_Int ------" << std::endl;
    test_TwoWayList_Int();
    std::cout << "------ test_OneWayList_Foo ------" << std::endl;
    test_OneWayList_Foo();
    std::cout << "------ test_TwoWayList_Foo ------" << std::endl;
    test_TwoWayList_Foo();
    std::cout << "------ test_OneWayList_Pointer ------" << std::endl;
    test_OneWayList_Pointer();
    std::cout << "------ test_TwoWayList_Pointer ------" << std::endl;
    test_TwoWayList_Pointer();
    return 0;
}
