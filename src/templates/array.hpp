#ifndef ARRAY_H
#define ARRAY_H

#include <cstdint>
#include <stdexcept>


template <class T>
class Array {
    public:
        Array();
        Array(const Array<T>& other);
        Array<T>& operator=(const Array<T>& other);
        ~Array();
        Array<T>& operator+=(T element);
        T& operator[](uint32_t index);
        uint32_t get_size();
        void clear();

    private:
        T* data;
        uint32_t size;
        uint32_t max_size;
        void resize();
};

template <class T>
Array<T>::Array() {
    this->size = 0;
    this->max_size = 1;
    this->data = new T[this->max_size];
}

template <class T>
Array<T>::Array(const Array<T>& other) {
    this->size = other.size;
    this->max_size = other.max_size;
    this->data = new T[this->max_size];
    for (uint32_t i = 0; i < this->size; ++i) {
        this->data[i] = other.data[i];
    }
}

template <class T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
    if (this != &other) {
        delete[] this->data;
        this->size = other.size;
        this->max_size = other.max_size;
        this->data = new T[this->max_size];
        for (uint32_t i = 0; i < this->size; ++i) {
            this->data[i] = other.data[i];
        }
    }
    return *this;
}

template <class T>
Array<T>::~Array() {
    delete [] this->data;
}

template <class T>
Array<T>& Array<T>::operator+=(T element) {
    if (this->size == this->max_size) {
        this->resize();
    }
    data[this->size] = element;
    this->size++;
    return *this;
}

template <class T>
T& Array<T>::operator[](uint32_t index) {
    if (index >= this->size) {
        throw std::out_of_range("Index out of bounds.");
    }
    return this->data[index];
}

template <class T>
uint32_t Array<T>::get_size() {
    return this->size;
}

template <class T>
void Array<T>::clear() {
    delete [] this->data;
    this->max_size = 1;
    this->size = 0;
    this->data = new T[this->max_size];
}

template <class T>
void Array<T>::resize() {
    if (this->size == this->max_size) {
        uint32_t old_max_size = this->max_size;
        this->max_size *= 2;
        T* new_data = new T[this->max_size];
        for (uint32_t i = 0; i < old_max_size; i++) {
            new_data[i] = this->data[i];
        }
        delete [] this->data;
        this->data = new_data;
    }
}

#endif