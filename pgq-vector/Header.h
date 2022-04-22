// Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>

#pragma once
#include <exception>
#include <iostream>
#include <stdexcept>

template <class T>
class vector {
public:
    vector();
    vector(const vector<T>& vec);
    explicit vector(const size_t& size);
    ~vector();

    template <typename ValueType>
    class Iterator
        : public std::iterator<std::random_access_iterator_tag, ValueType> {
    public:
        Iterator() : pointer__(nullptr) {}
        explicit Iterator(ValueType* ptr) : pointer__(ptr) {}
        ValueType& operator+(const int& n) { return *(pointer__ + n); }
        ValueType& operator-(const int& n) { return *(pointer__ - n); }

        ValueType& operator++(int) { return *pointer__++; }
        ValueType& operator--(int) { return *pointer__--; }
        ValueType& operator++() { return *(++pointer__); }
        ValueType& operator--() { return *(--pointer__); }

        bool operator!=(const Iterator& it) { return pointer__ != it.pointer__; }
        bool operator==(const Iterator& it) { return pointer__ == it.pointer__; }
        ValueType& operator->() { return *pointer__; }
        ValueType& operator*() { return *pointer__; }
        friend class vector;

    private:
        ValueType* pointer__;
    };
    using iterator = Iterator<T>;

    vector<T>& operator=(const vector<T>& vec);
    template <class T1>
    friend std::ostream& operator<<(std::ostream& out, const vector<T1>& vec);
    T& operator[](const size_t& index);
    T operator[](const size_t& index) const;
    T at(const size_t& index) const;
    T& at(const size_t& index);
    T* front() const noexcept;
    T* back() const noexcept;
    T* data() const noexcept;
    iterator begin() {
        iterator it;
        it.pointer__ = data__;
        return it;
    }
    iterator end() {
        iterator it;
        it.pointer__ = &data__[size__];
        return it;
    }
    [[nodiscard]] bool empty() const noexcept;
    [[nodiscard]] size_t size() const noexcept;
    void reserve();
    size_t capacity();
    void clear() noexcept;
    void insert(const size_t& index, const T& value);
    void push_back(const T& val);
    void pop_back();
    void swap(vector<T>& vec) noexcept;

private:
    T* data__;
    size_t size__;
    size_t capacity__;
};
template <class T>
vector<T>::vector() : size__(0), capacity__(5) {
    data__ = new T[capacity__];
    for (size_t i = 0; i < capacity__; ++i) data__[i] = 0;
}
template <class T>
vector<T>::vector(const size_t& size) : size__(size), capacity__(size) {
    data__ = new T[size__];
    for (size_t i = 0; i < size__; ++i) data__[i] = 0;
}
template <class T>
vector<T>::vector(const vector<T>& vec)
    : size__(vec.size__), capacity__(vec.capacity__) {
    data__ = new T[size__];
    for (size_t i = 0; i < vec.size__; ++i) {
        data__[i] = vec.data__[i];
    }
}
template <class T>
vector<T>::~vector() {
    delete[] data__;
}
template <class T>
vector<T>& vector<T>::operator=(const vector<T>& vec) {
    if (&vec != this) {
        size__ = vec.size__;
        data__ = new T[size__];
        for (size_t i = 0; i < size__; ++i) {
            data__[i] = vec.data__[i];
        }
    }
    return *this;
}
template <class T1>
std::ostream& operator<<(std::ostream& out, const vector<T1>& vec) {
    for (size_t i = 0; i < vec.size__; ++i) out << vec[i] << ' ';
    return out;
}
template <class T>
T& vector<T>::operator[](const size_t& index) {
    return data__[index];
}
template <class T>
T vector<T>::operator[](const size_t& index) const {
    return data__[index];
}
template <class T>
inline T vector<T>::at(const size_t& index) const {
    if (index >= capacity__) throw std::out_of_range("| Index was out of range!");
    return data__[index];
}
template <class T>
inline T& vector<T>::at(const size_t& index) {
    if (index >= capacity__) throw std::out_of_range("| Index was out of range!");
    return data__[index];
}
template <class T>
inline T* vector<T>::front() const noexcept {
    return data__;
}
template <class T>
inline T* vector<T>::back() const noexcept {
    return (data__ + size__ - 1);
}
template <class T>
inline T* vector<T>::data() const noexcept {
    return data__;
}
template <class T>
bool vector<T>::empty() const noexcept {
    return size__ == 0;
}
template <class T>
inline size_t vector<T>::capacity() {
    return capacity__;
}
template <class T>
size_t vector<T>::size() const noexcept {
    return size__;
}
template <class T>
void vector<T>::clear() noexcept {
    delete[] data__;
    data__ = new T[1];
    data__[0] = 0;
    size__ = 0;
    capacity__ = 0;
}
template <class T>
inline void vector<T>::swap(vector<T>& vec) noexcept {
    if (&vec != this) {
        for (size_t i = 0; i < (vec.size() > size__ ? size__ : vec.size()); ++i)
            std::swap(data__[i], vec.data__[i]);
    }
}
template <class T>
inline void vector<T>::insert(const size_t& index, const T& value) {
    (*this).at(index) = value;
}
template <class T>
void vector<T>::reserve() {
    if (size__ <= 1) {
        capacity__ = static_cast<size_t>(size__ * 2);
    }
    else {
        capacity__ = static_cast<size_t>(size__ * 1.5);
    }
    T* temp_data = new T[size__];
    for (size_t i = 0; i < size__; ++i) temp_data[i] = data__[i];
    data__ = new T[capacity__];
    for (size_t i = 0; i < size__; ++i) data__[i] = temp_data[i];
    delete[] temp_data;
}
template <class T>
void vector<T>::pop_back() {
    if (empty()) {
        return;
    }
    --size__;
    if (size__ < (capacity__ / 2) && capacity__ / 1.5 > 5) {
        reserve();
    }
}
template <class T>
inline void vector<T>::push_back(const T& val) {
    if (size__ >= capacity__) {
        reserve();
    }
    ++size__;
    data__[size__ - 1] = val;
}
