#include "point.h"

template<Scalar T>
Point<T>::Point() : x_(0), y_(0) {}

template<Scalar T>
Point<T>::Point(T x, T y) : x_(x), y_(y) {}

template<Scalar T>
T Point<T>::x() const { return x_; }

template<Scalar T>
T Point<T>::y() const { return y_; }

template<Scalar T>
void Point<T>::setX(T x) { x_ = x; }

template<Scalar T>
void Point<T>::setY(T y) { y_ = y; }

template<Scalar T>
Point<T> Point<T>::operator+(const Point<T>& other) const {
    return Point<T>(x_ + other.x_, y_ + other.y_);
}

template<Scalar T>
Point<T> Point<T>::operator/(T divisor) const {
    return Point<T>(x_ / divisor, y_ / divisor);
}

template<Scalar T>
bool Point<T>::operator==(const Point<T>& other) const {
    return x_ == other.x_ && y_ == other.y_;
}

template<Scalar T>
std::ostream& operator<<(std::ostream& os, const Point<T>& point) {
    os << "(" << point.x_ << ", " << point.y_ << ")";
    return os;
}

template class Point<int>;
template class Point<double>;
template class Point<float>;

template std::ostream& operator<<(std::ostream& os, const Point<int>& point);
template std::ostream& operator<<(std::ostream& os, const Point<double>& point);
template std::ostream& operator<<(std::ostream& os, const Point<float>& point);