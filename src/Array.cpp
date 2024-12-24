#include "Array.h"
#include "ListElem.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>


// 1. Конструкторы и деструктор
template <class T>
Array<T>::Array() : Arr(nullptr), MaxCount(0), CurSize(0), ArrSize(0), pointer(0) {}


template <class T>
Array<T>::Array(int size, int maxSize)
        : MaxCount(maxSize), CurSize(0), ArrSize(size), pointer(0) {
    if (size <= 0 || maxSize <= 0) {
        throw std::invalid_argument("Invalid array or max size");
    }

    Arr = new ListElem<T>*[size];
    for (int i = 0; i < size; ++i) {
        Arr[i] = nullptr;
    }
}


template <class T>
Array<T>::~Array() {
    if (Arr) {
        for (int i = 0; i < ArrSize; ++i) {
            ListElem<T> *current = Arr[i];
            while (current) {
                ListElem<T> *temp = current;
                current = current->pNext;
                delete[] temp->objects;
                delete temp;
            }
        }
        delete[] Arr;
        Arr = nullptr;
    }
}


// 2. Вспомогательные приватные методы
template <class T>
ListElem<T>* Array<T>::InputNewElement() {
    int count;
    std::cout << "Enter number of elements: ";
    std::cin >> count;
    if (count <= 0) {
        std::cout << "Invalid number of elements" << std::endl;
        return nullptr;
    }

    ListElem<T>* NewElem = nullptr;
    try {
        NewElem = new ListElem<T>;
        NewElem->countObj = count;
        NewElem->objects = new T[count];
        NewElem->pNext = nullptr;

        for (int i = 0; i < count; i++) {
            NewElem->objects[i] = new char[100];
            std::cout << "Enter element #" << (i + 1) << ": ";
            std::cin >> NewElem->objects[i];
        }
        return NewElem;
    }
    catch (std::bad_alloc& e) {
        if (NewElem) {
            if (NewElem->objects) {
                for (int i = 0; i < count; i++) {
                    delete[] NewElem->objects[i];
                }
                delete[] NewElem->objects;
            }
            delete NewElem;
        }
        std::cerr << "Memory allocation error: " << e.what() << std::endl;
        return nullptr;
    }
}


template <class T>
bool Array<T>::IsListFull(int index) {
    if (index >= ArrSize) return true;

    int count = 0;
    ListElem<T>* current = Arr[index];
    while (current != nullptr) {
        count += current->countObj;
        current = current->pNext;
    }
    return count >= MaxCount;
}


template <class T>
bool Array<T>::ResizeArray(int newSize) {
    if (newSize <= ArrSize) return false;
    
    try {
        ListElem<T>** newArr = new ListElem<T>*[newSize];
        
        for(int i = 0; i < ArrSize; i++) {
            newArr[i] = Arr[i];
        }
        
        for(int i = ArrSize; i < newSize; i++) {
            newArr[i] = nullptr;
        }
        
        delete[] Arr;
        Arr = newArr;
        ArrSize = newSize;
        return true;
    }
    catch(std::bad_alloc& e) {
        return false;
    }
}



// 3. Основные операции с элементами
template <class T>
void Array<T>::AddElem() {
    if (pointer >= ArrSize) {
        std::cout << "Error: Array is full." << std::endl;
        return;
    }

    ListElem<T>* NewElem = InputNewElement();
    if (!NewElem) return;

    if (Arr[pointer] == nullptr) {
        Arr[pointer] = NewElem;
    } else {
        ListElem<T>* cur = Arr[pointer];
        while (cur->pNext != nullptr) {
            cur = cur->pNext;
        }
        cur->pNext = NewElem;
    }

    CurSize++;
    if (CurSize >= MaxCount) {
        pointer++;
        CurSize = 0;
    }
}


