#ifndef PENTAGON_H
#define PENTAGON_H

#include "figure.h"
#include <vector>
#include <cmath>

template<Scalar T>
class Pentagon : public Figure<T> {
private:
    std::vector<Point<T>> vertices;
    
public:
    Pentagon() = default;
    
    Pentagon(const std::vector<Point<T>>& verts) : vertices(verts) {
        if (verts.size() != 5) {
            throw std::invalid_argument("Pentagon must have 5 vertices");
        }
    }
    
    Pentagon(const Pentagon& other) : vertices(other.vertices) {}
    Pentagon(Pentagon&& other) noexcept = default;
    Pentagon& operator=(const Pentagon& other) = default;
    Pentagon& operator=(Pentagon&& other) noexcept = default;
    
    Point<T> geometricCenter() const override {
        T sumX = T(), sumY = T();
        for (const auto& vertex : vertices) {
            sumX += vertex.x();
            sumY += vertex.y();
        }
        return Point<T>(sumX / 5, sumY / 5);
    }
    
    double area() const override {
        double area = 0;
        for (int i = 0; i < 5; ++i) {
            int j = (i + 1) % 5;
            area += vertices[i].x() * vertices[j].y() - vertices[j].x() * vertices[i].y();
        }
        return std::abs(area) / 2.0;
    }
    
    void printVertices(std::ostream& os) const override {
        os << "Pentagon vertices: ";
        for (size_t i = 0; i < vertices.size(); ++i) {
            os << "(" << vertices[i].x() << ", " << vertices[i].y() << ")";
            if (i != vertices.size() - 1) os << ", ";
        }
    }
    
    void readFromStream(std::istream& is) override {
        vertices.clear();
        for (int i = 0; i < 5; ++i) {
            T x, y;
            if (!(is >> x >> y)) {
                throw std::runtime_error("Failed to read pentagon vertex");
            }
            vertices.emplace_back(x, y);
        }
    }
    
    bool operator==(const Figure<T>& other) const override {
        const Pentagon* pent = dynamic_cast<const Pentagon*>(&other);
        if (!pent) return false;
        return vertices == pent->vertices;
    }
};

#endif