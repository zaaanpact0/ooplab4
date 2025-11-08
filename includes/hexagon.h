#ifndef HEXAGON_H
#define HEXAGON_H

#include "figure.h"
#include <vector>
#include <cmath>

template<Scalar T>
class Hexagon : public Figure<T> {
private:
    std::vector<Point<T>> vertices;
    
public:
    Hexagon() = default;
    
    Hexagon(const std::vector<Point<T>>& verts) : vertices(verts) {
        if (verts.size() != 6) {
            throw std::invalid_argument("Hexagon must have 6 vertices");
        }
    }
    
    Hexagon(const Hexagon& other) : vertices(other.vertices) {}
    Hexagon(Hexagon&& other) noexcept = default;
    Hexagon& operator=(const Hexagon& other) = default;
    Hexagon& operator=(Hexagon&& other) noexcept = default;
    
    Point<T> geometricCenter() const override {
        T sumX = T(), sumY = T();
        for (const auto& vertex : vertices) {
            sumX += vertex.x();
            sumY += vertex.y();
        }
        return Point<T>(sumX / 6, sumY / 6);
    }
    
    double area() const override {
        double area = 0;
        for (int i = 0; i < 6; ++i) {
            int j = (i + 1) % 6;
            area += vertices[i].x() * vertices[j].y() - vertices[j].x() * vertices[i].y();
        }
        return std::abs(area) / 2.0;
    }
    
    void printVertices(std::ostream& os) const override {
        os << "Hexagon vertices: ";
        for (size_t i = 0; i < vertices.size(); ++i) {
            os << "(" << vertices[i].x() << ", " << vertices[i].y() << ")";
            if (i != vertices.size() - 1) os << ", ";
        }
    }
    
    void readFromStream(std::istream& is) override {
        vertices.clear();
        for (int i = 0; i < 6; ++i) {
            T x, y;
            if (!(is >> x >> y)) {
                throw std::runtime_error("Failed to read hexagon vertex");
            }
            vertices.emplace_back(x, y);
        }
    }
    
    bool operator==(const Figure<T>& other) const override {
        const Hexagon* hex = dynamic_cast<const Hexagon*>(&other);
        if (!hex) return false;
        return vertices == hex->vertices;
    }
};

#endif