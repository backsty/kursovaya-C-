#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string>

#include "PointersList.h"
#include "Node.h"

template <typename T>
PointersList<T>::PointersList(int max_size) : head(nullptr), max_size(max_size), current_size(0) {}

template <class T>
PointersList<T>::~PointersList()
{
    Node<T>* current = head;
    while (current) {
        Node<T>* temp = current->next;
        delete current; 
        current = temp;
    }
}

template <class T>
void PointersList<T>::display() const {
    Node<T>* current = head;
    while (current) {
        if (current->data) {
            std::cout << *(current->data) << " ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}

template <class T>
void PointersList<T>::add(const T& element) {
    if (is_full()) {
        throw std::overflow_error("Список полон");
    }
    Node<T>* newNode = new Node<T>();
    newNode->data = new T(element);

    if (!head) {
        head = newNode;
    } else {
        Node<T>* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    ++current_size;
}

template <class T>
void PointersList<T>::insert(int position, T& element) {
    if (position < 0 || position > current_size) {
        throw std::out_of_range("Недопустимая позиция");
    }
    if (is_full()) {
        throw std::overflow_error("Список полон");
    }
    Node<T>* newNode = new Node<T>();
    newNode->data = new T(element);

    if (position == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        Node<T>* current = head;
        for (int i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    ++current_size;
}

template <class T>
void PointersList<T>::remove(int position) {
    if (position < 0 || position >= current_size) {
        throw std::out_of_range("Недопустимая позиция");
    }
    Node<T>* toDelete = head;
    if (position == 0) {
        head = head->next;
    } else {
        Node<T>* prev = nullptr;
        for (int i = 0; i < position; ++i) {
            prev = toDelete;
            toDelete = toDelete->next;
        }
        prev->next = toDelete->next;
    }
    delete toDelete;
    --current_size;
}

template <class T>
T* PointersList<T>::get(int position) {
    if (position < 0 || position >= current_size) {
        throw std::out_of_range("Недопустимая позиция");
    }
    Node<T>* current = head;
    for (int i = 0; i < position; ++i) {
        current = current->next;
    }
    return current->data;
}

template<>
void PointersList<char*>::sort_list() {
    if (!head || !head->next) return;
    bool sorted = false;

    do {
        sorted = true;
        Node<char*>* current = head;

        while (current->next) {
            if (strcmp(*(current->data), *(current->next->data)) > 0) {
                char** temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                sorted = false;
            }
            current = current->next;
        }
    } while (!sorted);
}

template class PointersList<char*>;
