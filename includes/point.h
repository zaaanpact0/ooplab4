#ifndef POINT_H
#define POINT_H

#include <memory>
#include <concepts>
#include <iostream>

template<typename T>
concept Scalar = std::is_scalar_v<T>;

template<Scalar T>
class Point {
private:
    T x_;
    T y_;
    
public:
    Point();
    Point(T x, T y);
    
    T x() const;
    T y() const;
    
    void setX(T x);
    void setY(T y);
    
    Point<T> operator+(const Point<T>& other) const;
    Point<T> operator/(T divisor) const;
    bool operator==(const Point<T>& other) const;
    
    template<Scalar U>
    friend std::ostream& operator<<(std::ostream& os, const Point<U>& point);
};

#endif