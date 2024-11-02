#pragma once

#include <string>

/// <summary>
/// Represents image dimensions.
/// </summary>
struct Dimensions {
    const int width;
    const int height;

    /// <summary>
    /// Initialises a Dimensions instance.
    /// </summary>
    /// <param name="w">Image width.</param>
    /// <param name="h">Image height.</param>
    constexpr Dimensions(int w = 0, int h = 0) : width(w), height(h) {}

    /// <summary>
    /// Returns a string representation of the dimensions.
    /// </summary>
    /// <returns>A string representation.</returns>
    [[nodiscard]] std::string to_string() const;
};
