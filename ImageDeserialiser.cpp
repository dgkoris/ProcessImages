#include "ImageDeserialiser.h"
#include <stdexcept>

static constexpr int MAX_IMAGE_NAME_LENGTH = 256;

ImageDeserialiser::ImageDeserialiser(const SharedMemoryReader& reader)
    : reader_(reader), currentOffset_(0) {}

int ImageDeserialiser::ReadNumberOfImages() {
    return reader_.ReadInt(currentOffset_);
}

std::vector<ImageData> ImageDeserialiser::ReadAllImagesMetadata(int numberOfImages) {
    std::vector<ImageData> images;

    for (int i = 0; i < numberOfImages; ++i) {
        int size = reader_.ReadInt(currentOffset_);
        int width = reader_.ReadInt(currentOffset_);
        int height = reader_.ReadInt(currentOffset_);
        int nameLength = reader_.ReadInt(currentOffset_);

        if (nameLength <= 0 || nameLength > MAX_IMAGE_NAME_LENGTH) {
            throw std::runtime_error("Invalid name length detected in shared memory.");
        }

        std::string name = reader_.ReadString(nameLength, currentOffset_);
        images.emplace_back(name, size, Dimensions(width, height), std::vector<unsigned char>(size));
    }

    return images;
}

void ImageDeserialiser::ReadAllImagesData(std::vector<ImageData>& images) {
    for (auto& image : images) {
        image.data = reader_.ReadBytes(image.size, currentOffset_);
    }
}
