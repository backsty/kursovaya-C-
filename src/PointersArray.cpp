#include <iostream>
#include <stdexcept>
#include <cstring>
#include <fstream>
#include <string>

#include "PointersArray.h"

template <typename T>
PointersArray<T>::PointersArray(int element_max_size, int array_length)
    : max_list_size(element_max_size), length(array_length) {
    lists = new PointersList<T>*[length];
    for (int i = 0; i < length; ++i) {
        lists[i] = new PointersList<T>(max_list_size);
    }
}

template <typename T>
PointersArray<T>::~PointersArray() {
    for (int i = 0; i < length; ++i) {
        delete lists[i];
    }
    delete[] lists;
}

template <typename T>
void PointersArray<T>::add(const T& element) {
    for (int i = 0; i < length; ++i) {
        if (!lists[i]->is_full()) {
            lists[i]->add(element);
            return;
        }
    }
    throw std::overflow_error("Все списки заполнены");
}

template <typename T>
void PointersArray<T>::insert(int list_index, int position, T& element) {
    if (list_index < 0 || list_index >= length) {
        throw std::out_of_range("Индекс списка выходит за пределы диапазона");
    }
    
    if (lists[list_index]->is_full()) {
        for (int i = list_index + 1; i < length; i++) {
            if (!lists[i]->is_full()) {
                lists[i]->insert(0, element);
                return;
            }
        }
        throw std::overflow_error("Выбранный список заполнен");
    }

    int current_size = lists[list_index]->size();
    if (position < 0 || position > current_size) {
        throw std::out_of_range("Недопустимая позиция");
    }
    
    lists[list_index]->insert(position, element);
}

template <typename T>
void PointersArray<T>::remove(int list_index, int position) {
    if (list_index < 0 || list_index >= length) {
        throw std::out_of_range("Индекс списка выходит за пределы диапазона");
    }
    
    int current_size = lists[list_index]->size();
    if (position < 0 || position >= current_size) {
        throw std::out_of_range("Недопустимая позиция");
    }
    
    lists[list_index]->remove(position);
}

template <typename T>
void PointersArray<T>::display() const {
    for (int i = 0; i < length; ++i) {
        std::cout << "List " << i << ": ";
        lists[i]->display();
    }
}

template <typename T>
void PointersArray<T>::sort() {
    for (int i = 0; i < length; ++i) {
        if (lists[i]->size() > 0) {
            lists[i]->sort_list();
        }
    }
}

template <typename T>
void PointersArray<T>::balance() {
    int total_elements = 0;
    // Подсчёт общего количества элементов
    for (int i = 0; i < length; ++i) {
        total_elements += lists[i]->size();
    }
    
    int target_size = total_elements / length;
    if (total_elements % length != 0) target_size++;
    
    // Временное хранилище всех элементов
    T** elements = new T*[total_elements];
    int elem_idx = 0;
    
    // Сбор всех элементов
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < lists[i]->size(); ++j) {
            elements[elem_idx++] = new T(*(lists[i]->get(j)));
        }
    }
    
    // Очистка списков
    for (int i = 0; i < length; ++i) {
        delete lists[i];
        lists[i] = new PointersList<T>(max_list_size);
    }
    
    // Перераспределение элементов
    elem_idx = 0;
    for (int i = 0; i < length && elem_idx < total_elements; ++i) {
        for (int j = 0; j < target_size && elem_idx < total_elements; ++j) {
            lists[i]->add(*elements[elem_idx]);
            delete elements[elem_idx];
            elem_idx++;
        }
    }
    
    delete[] elements;
}

template <typename T>
void PointersArray<T>::save(const char* filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Невозможно открыть файл для записи");
    }

    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(reinterpret_cast<const char*>(&max_list_size), sizeof(max_list_size));

    for (int i = 0; i < length; ++i) {
        int size = lists[i]->size();
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));

        for (int j = 0; j < size; ++j) {
            char** strPtr = lists[i]->get(j);
            char* str = *strPtr;
            int strLen = strlen(str) + 1;
            file.write(reinterpret_cast<const char*>(&strLen), sizeof(strLen));
            file.write(str, strLen);
        }
    }
    file.close();
}

template <typename T>
void PointersArray<T>::load(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Невозможно открыть файл для чтения");
    }

    int savedLength, savedMaxSize;
    file.read(reinterpret_cast<char*>(&savedLength), sizeof(savedLength));
    file.read(reinterpret_cast<char*>(&savedMaxSize), sizeof(savedMaxSize));

    if (savedLength != length || savedMaxSize != max_list_size) {
        throw std::runtime_error("Несовместимые размеры структуры");
    }

    for (int i = 0; i < length; ++i) {
        delete lists[i];
        lists[i] = new PointersList<T>(max_list_size);
    }

    for (int i = 0; i < length; ++i) {
        int size;
        file.read(reinterpret_cast<char*>(&size), sizeof(size));

        for (int j = 0; j < size; ++j) {
            int strLen;
            file.read(reinterpret_cast<char*>(&strLen), sizeof(strLen));
            
            char* str = new char[strLen];
            file.read(str, strLen);
            
            lists[i]->add(str);
        }
    }
    file.close();
}

template class PointersArray<char*>;
