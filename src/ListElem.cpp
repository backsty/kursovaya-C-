#include "ListElem.h"

// Реализации специализаций
template <>
void ListElem<char*>::serialize(std::ofstream &outFile) {
    outFile.write(reinterpret_cast<const char*>(&countObj), sizeof(countObj));
    for(int i = 0; i < countObj; i++) {
        size_t length = objects[i] ? strlen(objects[i]) : 0;
        outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
        outFile.write(objects[i], static_cast<std::streamsize>(length));
    }
}

template <>
void ListElem<char*>::deserialize(std::ifstream &inFile) {
    inFile.read(reinterpret_cast<char*>(&countObj), sizeof(countObj));
    objects = new char*[countObj];
    for(int i = 0; i < countObj; i++) {
        int length;
        inFile.read(reinterpret_cast<char*>(&length), sizeof(length));
        objects[i] = new char[length + 1];
        inFile.read(objects[i], length);
        objects[i][length] = '\0';
    }
}