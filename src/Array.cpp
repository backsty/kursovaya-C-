#include "Array.h"
#include "ListElem.h"
#include <iostream>
#include <fstream>

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

// Функция простого добавления элемента в список
template <class T>
void Array<T>::AddElem() {
    if (pointer >= ArrSize) {
        std::cout << "Error: Array is full." << std::endl;
        return;
    }

    // Ввод кол-во элементов
    int count = 0;
    std::cout << "Enter count of elements: ";
    std::cin >> count;

    if (count <= 0) {
        std::cout << "Invalid count of elements" << std::endl;
        return;
    }

    ListElem<T>* NewElem;
    try {
        NewElem = new ListElem<T>;
        NewElem->countObj = count;
        NewElem->objects = new T[count];
        NewElem->pNext = nullptr;

        for (int i = 0; i < count; ++i) {
            NewElem->objects[i] = new char[100];
            std::cout << "Enter element #" << (i + 1) << ": ";
            std::cin >> NewElem->objects[i];
        }
    } catch (std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        if (NewElem) {
            for (int i = 0; i < count; ++i) {
                delete[] NewElem->objects[i];
            }
            delete[] NewElem->objects;
            delete NewElem;
        }
        return;
    }

    // Добавление нового элемента в массив
    if (Arr[pointer] == nullptr) {
        Arr[pointer] = NewElem;
    } else {
        ListElem<T>* cur = Arr[pointer];
        while (cur->pNext != nullptr) {
            cur = cur->pNext;
        }
        cur->pNext = NewElem;
    }

    // Обновление указателей
    CurSize++;
    if (CurSize >= MaxCount) {
        pointer++;
        CurSize = 0;
    }
}

// Функция сортировки элементов
template <class T>
void Array<T>::Change(T a[], int first, int second) {
    if (first == second) return;
    T temp = a[second];
    a[second] = a[first];
    a[first] = temp;
}

template <class T>
int Array<T>::FindMax(T a[], int max) {
    int imax = 0;
    for (int i = 0; i < max; i++) {
        if (a[imax] < a[i]) imax = i;
    }
    return imax;
}

template <class T>
void Array<T>::Sort(T b[], int max) {
    for (int i = max - 1; i > 0; i--) {
        int i1 = FindMax(b, i);
        Change(b, i, i1);
    }
}

