#include "ShapeCatalog.h"

#include <stdexcept>
#include <utility>

void ShapeCatalog::add(std::unique_ptr<Shape> shape) {
    if (shape == nullptr) {
        throw std::invalid_argument("shape cannot be null");
    }
    shapes_.push_back(std::move(shape));
}

std::size_t ShapeCatalog::size() const {
    return shapes_.size();
}

double ShapeCatalog::totalArea() const {
    // TODO: sum area() through the Shape interface.
    return 0.0;
}

std::vector<std::string> ShapeCatalog::namesByArea() const {
    // TODO: copy the shapes' names and sort by the corresponding areas.
    return {};
}
