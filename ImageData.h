#pragma once

#include <string>
#include <vector>
#include "Dimensions.h"

/// <summary>
/// Represents image data.
/// </summary>
class ImageData {
public:
    const std::string name;
    const int size;
    const Dimensions imageDimensions;
    std::vector<unsigned char> data;

    /// <summary>
    /// Initialises an ImageData instance.
    /// </summary>
    /// <param name="name">Image name.</param>
    /// <param name="size">Image size in bytes.</param>
    /// <param name="imageDimensions">Image dimensions.</param>
    /// <param name="data">Image data as a byte array.</param>
    ImageData(const std::string& name, int size, const Dimensions& imageDimensions, const std::vector<unsigned char>& data);

    /// <summary>
    /// Returns a string representation of the image data.
    /// </summary>
    /// <returns>A string representation.</returns>
    [[nodiscard]] std::string to_string() const;
};
