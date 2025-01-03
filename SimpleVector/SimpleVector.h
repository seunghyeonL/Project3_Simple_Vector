#pragma once
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class SimpleVector
{
private:
    T* data;
    int currentSize;
    int currentCapacity;

protected:
    void resize(int newCapacity);

public:
    // iterator_traits 요구사항
    // 반복자에서 못찾으면 여기서 찾는듯(?)함

    // using difference_type = std::ptrdiff_t;
    using value_type = T;
    // using pointer = T *;
    // using reference = T &;
    // using iterator_category = std::random_access_iterator_tag;

    SimpleVector(int capacity = 10)
        : currentSize{0}, currentCapacity{capacity}
    {
        data = new T[capacity];
        cout << "---인스턴스 생성, data 배열 동적할당---" << endl;
    }

    SimpleVector(initializer_list<T> init)
    {
        int size = init.size();
        currentSize = size;
        currentCapacity = size > 10 ? size : 10;

        data = new T[size];
        cout << "---인스턴스 생성, data 배열 동적할당---" << endl;
        for (int i = 0; i < size; i++)
        {
            data[i] = *(init.begin() + i);
        }
    }

    SimpleVector(const SimpleVector& other)
    {
        currentSize = other.currentSize;
        currentCapacity = other.currentCapacity;
        data = new T[other.currentCapacity];
        cout << "---인스턴스 생성, data 배열 동적할당---" << endl;

        for (int i = 0; i < currentSize; i++)
        {
            data[i] = other.data[i];
        }
    }

    ~SimpleVector()
    {
        delete[] data;
        cout << "---인스턴스 소멸, data 배열 해제---" << endl;
    }

    T* begin();
    T* end();
    void push_back(const T& newEl);
    void pop_back();
    int size();
    int capacity();
    T& operator[](int idx);
    T& at(int idx);
    void sortData();
    void sortData(bool (*compare)(T a, T b));
};


template <typename T>
void SimpleVector<T>::resize(int newCapacity)
{
    if (newCapacity <= currentCapacity)
    {
        return;
    }

    T* newData = new T[newCapacity];
    cout << "---사이즈 증가로 인해, 새 data 배열 동적할당---" << endl;

    for (int i = 0; i < currentSize; i++)
    {
        newData[i] = data[i];
    }

    delete[] data;
    cout << "---사이즈 증가로 인해, 이전 data 해제---" << endl;
    data = newData;
    currentCapacity = newCapacity;
}

template <typename T>
T* SimpleVector<T>::begin()
{
    return data;
};

template <typename T>
T* SimpleVector<T>::end()
{
    return data + currentSize;
};

template <typename T>
void SimpleVector<T>::push_back(const T& newEl)
{
    if (currentSize == currentCapacity)
    {
        int newCapacity = currentCapacity + 5;
        resize(newCapacity);
    }

    data[currentSize++] = newEl;
}

template <typename T>
void SimpleVector<T>::pop_back()
{
    if (currentSize == 0)
    {
        return;
    }

    currentSize--;
}

template <typename T>
int SimpleVector<T>::size()
{
    return currentSize;
}

template <typename T>
int SimpleVector<T>::capacity()
{
    return currentCapacity;
}

template <typename T>
T& SimpleVector<T>::operator[](int idx)
{
    return data[idx];
}

template <typename T>
T& SimpleVector<T>::at(int idx)
{
    if (idx < 0 || idx >= currentSize)
    {
        throw out_of_range("인덱스 벗어났음");
    }
    return data[idx];
}

template <typename T>
void SimpleVector<T>::sortData()
{
    sort(begin(), end());
}

template <typename T>
void SimpleVector<T>::sortData(bool (*compare)(T a, T b))
{
    sort(begin(), end(), compare);
}
