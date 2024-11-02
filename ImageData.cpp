#include "ImageData.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

/// <summary>
/// Initialises an ImageData instance.
/// </summary>
/// <param name="name">Image name.</param>
/// <param name="size">Image size in bytes.</param>
/// <param name="imageDimensions">Image dimensions.</param>
/// <param name="data">Image data as a byte array.</param>
/// <exception cref="std::invalid_argument">Thrown when <paramref name="data"/> is empty or <paramref name="name"/> is empty.</exception>
ImageData::ImageData(const std::string& name, int size, const Dimensions& imageDimensions, const std::vector<unsigned char>& data)
    : name(name), size(size), imageDimensions(imageDimensions), data(data) {
    if (data.empty()) throw std::invalid_argument("'data' cannot be empty");
    if (name.empty()) throw std::invalid_argument("'name' cannot be empty");
}

/// <summary>
/// Returns a string representation of the image data, including name, size, and dimensions.
/// </summary>
/// <returns>A formatted string representation.</returns>
std::string ImageData::to_string() const {
    std::ostringstream oss;
    oss << std::left << std::setw(25) << name << "\t" << std::setw(8) << size << " bytes\t" << imageDimensions.to_string();
    return oss.str();
}
