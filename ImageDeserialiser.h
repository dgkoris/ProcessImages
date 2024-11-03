#pragma once

#include "SharedMemoryReader.h"
#include "ImageData.h"
#include <vector>

/// <summary>
/// Deserialises image data.
/// </summary>
class ImageDeserialiser {
public:
    /// <summary>
    /// Constructs an ImageDeserialiser.
    /// </summary>
    /// <param name="reader">A reference to the shared memory reader.</param>
    explicit ImageDeserialiser(const SharedMemoryReader& reader);

    /// <summary>
    /// Reads and returns the number of images.
    /// </summary>
    /// <returns>The number of images.</returns>
    int ReadNumberOfImages();

    /// <summary>
    /// Reads and returns metadata for each image.
    /// </summary>
    /// <param name="numberOfImages">The number of images to read metadata for.</param>
    /// <returns>A vector of ImageData.</returns>
    std::vector<ImageData> ReadAllImagesMetadata(int numberOfImages);

    /// <summary>
    /// Reads and populates the raw data for each image.
    /// </summary>
    /// <param name="images">A reference to a vector of ImageData. Populates with raw image data.</param>
    void ReadAllImagesData(std::vector<ImageData>& images);

private:
    const SharedMemoryReader& reader_;
    int currentOffset_ = 0;
};
