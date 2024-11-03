#include "ImageData.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

ImageData::ImageData(const std::string& name, int size, const Dimensions& imageDimensions, const std::vector<unsigned char>& data)
    : name(name), size(size), imageDimensions(imageDimensions), data(data) {
    if (data.empty()) throw std::invalid_argument("'data' cannot be empty");
    if (name.empty()) throw std::invalid_argument("'name' cannot be empty");
}

std::string ImageData::to_string() const {
    std::ostringstream oss;
    oss << std::left << std::setw(25) << name << "\t" << std::setw(8) << size << " bytes\t" << imageDimensions.to_string();
    return oss.str();
}
