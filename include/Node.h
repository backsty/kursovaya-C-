#ifndef NODE_H
#define NODE_H

#include <cstddef>

template<typename T>
struct Node {
    Node<T>* next;
    T* data;

    Node() : next(nullptr), data(nullptr) {}
    ~Node() { delete data; };
};

#endif