template <class T>
void Array<T>::AddElem(int position) {
    if (position <= 0) {
        std::cout << "Invalid position" << std::endl;
        return;
    }

    int index = (position - 1) / MaxCount;
    if (index >= ArrSize) {
        std::cout << "Position exceeds array size" << std::endl;
        return;
    }

    if (IsListFull(index)) {
        std::cout << "List at index " << index << " is full" << std::endl;
        return;
    }

    ListElem<T>* NewElem = InputNewElement();
    if (!NewElem) return;

    int localPos = position - (index * MaxCount);

    if (Arr[index] == nullptr) {
        Arr[index] = NewElem;
        return;
    }

    if (localPos == 1) {
        NewElem->pNext = Arr[index];
        Arr[index] = NewElem;
        return;
    }

    ListElem<T>* current = Arr[index];
    ListElem<T>* prev = nullptr;
    int pos = 1;

    while (current != nullptr && pos < localPos) {
        prev = current;
        current = current->pNext;
        pos++;
    }

    if (prev != nullptr) {
        prev->pNext = NewElem;
        NewElem->pNext = current;
    }
}


template <class T>
void Array<T>::AddElementAtPosition(T element, int arrayIndex, int nodeIndex, int position) {
    if (arrayIndex < 0 || arrayIndex >= ArrSize) {
        std::cout << "Invalid array index" << std::endl;
        return;
    }

    if (nodeIndex <= 0) {
        std::cout << "Invalid node index" << std::endl;
        return;
    }

    if (position <= 0) {
        std::cout << "Invalid position" << std::endl;
        return;
    }

    ListElem<T>* current = Arr[arrayIndex];
    // ListElem<T>* prev = nullptr;
    int currentNode = 1;

    while (current != nullptr && currentNode < nodeIndex) {
        // prev = current;
        current = current->pNext;
        currentNode++;
    }

    if (current == nullptr) {
        std::cout << "Node not found" << std::endl;
        return;
    }

    try {
        T* newObjects = new T[current->countObj + 1];

        for(int i = 0; i < current->countObj + 1; i++) {
            newObjects[i] = new char[100];
        }

        if (position > current->countObj) {
            for (int i = 0; i < current->countObj; i++) {
                strcpy(newObjects[i], current->objects[i]);
            }
            strcpy(newObjects[current->countObj], element);
        } else {
            for (int i = 0; i < position - 1; i++) {
                strcpy(newObjects[i], current->objects[i]);
            }
            strcpy(newObjects[position - 1], element);
            for (int i = position - 1; i < current->countObj; i++) {
                strcpy(newObjects[i + 1], current->objects[i]);
            }
        }

        for(int i = 0; i < current->countObj; i++) {
            delete[] current->objects[i];
        }
        delete[] current->objects;

        current->objects = newObjects;
        current->countObj++;
    }
    catch (std::bad_alloc& e) {
        std::cout << "Memory allocation failed" << std::endl;
    }
}


template <class T>
void Array<T>::AddToArrayIndex(int arrayIndex) {
    if (arrayIndex < 0) {
        std::cout << "Invalid array index" << std::endl;
        return;
    }

    if (arrayIndex >= ArrSize) {
        int newSize = std::max(arrayIndex + 1, ArrSize * RESIZE_FACTOR);
        if (!ResizeArray(newSize)) {
            std::cout << "Failed to resize array" << std::endl;
            return;
        }
    }

    int count;
    std::cout << "Enter number of elements: ";
    std::cin >> count;
    if (count <= 0) {
        std::cout << "Invalid count" << std::endl;
        return;
    }

    ListElem<T>* NewElem = new ListElem<T>();
    NewElem->objects = new T[count];
    NewElem->countObj = count;
    NewElem->capacity = count;

    for(int i = 0; i < count; i++) {
        NewElem->objects[i] = new char[100];
        std::cout << "Enter element #" << (i + 1) << ": ";
        std::cin >> NewElem->objects[i];
    }

    if (Arr[arrayIndex] == nullptr) {
        Arr[arrayIndex] = NewElem;
    } else {
        ListElem<T>* current = Arr[arrayIndex];
        while(current->pNext != nullptr) {
            current = current->pNext;
        }
        current->pNext = NewElem;
    }
}


