#include "MyVector.h"
#include "MyString.h"
#include "Row.h"

template <typename T>
MyVector<T>::MyVector() : MyVector(8)
{
}

template <typename T>
MyVector<T>::~MyVector() {
    free();
}

template <typename T>
void MyVector<T>::push_back(const T& value) {
    if (size >= capacity) {
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        reserve(newCapacity);
    }
    data[size++] = value;
}

template <typename T>
void MyVector<T>::push_back()
{
    if (size >= capacity) {
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        reserve(newCapacity);
    }

    data[size++] = T();
}

template <typename T>
void MyVector<T>::pop_back() {
    if (size > 0) {
        size--;
    }
}

template <typename T>
T& MyVector<T>::operator[](size_t index) {
    if (index >= size)
        throw std::out_of_range("Index out of range");

    return data[index];
}

template <typename T>
const T& MyVector<T>::operator[](size_t index) const {
    if (index >= size)
        throw std::out_of_range("Index out of range");

    return data[index];
}

template <typename T>
size_t MyVector<T>::getSize() const {
    return size;
}

template <typename T>
size_t MyVector<T>::getCapacity() const {
    return capacity;
}

template <typename T>
void MyVector<T>::copyFrom(const MyVector& other)
{
    size = other.size;
    capacity = other.capacity;
    data = new T[capacity];

    for (size_t i = 0; i < size; i++)
    {
        data[i] = other.data[i];
    }
}

template <typename T>
void MyVector<T>::free() {
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
    size = 0;
    capacity = 0;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

template <typename T>
MyVector<T>::MyVector(const MyVector& other)
{
    copyFrom(other);
}

template <typename T>
MyVector<T>::MyVector(size_t newCapacity) : size(0), capacity(newCapacity)
{
    data = new T[capacity];
}

template <typename T>
void MyVector<T>::reserve(size_t newCapacity) {
    if (newCapacity <= capacity) {
        return;
    }

    T* newData = new T[newCapacity];
    if (data != nullptr) {
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
    }
    data = newData;
    capacity = newCapacity;
}

// Explicit instantiations for common types
template class MyVector<int>;
template class MyVector<float>;
template class MyVector<double>;
template class MyVector<char>;
template class MyVector<Row>;
template class MyVector<size_t>;
template class MyVector<MyString>;
