#include "array.h"
#include "figure.h"
#include "rhombus.h"
#include "pentagon.h"
#include "hexagon.h"

template<typename T>
void Array<T>::resize(size_t new_capacity) {
    std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_capacity);
    
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = std::move(data[i]);
    }
    
    data = std::move(new_data);
    capacity = new_capacity;
}

template<typename T>
Array<T>::Array() : capacity(2), size_(0) {
    data = std::make_unique<T[]>(capacity);
}

template<typename T>
Array<T>::Array(size_t initial_capacity) 
    : capacity(initial_capacity), size_(0) {
    data = std::make_unique<T[]>(capacity);
}

template<typename T>
Array<T>::Array(const Array& other) 
    : capacity(other.capacity), size_(other.size_) {
    data = std::make_unique<T[]>(capacity);
    for (size_t i = 0; i < size_; ++i) {
        data[i] = other.data[i];
    }
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        capacity = other.capacity;
        size_ = other.size_;
        data = std::make_unique<T[]>(capacity);
        for (size_t i = 0; i < size_; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template<typename T>
Array<T>::Array(Array&& other) noexcept 
    : data(std::move(other.data)), capacity(other.capacity), size_(other.size_) {
    other.capacity = 0;
    other.size_ = 0;
}

template<typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this != &other) {
        data = std::move(other.data);
        capacity = other.capacity;
        size_ = other.size_;
        other.capacity = 0;
        other.size_ = 0;
    }
    return *this;
}

template<typename T>
void Array<T>::push_back(const T& value) {
    if (size_ >= capacity) {
        resize(capacity * 2);
    }
    data[size_++] = value;
}

template<typename T>
void Array<T>::push_back(T&& value) {
    if (size_ >= capacity) {
        resize(capacity * 2);
    }
    data[size_++] = std::move(value);
}

template<typename T>
void Array<T>::erase(size_t index) {
    if (index >= size_) return;
    
    for (size_t i = index; i < size_ - 1; ++i) {
        data[i] = std::move(data[i + 1]);
    }
    --size_;
}

template<typename T>
T& Array<T>::operator[](size_t index) {
    if (index >= size_) throw std::out_of_range("Index out of range");
    return data[index];
}

template<typename T>
const T& Array<T>::operator[](size_t index) const {
    if (index >= size_) throw std::out_of_range("Index out of range");
    return data[index];
}

template<typename T>
double Array<T>::totalArea() const {
    double total = 0.0;
    for (size_t i = 0; i < size_; ++i) {
        total += static_cast<double>(*data[i]);
    }
    return total;
}

template<typename T>
void Array<T>::printAll() const {
    std::cout << "Array contents (" << size_ << " elements):\n";
    for (size_t i = 0; i < size_; ++i) {
        std::cout << "Element " << i << ":\n";
        std::cout << "  " << *data[i] << "\n";
        
        auto center = data[i]->geometricCenter();
        std::cout << "  Center: (" << center.x() << ", " << center.y() << ")\n";
        std::cout << "  Area: " << data[i]->area() << "\n\n";
    }
}

template class Array<std::shared_ptr<Figure<int>>>;
template class Array<std::shared_ptr<Figure<double>>>;
template class Array<std::shared_ptr<Figure<float>>>;

template class Array<std::shared_ptr<Rhombus<int>>>;
template class Array<std::shared_ptr<Rhombus<double>>>;
template class Array<std::shared_ptr<Rhombus<float>>>;

template class Array<std::shared_ptr<Hexagon<int>>>;
template class Array<std::shared_ptr<Hexagon<double>>>;
template class Array<std::shared_ptr<Hexagon<float>>>;

template class Array<std::shared_ptr<Pentagon<int>>>;
template class Array<std::shared_ptr<Pentagon<double>>>;
template class Array<std::shared_ptr<Pentagon<float>>>;