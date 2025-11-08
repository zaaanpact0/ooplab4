#include "figure.h"

template<Scalar T>
Figure<T>::operator double() const {
    return area();
}

template<Scalar T>
bool Figure<T>::operator==(const Figure<T>& other) const {
    if (vertices_.size() != other.vertices_.size()) {
        return false;
    }

    for (size_t i = 0; i < vertices_.size(); i++) {
        if (!(vertices_[i] == other.vertices_[i])) {
            return false;
        }
    }

    return true;
}

template<Scalar T>
void Figure<T>::printInfo() const {
    std::cout << "Geometric center: " << geometricCenter() << std::endl;
    std::cout << "Area: " << area() << std::endl;
    std::cout << "Vertices: ";
    printVertices(std::cout);
    std::cout << std::endl;
}

template class Figure<int>;
template class Figure<double>;
template class Figure<float>;