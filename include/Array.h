#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "ListElem.h"
#include <iostream>
#include <fstream>
#include <cstring>

template <class T>
class Array {
public:
    Array();
    explicit Array(int size = 10, int MaxSize = 3);
    ~Array();

    void AddElem();
    void AddElem(int position);
    void AddElementAtPosition(T element, int arrayIndex, int nodeIndex, int position);
    void AddToArrayIndex(int arrayIndex);
    void AddToListNode(int arrayIndex, int nodeIndex);
    bool ResizeArray(int newSize);
    
    void DelElem(int arrayIndex, int nodeIndex, int position);
    void DelElemRange(int arrayIndex, int nodeIndex, int startPos, int endPos);
    
    void ShowAll();
    int CountTotalElements();
    
    void SortALL();
    void Balance();
    
    void SaveToFile(const char* filename);
    void LoadFromFile(const char* filename);

private:
    ListElem<T> **Arr;
    ListElem<T>* InputNewElement();
    bool IsListFull(int index);

    static const int RESIZE_FACTOR = 2;

    int MaxCount;   // Максимальная длина списка
    int CurSize;    // Текущий размер односвязного списка
    int ArrSize;    // Размер массива указателей
    int pointer;    // Указатель на вставку элемента
};

#endif