#ifndef POINTERSARRAY_H
#define POINTERSARRAY_H

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <fstream>
#include <string>

#include "PointersList.h"

template <typename T>
class PointersArray {
    PointersList<T>** lists;
    int max_list_size;
    int length;

public:
    explicit PointersArray(int element_max_size, int array_length);
    ~PointersArray();

    void add(const T& element);
    void insert(int list_index, int position, T& element);
    void remove(int list_index, int position);
    void display() const;
    void sort();
    void balance();
    void save(const char* filename);
    void load(const char* filename);

    bool can_insert(int list_index) const {
        return !lists[list_index]->is_full();
    }
    int get_list_size(int list_index) const {
        if (list_index < 0 || list_index >= length) {
            throw std::out_of_range("Индекс списка выходит за пределы диапазона");
        }
        return lists[list_index]->size();
    }
};

#endif