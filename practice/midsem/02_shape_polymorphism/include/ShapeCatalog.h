#ifndef MIDSEM_SHAPE_CATALOG_H
#define MIDSEM_SHAPE_CATALOG_H

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "Shape.h"

class ShapeCatalog {
private:
    std::vector<std::unique_ptr<Shape>> shapes_;

public:
    void add(std::unique_ptr<Shape> shape);
    std::size_t size() const;
    double totalArea() const;
    std::vector<std::string> namesByArea() const;
};

#endif
