#ifndef FIGURE_H
#define FIGURE_H

#include "point.h"
#include <iostream>
#include <memory>
#include <vector>

template<Scalar T>
class Figure {
protected:
    std::vector<Point<T>> vertices_;

public:
    virtual ~Figure() = default;
    
    virtual Point<T> geometricCenter() const = 0;
    virtual double area() const = 0;
    virtual void printVertices(std::ostream& os) const = 0;
    virtual void readFromStream(std::istream& is) = 0;
    
    virtual bool operator==(const Figure& other) const;
    
    friend std::ostream& operator<<(std::ostream& os, const Figure& fig) {
        fig.printVertices(os);
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Figure& fig) {
        fig.readFromStream(is);
        return is;
    }
    
    operator double() const;
    
    void printInfo() const;
};

#endif