template <class T>
void Array<T>::AddToListNode(int arrayIndex, int nodeIndex) {
    if (arrayIndex < 0 || arrayIndex >= ArrSize) {
        std::cout << "Invalid array index" << std::endl;
        return;
    }

    ListElem<T>* current = Arr[arrayIndex];
    int currentNode = 1;
    
    while (current != nullptr && currentNode < nodeIndex) {
        current = current->pNext;
        currentNode++;
    }

    if (current == nullptr) {
        std::cout << "Node not found" << std::endl;
        return;
    }

    int count;
    std::cout << "Enter number of elements to add: ";
    std::cin >> count;
    if (count <= 0) {
        std::cout << "Invalid count" << std::endl;
        return;
    }

    if (current->countObj + count > current->capacity) {
        int newCapacity = std::max(current->countObj + count, 
                                 current->capacity * RESIZE_FACTOR);
        if (!current->ResizeNode(newCapacity)) {
            std::cout << "Failed to resize node" << std::endl;
            return;
        }
    }

    for(int i = 0; i < count; i++) {
        current->objects[current->countObj + i] = new char[100];
        std::cout << "Enter element #" << (i + 1) << ": ";
        std::cin >> current->objects[current->countObj + i];
    }
    current->countObj += count;
}



// 4. Операции удаления
template <class T>
void Array<T>::DelElem(int arrayIndex, int nodeIndex, int position) {
    if (arrayIndex < 0 || arrayIndex >= ArrSize) {
        std::cout << "Invalid array index" << std::endl;
        return;
    }

    if (nodeIndex <= 0) {
        std::cout << "Invalid node index" << std::endl;
        return;
    }

    if (position <= 0) {
        std::cout << "Invalid position" << std::endl;
        return;
    }

    ListElem<T>* current = Arr[arrayIndex];
    int currentNode = 1;

    while (current != nullptr && currentNode < nodeIndex) {
        current = current->pNext;
        currentNode++;
    }

    if (current == nullptr) {
        std::cout << "Node not found" << std::endl;
        return;
    }

    if (position > current->countObj) {
        std::cout << "Position exceeds node size" << std::endl;
        return;
    }

    T* newObjects = new T[current->countObj - 1];

    for (int i = 0; i < position - 1; i++) {
        newObjects[i] = new char[strlen(current->objects[i]) + 1];
        strcpy(newObjects[i], current->objects[i]);
    }

    for (int i = position; i < current->countObj; i++) {
        newObjects[i - 1] = new char[strlen(current->objects[i]) + 1];
        strcpy(newObjects[i - 1], current->objects[i]);
    }

    for (int i = 0; i < current->countObj; i++) {
        delete[] current->objects[i];
    }
    delete[] current->objects;

    current->objects = newObjects;
    current->countObj--;
}


