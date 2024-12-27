#ifndef POINTERSLIST_H
#define POINTERSLIST_H

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string>

#include "Node.h"

template <class T>
class PointersList {
    Node<T>* head;      // Указатель на начало списка
    int max_size;       // Максимальный размер списка
    int current_size;   // Текущий размер списка

public:
    explicit PointersList(int max_size = 3);
    ~PointersList();

    void add(const T& element);
    void insert(int position, T& element);
    void remove(int position);
    T* get(int position);
    void sort_list();

    void display() const;
    bool is_full() const { return current_size >= max_size; }
    int size() const { return current_size; }
};

#endif
