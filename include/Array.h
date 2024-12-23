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
    Array(int size, int MaxSize);
    ~Array();

    void AddElem();
    void AddElem(int position);
    void DelElem(int position);
    void SortALL();
    void ShowAll();
    void Balance();
    void SaveToFile(const char* filename);
    void LoadFromFile(const char* filename);

private:
    ListElem<T> **Arr;
    bool IsListFull(int index);
    void Change(T a[], int first, int second);
    int FindMax(T a[], int max);
    void Sort(T b[], int max);

    int MaxCount;   // Максимальная длина списка
    int CurSize;    // Текущий размер односвязного списка
    int ArrSize;    // Размер массива указателей
    int pointer;    // Указатель на вставку элемента
};

#endif