template <class T>
void Array<T>::DelElemRange(int arrayIndex, int nodeIndex, int startPos, int endPos) {
    if (arrayIndex < 0 || arrayIndex >= ArrSize) {
        std::cout << "Invalid array index" << std::endl;
        return;
    }

    if (nodeIndex <= 0) {
        std::cout << "Invalid node index" << std::endl;
        return;
    }

    if (startPos <= 0 || endPos <= 0 || startPos > endPos) {
        std::cout << "Invalid range" << std::endl;
        return;
    }

    ListElem<T>* current = Arr[arrayIndex];
    if (current == nullptr) {
        std::cout << "Node not found" << std::endl;
        return;
    }

    int currentNode = 1;
    while (current != nullptr && currentNode < nodeIndex) {
        current = current->pNext;
        currentNode++;
    }

    if (current == nullptr) {
        std::cout << "Node not found" << std::endl;
        return;
    }

    if (startPos > current->countObj || endPos > current->countObj) {
        std::cout << "Position exceeds node size" << std::endl;
        return;
    }

    int elementsToDelete = endPos - startPos + 1;
    int newSize = current->countObj - elementsToDelete;
    
    if (newSize <= 0) {
        for (int i = 0; i < current->countObj; i++) {
            delete[] current->objects[i];
        }
        delete[] current->objects;
        current->objects = nullptr;
        current->countObj = 0;
        return;
    }

    T* newObjects = new T[newSize];

    int newIndex = 0;
    for (int i = 0; i < startPos - 1; i++) {
        newObjects[newIndex] = new char[strlen(current->objects[i]) + 1];
        strcpy(newObjects[newIndex++], current->objects[i]);
    }

    for (int i = endPos; i < current->countObj; i++) {
        newObjects[newIndex] = new char[strlen(current->objects[i]) + 1];
        strcpy(newObjects[newIndex++], current->objects[i]);
    }

    for (int i = 0; i < current->countObj; i++) {
        delete[] current->objects[i];
    }
    delete[] current->objects;

    current->objects = newObjects;
    current->countObj = newSize;
}



// 5. Операции отображения и подсчета
template <class T>
void Array<T>::ShowAll() {
    for (int i = 0; i < ArrSize; i++) {
        if (Arr[i] == nullptr) {
            std::cout << "Array Index [" << i << "] is empty.\n";
            continue;
        }

        std::cout << "Array Index [" << i << "]\n";

        ListElem<T>* cur = Arr[i];
        while (cur != nullptr) {
            std::cout << "  List Node: ";
            for (int j = 0; j < cur->countObj; j++) {
                std::cout << cur->objects[j] << " ";
            }
            std::cout << "\n";
            cur = cur->pNext;
        }
        std::cout << "\n";
    }
}


template <class T>
int Array<T>::CountTotalElements() {
    int total = 0;
    for (int i = 0; i < ArrSize; i++) {
        ListElem<T>* current = Arr[i];
        while (current != nullptr) {
            total += current->countObj;
            current = current->pNext;
        }
    }
    return total;
}



// 6. Операции сортировки и балансировки
template <class T>
void Array<T>::SortALL() {
    for (int i = 0; i < ArrSize; i++) {
        if (Arr[i] == nullptr) continue;

        ListElem<T>* current = Arr[i];
        while (current != nullptr) {
            for (int j = 0; j < current->countObj - 1; j++) {
                for (int k = 0; k < current->countObj - j - 1; k++) {
                    int num1 = atoi(current->objects[k]);
                    int num2 = atoi(current->objects[k + 1]);
                    
                    if (num1 > num2) {
                        char* temp = current->objects[k];
                        current->objects[k] = current->objects[k + 1];
                        current->objects[k + 1] = temp;
                    }
                }
            }
            current = current->pNext;
        }
    }
}


