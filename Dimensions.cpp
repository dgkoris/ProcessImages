#include "Dimensions.h"

std::string Dimensions::to_string() const {
    return "(" + std::to_string(width) + "x" + std::to_string(height) + ")";
}
