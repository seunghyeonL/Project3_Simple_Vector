#pragma once
#include <functional>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class SimpleVector {
  private:
    struct CustomDeleter {
        void operator()(T *p) {
            delete[] p;
            cout << "data 배열 해제" << endl;
        }
    };
    unique_ptr<T[], function<void(T *)>> data;
    int currentSize;
    int currentCapacity;

  protected:
    void resize(int newCapacity);

  public:
    // 정적 멤버함수로 deleter 선언
    // static void CustomDeleter(T *p) {
    //     delete[] p;
    //     cout << "data 배열 해제" << endl;
    // }
    // functor로 하면 private로 옮겨도 됨.
    // struct CustomDeleter {
    //     void operator()(T *p) {
    //         delete[] p;
    //         cout << "data 배열 해제" << endl;
    //     }
    // };

    // iterator_traits 요구사항
    // 포인터는 대충 만족한다고 들음(불확실)
    // 반복자에서 못찾으면 여기서 찾는듯(?)함
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::random_access_iterator_tag;

    SimpleVector(int capacity = 10)
        : currentSize{0}, currentCapacity{capacity},
          data(nullptr, CustomDeleter()) {
        data.reset(new T[capacity]);
        cout << "---인스턴스 생성, data 배열 동적할당---" << endl;
    }

    SimpleVector(initializer_list<T> init) : data(nullptr, CustomDeleter()) {
        int size = init.size();
        currentSize = size;
        currentCapacity = size > 10 ? size : 10;
        data.reset(new T[size]);
        cout << "---인스턴스 생성, data 배열 동적할당---" << endl;
        for (int i = 0; i < size; i++) {
            data[i] = *(init.begin() + i);
        }
    }
    SimpleVector(const SimpleVector &other) : data(nullptr, CustomDeleter()) {
        currentSize = other.currentSize;
        currentCapacity = other.currentCapacity;
        data.reset(new T[other.currentCapacity]);
        cout << "---인스턴스 생성, data 배열 동적할당---" << endl;

        for (int i = 0; i < currentSize; i++) {
            data[i] = other.data[i];
        }
    }
    ~SimpleVector() {
        cout << "---인스턴스 소멸---" << endl;
    }

    T *begin();
    T *end();
    void push_back(const T &newEl);
    void pop_back();
    int size();
    int capacity();
    T &operator[](int idx);
    T &at(int idx);
    void sortData();
    void sortData(bool (*compare)(T &a, T &b));
};

template <typename T>
void SimpleVector<T>::resize(int newCapacity) {
    if (newCapacity <= currentCapacity) {
        return;
    }

    T *newData = new T[newCapacity];

    for (int i = 0; i < currentSize; i++) {
        newData[i] = data[i];
    }

    cout << "---사이즈 증가로 인해, 새 data 배열 동적할당---" << endl;
    data.reset(newData);

    currentCapacity = newCapacity;
}

template <typename T>
T *SimpleVector<T>::begin() {
    return data.get();
};

template <typename T>
T *SimpleVector<T>::end() {
    return data.get() + currentSize;
};

template <typename T>
void SimpleVector<T>::push_back(const T &newEl) {
    if (currentSize == currentCapacity) {
        int newCapacity = currentCapacity + 5;
        resize(newCapacity);
    }

    data[currentSize++] = newEl;
}

template <typename T>
void SimpleVector<T>::pop_back() {
    if (currentSize == 0) {
        return;
    }

    currentSize--;
}

template <typename T>
int SimpleVector<T>::size() {
    return currentSize;
}

template <typename T>
int SimpleVector<T>::capacity() {
    return currentCapacity;
}

template <typename T>
T &SimpleVector<T>::operator[](int idx) {
    return data[idx];
}

template <typename T>
T &SimpleVector<T>::at(int idx) {
    if (idx < 0 || idx >= currentSize) {
        throw out_of_range("인덱스 벗어났음");
    }
    return data[idx];
}

template <typename T>
void SimpleVector<T>::sortData() {
    sort(begin(), end());
}

template <typename T>
void SimpleVector<T>::sortData(bool (*compare)(T &a, T &b)) {
    sort(begin(), end(), compare);
}