template <class T>
void Array<T>::SortALL() {
    for (int i = 0; i < ArrSize; i++) {
        ListElem<T> *cur = Arr[i];
        while(cur != nullptr) {
            Sort(cur->objects,cur->countObj);
            cur = cur->pNext;
        }
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

// Функция добавления элемента по позиции
template <class T>
void Array<T>::AddElem(int position) {
    if (position <= 0) {
        std::cout << "Incorrect position" << std::endl;
        return;
    }

    int index = 0;
    int maxPosition = ArrSize * MaxCount;

    if (position > maxPosition) {
        std::cout << "The position exceeds the size of the structure" << std::endl;
        return;
    }

    while (position > MaxCount) {
        index++;
        position -= MaxCount;
    }

    ListElem<T> *currentNode = Arr[index];

    if (currentNode == nullptr) {
        int elementCount = 0;
        std::cout << "Enter count of elements=";
        std::cin >> elementCount;

        if (elementCount <= 0) {
            std::cout << "Non of elements" << std::endl;
            return;
        }

        ListElem<T> *newNode;

        try {
            newNode = new ListElem<T>;
            newNode->countObj = elementCount;
            newNode->objects = new T[elementCount];  // Выделение памяти для объектов

            for (int i = 0; i < elementCount; i++) {
                std::cout << "Enter element: ";
                std::cin >> newNode->objects[i];
            }

            Arr[index] = newNode;
            newNode->pNext = nullptr;
            CurSize++;
        } catch (std::bad_alloc &e) {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            if (newNode) {
                delete[] newNode->objects;
                delete newNode;
            }
            return;
        }
        return;
    }

    if (index >= ArrSize) {
        AddElem(position); // Рекурсивный вызов для следующего индекса
        return;
    }

    if (IsListFull(index)) {
        ListElem<T> *pcur = Arr[index];

        while(pcur->pNext != nullptr) {
            pcur = pcur->pNext;
        }

        int count = 0;
        std::cout << "Enter count of elements=";
        std::cin >> count;

        if (count <= 0) {
            std::cout << "Non of elements to add" << std::endl;
            return;
        }

        ListElem<T>* NewElem;
        try {
            NewElem = new ListElem<T>;
            NewElem->countObj = count;
            NewElem->objects = new T[count];

            for (int i = 0; i < count; i++) {
                std::cout << "Enter element: ";
                std::cin >> NewElem->objects[i];
            }

            pcur->pNext = NewElem;
            NewElem->pNext = nullptr;
            CurSize++;
        } catch (std::bad_alloc& e) {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            if (NewElem) {
                delete[] NewElem->objects;
                delete NewElem;
            }
            return;
        }
        return;
    }

    if (position == 1) {
        int count = 0;
        std::cout << "Enter count of elements=";
        std::cin >> count;

        if (count <= 0) {
            std::cout << "Non of elements" << std::endl;
            return;
        }

        ListElem<T>* NewElem;
        try {
            NewElem = new ListElem<T>;
            NewElem->countObj = count;
            NewElem->objects = new T[count];

            for (int i = 0; i < count; i++) {
                std::cout << "Enter element: ";
                std::cin >> NewElem->objects[i];
            }

            NewElem->pNext = Arr[index];
            Arr[index] = NewElem;
            CurSize++;
        } catch (std::bad_alloc& e) {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            if (NewElem) {
                delete[] NewElem->objects;
                delete NewElem;
            }
            return;
        }
        return;
    } else {
        int count = 0;
        std::cout << "Enter count of elements=";
        std::cin >> count;

        if (count <= 0) {
            std::cout << "Non of elements" << std::endl;
            return;
        }

        ListElem<T>* NewElem;
        try {
            NewElem = new ListElem<T>;
            NewElem->countObj = count;
            NewElem->objects = new T[count];

            for (int i = 0; i < count; i++) {
                std::cout << "Enter element: ";
                std::cin >> NewElem->objects[i];
            }

            ListElem<T>* cur = Arr[index];
            ListElem<T>* pcur = Arr[index];
            int posCount = 0;

            while (cur != nullptr && posCount < position - 2) {
                posCount++;
                pcur = cur;
                cur = cur->pNext;
            }

            if (pcur == nullptr) {
                std::cout << "Position is out of range" << std::endl;
                delete[] NewElem->objects;
                delete NewElem;
                return;
            }

            NewElem->pNext = cur;
            pcur->pNext = NewElem;
            CurSize++;
        } catch (std::bad_alloc& e) {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            if (NewElem) {
                delete[] NewElem->objects;
                delete NewElem;
            }
            return;
        }
    }
}


// Функция удаления элемента с заданной позиции
template <class T>
void Array<T>::DelElem(int position) {
    // Проверка валидности позиции
    if (position <= 0) {
        std::cout << "Incorrect position" << std::endl;
        return;
    }

    // Вычисление индекса и локальной позиции
    int index = (position - 1) / MaxCount;
    int localPos = position - index * MaxCount;

    // Вычисление индекса и локальной позиции
    if (index >= ArrSize || Arr[index] == nullptr) {
        std::cout << "Element not found" << std::endl;
        return;
    }

    // Удаление первого элемента
    if (localPos == 1) {
        ListElem<T>* temp = Arr[index];  // Сохраняем первый элемент
        Arr[index] = temp->pNext;  // Обновляем указатель на первый элемент
        delete[] temp->objects;  // Освобождаем память для объектов
        delete temp;  // Освобождаем память для самого узла
        CurSize--;  // Уменьшаем общий размер
        return;
    }

    // Поиск элемента для удаления
    ListElem<T>* current = Arr[index];
    ListElem<T>* prev = nullptr;
    int currentPos = 1;

    while (current != nullptr && currentPos < localPos) {
        prev = current;
        current = current->pNext;
        currentPos++;
    }

    // Проверка найден ли элемент
    if (current == nullptr) {
        std::cout << "Element not found" << std::endl;
        return;
    }

    // Удаление элемента
    prev->pNext = current->pNext;
    delete[] current->objects;
    delete current;
    CurSize--;
}


// Функция вывода всех элементов
template <class T>
void Array<T>::ShowAll() {
    bool hasElements = false;

    for (int i = 0; i <= pointer; i++) {
        if (Arr[i] != nullptr) {
            hasElements = true;
            std::cout << " <<< Next Pointer-> >>> \n";
            ListElem<T> *cur = Arr[i];
            
            while (cur != nullptr) {
                std::cout << "Elem=";
                for (int j = 0; j < cur->countObj; j++) {
                    std::cout << cur->objects[j] << " ";
                }
                std::cout << "\n <<< Next list-> >>> \n";
                cur = cur->pNext;
            }
        }
    }

    if (!hasElements) {
        std::cout << "The structure is empty" << std::endl;
    }
}


// Функция балансировки структуры данных
template <class T>
void Array<T>::Balance() {
    if (ArrSize <= 0) return;

    // Подсчет общего числа элементов
    int totalElements = 0;
    for (int i = 0; i < ArrSize; ++i) {
        ListElem<T> *cur = Arr[i];
        while (cur != nullptr) {
            totalElements += cur->countObj;
            cur = cur->pNext;
        }
    }

    // Если массив пуст, нет необходимости в балансировке
    if (totalElements == 0) return;

    // Новый максимальный размер для элементов
    int newMaxCount = (totalElements + ArrSize - 1) / ArrSize;

    // Новый массив для хранения сбалансированных элементов
    ListElem<T> **newArr;
    try {
        newArr = new ListElem<T>*[ArrSize];
        for (int i = 0; i < ArrSize; ++i) {
            newArr[i] = nullptr;
        }
    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed." << e.what() << std::endl;
        return;
    }

    int currentIndex = 0;
    int currentCount = 0;
    ListElem<T> *currentElem = nullptr;

    // Перенос элементов из старого массива в новый
    for (int i = 0; i < ArrSize && currentIndex < ArrSize; ++i) {
        ListElem<T> *cur = Arr[i];
        while (cur != nullptr) {
            for (int j = 0; j < cur->countObj && currentIndex < ArrSize; ++j) {
                // Проверка на заполнение текущего элемента
                if (currentCount >= newMaxCount) {
                    currentIndex++;
                    if (currentIndex >= ArrSize) break;
                    currentCount = 0;
                    currentElem = nullptr;
                }

                // Если новый элемент еще не создан, создаем его
                if (currentElem == nullptr) {
                    currentElem = new ListElem<T>;
                    currentElem->countObj = 0;
                    currentElem->objects = new T[newMaxCount];
                    currentElem->pNext = nullptr;
                    newArr[currentIndex] = currentElem;
                }

                // Перенос объекта в новый элемент
                currentElem->objects[currentCount] = cur->objects[j];
                currentCount++;
                currentElem->countObj = currentCount;
            }

            // Очистка старого элемента
            ListElem<T> *temp = cur;
            cur = cur->pNext;
            delete[] temp->objects;
            delete temp;
        }
        Arr[i] = nullptr;
    }

    // Очистка старого массива и обновление указателей
    delete[] Arr;
    Arr = newArr;

    CurSize = (totalElements + newMaxCount - 1) / newMaxCount;
    MaxCount = newMaxCount;
    pointer = (CurSize > 0) ? CurSize - 1 : 0;
}




// Функция сохранения структуры данных в файл
template <class T>
void Array<T>::SaveToFile(const char* filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening the file for writing: " << filename << std::endl;
        return;
    }

    try {
        // Записываем размеры структуры
        outFile.write(reinterpret_cast<const char*>(&ArrSize), sizeof(ArrSize));
        outFile.write(reinterpret_cast<const char*>(&MaxCount), sizeof(MaxCount));
        outFile.write(reinterpret_cast<const char*>(&CurSize), sizeof(CurSize));
        outFile.write(reinterpret_cast<const char*>(&pointer), sizeof(pointer));

        // Записываем данные каждого списка
        for (int i = 0; i < ArrSize; ++i) {
            ListElem<T>* cur = Arr[i];
            bool hasNext = (cur != nullptr);
            outFile.write(reinterpret_cast<const char*>(&hasNext), sizeof(hasNext));

            while (cur != nullptr) {
                cur->serialize(outFile);
                cur = cur->pNext;
                hasNext = (cur != nullptr);
                outFile.write(reinterpret_cast<const char*>(&hasNext), sizeof(hasNext));
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error when writing to a file: " << e.what() << std::endl;
    }

    outFile.close();
}

// Функция загрузки структуры данных из файла
template <class T>
void Array<T>::LoadFromFile(const char* filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening the file for reading: " << filename << std::endl;
        return;
    }

    // Очищаем текущую структуру
    for (int i = 0; i < ArrSize; ++i) {
        while (Arr[i] != nullptr) {
            ListElem<T>* temp = Arr[i];
            Arr[i] = Arr[i]->pNext;
            delete[] temp->objects;
            delete temp;
        }
    }
    delete[] Arr;

    try {
        // Читаем размеры структуры
        inFile.read(reinterpret_cast<char*>(&ArrSize), sizeof(ArrSize));
        inFile.read(reinterpret_cast<char*>(&MaxCount), sizeof(MaxCount));
        inFile.read(reinterpret_cast<char*>(&CurSize), sizeof(CurSize));
        inFile.read(reinterpret_cast<char*>(&pointer), sizeof(pointer));

        // Создаем новую структуру
        Arr = new ListElem<T>*[ArrSize];
        for (int i = 0; i < ArrSize; ++i) {
            Arr[i] = nullptr;
        }

        // Читаем данные каждого списка
        for (int i = 0; i < ArrSize; ++i) {
            bool hasNext;
            inFile.read(reinterpret_cast<char*>(&hasNext), sizeof(hasNext));

            ListElem<T>** current = &Arr[i];
            while (hasNext) {
                *current = new ListElem<T>;
                (*current)->deserialize(inFile);
                current = &((*current)->pNext);
                inFile.read(reinterpret_cast<char*>(&hasNext), sizeof(hasNext));
            }
            *current = nullptr;
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при чтении из файла: " << e.what() << std::endl;

        // Очищаем структуру в случае ошибки
        for (int i = 0; i < ArrSize; ++i) {
            while (Arr[i] != nullptr) {
                ListElem<T>* temp = Arr[i];
                Arr[i] = Arr[i]->pNext;
                delete[] temp->objects;
                delete temp;
            }
        }
        delete[] Arr;
        Arr = nullptr;
    }

    inFile.close();
}


