#include <cmath>
#include <memory>
#include <stdexcept>

#include <gtest/gtest.h>

#include "Circle.h"
#include "Rectangle.h"
#include "ShapeCatalog.h"

TEST(Circle, ComputesArea) {
    EXPECT_NEAR(Circle(1.0).area(), 3.141592653589793, 1e-9);
    EXPECT_NEAR(Circle(2.0).area(), 4.0 * 3.141592653589793, 1e-9);
    EXPECT_NEAR(Circle(0.5).area(), 0.25 * 3.141592653589793, 1e-9);
    EXPECT_NEAR(Circle(10.0).area(), 100.0 * 3.141592653589793, 1e-9);
}

TEST(Circle, ComputesPerimeter) {
    EXPECT_NEAR(Circle(1.0).perimeter(), 2.0 * 3.141592653589793, 1e-9);
    EXPECT_NEAR(Circle(2.0).perimeter(), 4.0 * 3.141592653589793, 1e-9);
    EXPECT_NEAR(Circle(0.5).perimeter(), 1.0 * 3.141592653589793, 1e-9);
    EXPECT_NEAR(Circle(10.0).perimeter(), 20.0 * 3.141592653589793, 1e-9);
}

TEST(Circle, RejectsNonPositiveRadius) {
    EXPECT_THROW(Circle(0.0), std::invalid_argument);
    EXPECT_THROW(Circle(-1.0), std::invalid_argument);
}

TEST(Circle, ExposesAStableName) {
    EXPECT_EQ(Circle(1.0).name(), "Circle");
}

TEST(Rectangle, ComputesArea) {
    EXPECT_DOUBLE_EQ(Rectangle(2.0, 3.0).area(), 6.0);
    EXPECT_DOUBLE_EQ(Rectangle(1.0, 1.0).area(), 1.0);
    EXPECT_DOUBLE_EQ(Rectangle(0.5, 4.0).area(), 2.0);
    EXPECT_DOUBLE_EQ(Rectangle(10.0, 2.0).area(), 20.0);
}

TEST(Rectangle, ComputesPerimeter) {
    EXPECT_DOUBLE_EQ(Rectangle(2.0, 3.0).perimeter(), 10.0);
    EXPECT_DOUBLE_EQ(Rectangle(1.0, 1.0).perimeter(), 4.0);
    EXPECT_DOUBLE_EQ(Rectangle(0.5, 4.0).perimeter(), 9.0);
    EXPECT_DOUBLE_EQ(Rectangle(10.0, 2.0).perimeter(), 24.0);
}

TEST(Rectangle, RejectsNonPositiveDimensions) {
    EXPECT_THROW(Rectangle(0.0, 2.0), std::invalid_argument);
    EXPECT_THROW(Rectangle(2.0, 0.0), std::invalid_argument);
    EXPECT_THROW(Rectangle(-1.0, 2.0), std::invalid_argument);
    EXPECT_THROW(Rectangle(2.0, -1.0), std::invalid_argument);
}

TEST(Rectangle, ExposesAStableName) {
    EXPECT_EQ(Rectangle(2.0, 3.0).name(), "Rectangle");
}

TEST(ShapeCatalog, OwnsDifferentDerivedShapes) {
    ShapeCatalog catalog;
    catalog.add(std::make_unique<Circle>(1.0));
    catalog.add(std::make_unique<Rectangle>(2.0, 3.0));

    EXPECT_EQ(catalog.size(), 2U);
}

TEST(ShapeCatalog, RejectsNullShapes) {
    ShapeCatalog catalog;

    EXPECT_THROW(catalog.add(nullptr), std::invalid_argument);
    EXPECT_EQ(catalog.size(), 0U);
}

TEST(ShapeCatalog, CalculatesTotalArea) {
    ShapeCatalog catalog;
    catalog.add(std::make_unique<Circle>(1.0));
    catalog.add(std::make_unique<Rectangle>(2.0, 3.0));

    EXPECT_NEAR(catalog.totalArea(), 3.141592653589793 + 6.0, 1e-9);
}

TEST(ShapeCatalog, SortsNamesByAreaWithATieBreak) {
    ShapeCatalog catalog;
    catalog.add(std::make_unique<Rectangle>(2.0, 2.0));
    catalog.add(std::make_unique<Circle>(1.0));

    const std::vector<std::string> names = catalog.namesByArea();

    ASSERT_EQ(names.size(), 2U);
    EXPECT_EQ(names[0], "Circle");
    EXPECT_EQ(names[1], "Rectangle");
}
