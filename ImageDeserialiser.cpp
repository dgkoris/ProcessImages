#include "Constants.h"
#include "ImageDeserialiser.h"
#include <cstring>
#include <stdexcept>

ImageDeserialiser::ImageDeserialiser(const SharedMemoryReader& reader)
    : reader_(reader), currentOffset_(0) {}

int ImageDeserialiser::ReadNumberOfImages() {
    LPVOID pBuf = reader_.MapMemory(currentOffset_, sizeof(int));
    int numberOfImages;
    std::memcpy(&numberOfImages, pBuf, sizeof(int));
    reader_.UnmapMemory(pBuf);
    currentOffset_ += sizeof(int);
    return numberOfImages;
}

std::vector<ImageData> ImageDeserialiser::ReadAllImagesMetadata(int numberOfImages) {
    std::vector<ImageData> images;

    for (int i = 0; i < numberOfImages; ++i) {
        int size, width, height, nameLength;

        DWORD alignedOffset = (currentOffset_ / MAPPING_SIZE) * MAPPING_SIZE;
        DWORD delta = currentOffset_ - alignedOffset;
        LPVOID pBuf = reader_.MapMemory(alignedOffset, MAPPING_SIZE);

        unsigned char* bufPtr = static_cast<unsigned char*>(pBuf) + delta;

        // Byte size
        std::memcpy(&size, bufPtr, sizeof(int));
        bufPtr += sizeof(int);
        currentOffset_ += sizeof(int);

        // Width
        std::memcpy(&width, bufPtr, sizeof(int));
        bufPtr += sizeof(int);
        currentOffset_ += sizeof(int);

        // Height
        std::memcpy(&height, bufPtr, sizeof(int));
        bufPtr += sizeof(int);
        currentOffset_ += sizeof(int);

        // Name length
        std::memcpy(&nameLength, bufPtr, sizeof(int));
        bufPtr += sizeof(int);
        currentOffset_ += sizeof(int);

        if (nameLength <= 0 || nameLength > MAX_IMAGE_NAME_LENGTH) {
            reader_.UnmapMemory(pBuf);
            throw std::runtime_error("Invalid name length detected in shared memory.");
        }

        // Name bytes
        std::string name(nameLength, '\0');
        std::memcpy(name.data(), bufPtr, nameLength);
        currentOffset_ += nameLength;

        reader_.UnmapMemory(pBuf);
        images.emplace_back(name, size, Dimensions(width, height), std::vector<unsigned char>(size));
    }

    return images;
}

void ImageDeserialiser::ReadAllImagesData(std::vector<ImageData>& images) {
    for (auto& image : images) {
        DWORD alignedOffset = (currentOffset_ / MAPPING_SIZE) * MAPPING_SIZE;
        DWORD delta = currentOffset_ - alignedOffset;
        LPVOID pBuf = reader_.MapMemory(alignedOffset, image.size + delta);

        std::memcpy(const_cast<unsigned char*>(image.data.data()), static_cast<unsigned char*>(pBuf) + delta, image.size);

        reader_.UnmapMemory(pBuf);
        currentOffset_ += image.size;
    }
}
