#pragma once

#include <vector>
#include "ImageData.h"

/// <summary>
/// Analyses image data to calculate the most common colour per row.
/// </summary>
class ImageAnalysis {
public:
    /// <summary>
    /// Constructs an ImageAnalysis.
    /// </summary>
    /// <param name="image">The image data to analyse.</param>
    explicit ImageAnalysis(const ImageData& image) : image_(image) {}

    /// <summary>
    /// Analyses the image and returns the most common colour per row.
    /// </summary>
    /// <returns>A vector containing the most common colour per row.</returns>
    std::vector<unsigned int> GetMostCommonColoursPerRow() const;

    /// <summary>
    /// Displays the results of the most common colour per row.
    /// </summary>
    void DisplayResults() const;

private:
    const ImageData& image_;

    /// <summary>
    /// Converts RGB values to unsigned int representation of a colour.
    /// </summary>
    /// <param name="r">Red value.</param>
    /// <param name="g">Green value.</param>
    /// <param name="b">Blue value.</param>
    /// <returns>An unsigned int representing the colour.</returns>
    static unsigned int ColourToInt(unsigned char r, unsigned char g, unsigned char b) {
        return (r << 16) | (g << 8) | b;
    }
};
