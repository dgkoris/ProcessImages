#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "ImageData.h"
#include "Dimensions.h"

int main() {

    // Create fake image data for testing:
    std::string name = "TestImage.bmp";
    int size = 1024;
    Dimensions dimensions(100, 50);

    // Vector of random bytes between 0 and 255
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<unsigned char> data(size);
    for (auto& byte : data) {
        byte = std::rand() % 256;
    }

    ImageData image(name, size, dimensions, data);

    std::cout << "Image Data:\n" << image.to_string() << std::endl;

    std::cout << "\n";
    for (size_t i = 0; i < data.size(); ++i) {
        // Print each byte in hexadecimal format
        std::cout << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(data[i]) << " ";

        if ((i + 1) % 16 == 0) {
            std::cout << "\n";
        }
    }
    std::cout << std::dec << std::endl;

    return 0;
}
