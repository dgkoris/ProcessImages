#include <iostream>
#include <iomanip>
#include <numeric>
#include "SharedMemoryReader.h"
#include "ImageDeserialiser.h"
#include "ImageData.h"
#include "ImageAnalysis.h"

static constexpr char SHARED_MEMORY_NAME[] = "Local\\SharedMemoryImages";

/// <summary>
/// Entry point of the application.
/// </summary>
/// <returns>Returns 0 on success or 1 on failure.</returns>
int main() {
    try {
        SharedMemoryReader sharedMemory(SHARED_MEMORY_NAME);
        ImageDeserialiser deserialiser(sharedMemory);

        int numberOfImages = deserialiser.ReadNumberOfImages();
        std::vector<ImageData> images = deserialiser.ReadAllImagesMetadata(numberOfImages);
        deserialiser.ReadAllImagesData(images);

        int totalSize = 0;
        for (const auto& image : images) {
            std::cout << "Loaded image: " << std::left << std::setw(25) << image.name
                << std::setw(10) << image.size << "bytes  ("
                << image.imageDimensions.width << "x" << image.imageDimensions.height << ")\n";
            totalSize += image.size;
        }

        std::cout << "\nTotal images: " << std::left << std::setw(24) << numberOfImages
            << std::setw(10) << totalSize << " bytes\n";
        std::cout << "\nData read from shared memory: '" << SHARED_MEMORY_NAME << "'.\n\n";

        for (const auto& image : images) {
            ImageAnalysis imageAnalysis(image);
            imageAnalysis.DisplayResults();
        }

        std::cout << "Press Enter to exit...\n";
        std::cin.get();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
