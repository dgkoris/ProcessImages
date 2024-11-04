#include "ImageAnalysis.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <unordered_map>

constexpr unsigned int MAX_VALID_COLOUR = 0xFFFFFF;
constexpr unsigned int INVALID_COLOUR = MAX_VALID_COLOUR + 1;

std::vector<unsigned int> ImageAnalysis::GetMostCommonColoursPerRow() const {
    std::vector<unsigned int> mostCommonColours;
    mostCommonColours.reserve(image_.imageDimensions.height);

    int width = image_.imageDimensions.width;
    int height = image_.imageDimensions.height;

    int pixelDataOffset = 54;                   // BMP pixel data starts after 54 bytes
    int rowSize = ((width * 3 + 3) / 4) * 4;    // Each row is padded to a multiple of 4 bytes

    std::unordered_map<unsigned int, int> colourCount;

    for (int y = height - 1; y >= 0; --y) {
        colourCount.clear();

        const unsigned char* rowPtr = image_.data.data() + pixelDataOffset + y * rowSize;

        for (int x = 0; x < width; ++x) {
            unsigned int colour = ColourToInt(rowPtr[2], rowPtr[1], rowPtr[0]);
            ++colourCount[colour];
            rowPtr += 3;
        }

        int maxCount = 0;
        unsigned int mostCommonColour = INVALID_COLOUR; // Use INVALID_COLOUR for multiple equal frequencies

        for (const auto& [colour, count] : colourCount) {
            if (count > maxCount) {
                maxCount = count;
                mostCommonColour = colour;
            }
            else if (count == maxCount) {
                mostCommonColour = INVALID_COLOUR;
            }
        }

        mostCommonColours.push_back(mostCommonColour);
    }
    return mostCommonColours;
}

void ImageAnalysis::DisplayResults() const {
    std::cout << "\nMost common colour per row for image: " << image_.name << "\n";
    std::vector<unsigned int> mostCommonColours = GetMostCommonColoursPerRow();

    for (size_t row = 0; row < mostCommonColours.size(); ++row) {
        if (mostCommonColours[row] != INVALID_COLOUR) {
            unsigned int colour = mostCommonColours[row];
            unsigned char r = (colour >> 16) & 0xFF;
            unsigned char g = (colour >> 8) & 0xFF;
            unsigned char b = colour & 0xFF;

            printf("\033[38;2;%d;%d;%dm[\033[0m Row %-4zu R: %3d G: %3d B: %3d \033[38;2;%d;%d;%dm]\033[0m\n",
                r, g, b, row, r, g, b, r, g, b);
        }
        else {
            std::cout << "[ Row " << row << "    Multiple colours have the same frequency ]\n";
        }
    }
}
