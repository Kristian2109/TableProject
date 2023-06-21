#ifndef MYVECTOR_H
#define MYVECTOR_H

template <typename T>
class MyVector {
private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 8;
    void copyFrom(const MyVector& other);
    void free();

public:
    MyVector();
    ~MyVector();
    MyVector(size_t newCapacity);

    MyVector<T>& operator=(const MyVector& other);
    MyVector(const MyVector& other);

    void push_back(const T& value);
    void push_back();
    void pop_back();
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    size_t getSize() const;
    size_t getCapacity() const;

private:
    void reserve(size_t newCapacity);
};

#endif  // MYVECTOR_H

