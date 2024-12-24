#ifndef LISTELEM_HPP
#define LISTELEM_HPP

#include <fstream>
#include <cstring>
#include <stdexcept>

template <class T>
struct ListElem {
    T* objects;
    int countObj;
    int capacity;
    ListElem<T>* pNext;

    ListElem() : objects(nullptr), countObj(0), capacity(0), pNext(nullptr) {}
    ~ListElem() { delete[] objects; }

    bool ResizeNode(int newSize) {
        try {
            T* newObjects = new T[newSize];
            for(int i = 0; i < countObj; i++) {
                newObjects[i] = objects[i];
            }
            delete[] objects;
            objects = newObjects;
            capacity = newSize;
            return true;
        }
        catch(std::bad_alloc& e) {
            return false;
        }
    }

    // Базовые версии для не-char* типов
    void serialize(std::ofstream &outFile) {
        outFile.write(reinterpret_cast<const char*>(&countObj), sizeof(countObj));
        outFile.write(reinterpret_cast<const char*>(objects), countObj * sizeof(T));
    }

    void deserialize(std::ifstream &inFile) {
        inFile.read(reinterpret_cast<char*>(&countObj), sizeof(countObj));
        objects = new T[countObj];
        inFile.read(reinterpret_cast<char*>(objects), countObj * sizeof(T));
    }
};

template <> void ListElem<char*>::serialize(std::ofstream &outFile);
template <> void ListElem<char*>::deserialize(std::ifstream &inFile);

#endif