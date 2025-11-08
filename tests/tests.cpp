#include <gtest/gtest.h>
#include "array.h"
#include "figure.h"
#include "rhombus.h"
#include "pentagon.h"
#include "hexagon.h"
#include "point.h"
#include <memory>
#include <sstream>

// Test Point class
TEST(PointTest, BasicOperations) {
    Point<int> p1(1, 2);
    Point<int> p2(1, 2);
    Point<int> p3(3, 4);
    
    EXPECT_EQ(p1, p2);
    EXPECT_NE(p1, p3);
    EXPECT_EQ(p1.x(), 1);
    EXPECT_EQ(p1.y(), 2);
}

TEST(PointTest, ArithmeticOperations) {
    Point<double> p1(2.0, 4.0);
    Point<double> p2(1.0, 1.0);
    
    Point<double> sum = p1 + p2;
    EXPECT_DOUBLE_EQ(sum.x(), 3.0);
    EXPECT_DOUBLE_EQ(sum.y(), 5.0);
    
    Point<double> div = p1 / 2.0;
    EXPECT_DOUBLE_EQ(div.x(), 1.0);
    EXPECT_DOUBLE_EQ(div.y(), 2.0);
}

// Test Rhombus class
TEST(RhombusTest, AreaCalculation) {
    Rhombus<double> rhombus({
        Point<double>(0, 1),
        Point<double>(1, 0),
        Point<double>(0, -1),
        Point<double>(-1, 0)
    });
    
    EXPECT_NEAR(rhombus.area(), 2.0, 0.001);
}

TEST(RhombusTest, GeometricCenter) {
    Rhombus<double> rhombus({
        Point<double>(0, 2),
        Point<double>(2, 0),
        Point<double>(0, -2),
        Point<double>(-2, 0)
    });
    
    Point<double> center = rhombus.geometricCenter();
    EXPECT_DOUBLE_EQ(center.x(), 0.0);
    EXPECT_DOUBLE_EQ(center.y(), 0.0);
}

TEST(RhombusTest, StreamOperations) {
    Rhombus<double> rhombus;
    std::stringstream ss("0 1 1 0 0 -1 -1 0");
    
    EXPECT_NO_THROW(ss >> rhombus);
    
    Point<double> center = rhombus.geometricCenter();
    EXPECT_DOUBLE_EQ(center.x(), 0.0);
    EXPECT_DOUBLE_EQ(center.y(), 0.0);
}

// Test Pentagon class
TEST(PentagonTest, AreaCalculation) {
    Pentagon<double> pentagon({
        Point<double>(0, 1),
        Point<double>(0.951, 0.309),
        Point<double>(0.588, -0.809),
        Point<double>(-0.588, -0.809),
        Point<double>(-0.951, 0.309)
    });
    
    EXPECT_NEAR(pentagon.area(), 2.377, 0.01);
}

TEST(PentagonTest, GeometricCenter) {
    Pentagon<double> pentagon({
        Point<double>(0, 2),
        Point<double>(1.902, 0.618),
        Point<double>(1.176, -1.618),
        Point<double>(-1.176, -1.618),
        Point<double>(-1.902, 0.618)
    });
    
    Point<double> center = pentagon.geometricCenter();
    EXPECT_NEAR(center.x(), 0.0, 0.001);
    EXPECT_NEAR(center.y(), 0.0, 0.001);
}

// Test Hexagon class
TEST(HexagonTest, AreaCalculation) {
    Hexagon<double> hexagon({
        Point<double>(1, 0),
        Point<double>(0.5, 0.866),
        Point<double>(-0.5, 0.866),
        Point<double>(-1, 0),
        Point<double>(-0.5, -0.866),
        Point<double>(0.5, -0.866)
    });
    
    EXPECT_NEAR(hexagon.area(), 2.598, 0.01);
}

// Test Array class
TEST(ArrayTest, BasicOperations) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    EXPECT_EQ(figures.size(), 0);
    
    auto rhombus = std::make_shared<Rhombus<double>>(std::vector<Point<double>>{
        Point<double>(0, 1), Point<double>(1, 0), 
        Point<double>(0, -1), Point<double>(-1, 0)
    });
    
    figures.push_back(rhombus);
    EXPECT_EQ(figures.size(), 1);
    
    auto pentagon = std::make_shared<Pentagon<double>>(std::vector<Point<double>>{
        Point<double>(0, 1), Point<double>(0.951, 0.309), 
        Point<double>(0.588, -0.809), Point<double>(-0.588, -0.809),
        Point<double>(-0.951, 0.309)
    });
    
    figures.push_back(pentagon);
    EXPECT_EQ(figures.size(), 2);
    
    EXPECT_NEAR(figures.totalArea(), 2.0 + 2.377, 0.1);
}

TEST(ArrayTest, EraseOperation) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    auto rhombus = std::make_shared<Rhombus<double>>(std::vector<Point<double>>{
        Point<double>(0, 1), Point<double>(1, 0), 
        Point<double>(0, -1), Point<double>(-1, 0)
    });
    
    figures.push_back(rhombus);
    EXPECT_EQ(figures.size(), 1);
    
    figures.erase(0);
    EXPECT_EQ(figures.size(), 0);
}

TEST(ArrayTest, CopyAndMove) {
    Array<std::shared_ptr<Figure<double>>> figures1;
    
    auto rhombus = std::make_shared<Rhombus<double>>(std::vector<Point<double>>{
        Point<double>(0, 1), Point<double>(1, 0), 
        Point<double>(0, -1), Point<double>(-1, 0)
    });
    
    figures1.push_back(rhombus);
    
    // Test copy constructor
    Array<std::shared_ptr<Figure<double>>> figures2(figures1);
    EXPECT_EQ(figures2.size(), 1);
    
    // Test move constructor
    Array<std::shared_ptr<Figure<double>>> figures3(std::move(figures1));
    EXPECT_EQ(figures3.size(), 1);
    EXPECT_EQ(figures1.size(), 0);
}

// Test operator double() conversion
TEST(FigureTest, DoubleConversion) {
    Rhombus<double> rhombus({
        Point<double>(0, 1),
        Point<double>(1, 0),
        Point<double>(0, -1),
        Point<double>(-1, 0)
    });
    
    double area = static_cast<double>(rhombus);
    EXPECT_NEAR(area, 2.0, 0.001);
}

// Test comparison operators
TEST(FigureTest, Comparison) {
    Rhombus<double> rhombus1({
        Point<double>(0, 1),
        Point<double>(1, 0),
        Point<double>(0, -1),
        Point<double>(-1, 0)
    });
    
    Rhombus<double> rhombus2({
        Point<double>(0, 1),
        Point<double>(1, 0),
        Point<double>(0, -1),
        Point<double>(-1, 0)
    });
    
    Rhombus<double> rhombus3({
        Point<double>(0, 2),
        Point<double>(2, 0),
        Point<double>(0, -2),
        Point<double>(-2, 0)
    });
    
    EXPECT_TRUE(rhombus1 == rhombus2);
    EXPECT_FALSE(rhombus1 == rhombus3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}