template <class T>
void Array<T>::Balance() {
    if (ArrSize <= 0) return;

    int totalElements = CountTotalElements();
    if (totalElements == 0) return;

    try {
        T* allElements = new T[totalElements];
        int currentIndex = 0;

        for (int i = 0; i < ArrSize; i++) {
            ListElem<T>* current = Arr[i];
            while (current != nullptr) {
                for (int j = 0; j < current->countObj; j++) {
                    allElements[currentIndex] = new char[strlen(current->objects[j]) + 1];
                    strcpy(allElements[currentIndex], current->objects[j]);
                    currentIndex++;
                }
                current = current->pNext;
            }
        }

        for (int i = 0; i < ArrSize; i++) {
            ListElem<T>* current = Arr[i];
            while (current != nullptr) {
                ListElem<T>* next = current->pNext;
                for(int j = 0; j < current->countObj; j++) {
                    delete[] current->objects[j];
                }
                delete[] current->objects;
                delete current;
                current = next;
            }
            Arr[i] = nullptr;
        }

        int elementsPerNode = 3;
        int nodesCount = (totalElements + elementsPerNode - 1) / elementsPerNode;

        currentIndex = 0;
        for (int i = 0; i < nodesCount && currentIndex < totalElements; i++) {
            int arrayIndex = i % ArrSize;
            int elementsInThisNode = std::min(elementsPerNode, totalElements - currentIndex);

            ListElem<T>* newNode = new ListElem<T>;
            newNode->objects = new T[elementsInThisNode];
            newNode->countObj = elementsInThisNode;
            newNode->pNext = nullptr;

            for (int j = 0; j < elementsInThisNode; j++) {
                newNode->objects[j] = new char[strlen(allElements[currentIndex + j]) + 1];
                strcpy(newNode->objects[j], allElements[currentIndex + j]);
            }

            if (Arr[arrayIndex] == nullptr) {
                Arr[arrayIndex] = newNode;
            } else {
                ListElem<T>* current = Arr[arrayIndex];
                while (current->pNext != nullptr) {
                    current = current->pNext;
                }
                current->pNext = newNode;
            }

            currentIndex += elementsInThisNode;
        }

        for (int i = 0; i < totalElements; i++) {
            delete[] allElements[i];
        }
        delete[] allElements;

    } catch (std::bad_alloc& e) {
        std::cout << "Memory allocation failed during balance" << std::endl;
    }
}











// 7. Файловые операции
template <class T>
void Array<T>::SaveToFile(const char* filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening file for writing" << std::endl;
        return;
    }

    // Запись размера структуры
    size_t totalSize = sizeof(int) * 2; // ArrSize + MaxCount
    for (int i = 0; i < ArrSize; i++) {
        ListElem<T>* current = Arr[i];
        while (current != nullptr) {
            totalSize += sizeof(int); // countObj
            for (int j = 0; j < current->countObj; j++) {
                totalSize += sizeof(size_t) + strlen(current->objects[j]); 
            }
            totalSize += sizeof(bool); // hasNext
            current = current->pNext;
        }
    }
    outFile.write(reinterpret_cast<const char*>(&totalSize), sizeof(size_t));

    // Запись размеров Array
    outFile.write(reinterpret_cast<const char*>(&ArrSize), sizeof(int));
    outFile.write(reinterpret_cast<const char*>(&MaxCount), sizeof(int));

    // Запись данных
    for (int i = 0; i < ArrSize; i++) {
        ListElem<T>* current = Arr[i];
        while (current != nullptr) {
            current->serialize(outFile);
            bool hasNext = (current->pNext != nullptr);
            outFile.write(reinterpret_cast<const char*>(&hasNext), sizeof(bool));
            current = current->pNext;
        }
    }
    outFile.close();
}


template <class T>
void Array<T>::LoadFromFile(const char* filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening file for reading" << std::endl;
        return;
    }

    // Чтение размера
    size_t totalSize;
    inFile.read(reinterpret_cast<char*>(&totalSize), sizeof(size_t));

    // Очистка и чтение размеров
    this->~Array();
    inFile.read(reinterpret_cast<char*>(&ArrSize), sizeof(int));
    inFile.read(reinterpret_cast<char*>(&MaxCount), sizeof(int));

    // Создание новой структуры
    Arr = new ListElem<T>*[ArrSize];
    for (int i = 0; i < ArrSize; i++) {
        Arr[i] = nullptr;
        ListElem<T>* last = nullptr;
        bool hasNext = true;

        while (hasNext && inFile.tellg() < totalSize) {
            ListElem<T>* newNode = new ListElem<T>();
            newNode->deserialize(inFile);
            
            if (Arr[i] == nullptr) Arr[i] = newNode;
            else last->pNext = newNode;
            last = newNode;
            
            inFile.read(reinterpret_cast<char*>(&hasNext), sizeof(bool));
        }
    }
    inFile.close();
}
