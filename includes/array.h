#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>
#include <iostream>

template<typename T>
class Array {
private:
    std::unique_ptr<T[]> data;
    size_t capacity;
    size_t size_;
    
    void resize(size_t new_capacity);
    
public:
    Array();
    Array(size_t initial_capacity);
    Array(const Array& other);
    Array(Array&& other) noexcept;
    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;
    
    void push_back(const T& value);
    void push_back(T&& value);
    void erase(size_t index);
    
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    
    size_t size() const { return size_; }
    size_t getCapacity() const { return capacity; }
    
    T* begin() { return data.get(); }
    T* end() { return data.get() + size_; }
    const T* begin() const { return data.get(); }
    const T* end() const { return data.get() + size_; }

    double totalArea() const;
    void printAll() const;
};


#endif
