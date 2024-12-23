#ifndef LISTELEM_HPP
#define LISTELEM_HPP

#include <fstream>
#include <cstring>
#include <stdexcept>

template <class T>
struct ListElem {
    T* objects;
    int countObj;
    ListElem<T>* pNext;

    ListElem() : objects(nullptr), countObj(0), pNext(nullptr) {}
    ~ListElem() { delete[] objects; }

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