#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "figure.h"
#include <vector>
#include <cmath>

template<Scalar T>
class Rhombus : public Figure<T> {
private:
    std::vector<Point<T>> vertices;
    
public:
    Rhombus() = default;
    
    Rhombus(const std::vector<Point<T>>& verts) : vertices(verts) {
        if (verts.size() != 4) {
            throw std::invalid_argument("Rhombus must have 4 vertices");
        }
    }
    
    Rhombus(const Rhombus& other) : vertices(other.vertices) {}
    Rhombus(Rhombus&& other) noexcept = default;
    Rhombus& operator=(const Rhombus& other) = default;
    Rhombus& operator=(Rhombus&& other) noexcept = default;
    
    Point<T> geometricCenter() const override {
        T sumX = T(), sumY = T();
        for (const auto& vertex : vertices) {
            sumX += vertex.x();
            sumY += vertex.y();
        }
        return Point<T>(sumX / 4, sumY / 4);
    }
    
    double area() const override {
        const auto& a = vertices[0];
        const auto& b = vertices[1];
        const auto& c = vertices[2];
        const auto& d = vertices[3];
        
        double d1 = std::sqrt(std::pow(b.x() - d.x(), 2) + std::pow(b.y() - d.y(), 2));
        double d2 = std::sqrt(std::pow(a.x() - c.x(), 2) + std::pow(a.y() - c.y(), 2));
        
        return (d1 * d2) / 2.0;
    }
    
    void printVertices(std::ostream& os) const override {
        os << "Rhombus vertices: ";
        for (size_t i = 0; i < vertices.size(); ++i) {
            os << "(" << vertices[i].x() << ", " << vertices[i].y() << ")";
            if (i != vertices.size() - 1) os << ", ";
        }
    }
    
    void readFromStream(std::istream& is) override {
        vertices.clear();
        for (int i = 0; i < 4; ++i) {
            T x, y;
            if (!(is >> x >> y)) {
                throw std::runtime_error("Failed to read rhombus vertex");
            }
            vertices.emplace_back(x, y);
        }
    }
    
    bool operator==(const Figure<T>& other) const override {
        const Rhombus* rhomb = dynamic_cast<const Rhombus*>(&other);
        if (!rhomb) return false;
        return vertices == rhomb->vertices;
    }
};

#endif