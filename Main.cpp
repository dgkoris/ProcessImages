#include <iostream>
#include <vector>
#include <iomanip>
#include "SharedMemoryReader.h"

const std::string SHARED_MEMORY_NAME = "Local\\SharedMemoryImages";
constexpr size_t CAPTURED_MEMORY_SIZE = 10 * 1024; // The size of the memory to capture from the shared memory segment.

/// <summary>
/// Entry point of the application.
/// </summary>
/// <returns>Returns 0 on success or 1 on failure.</returns>
int main() {
    try {
        SharedMemoryReader sharedMemory(SHARED_MEMORY_NAME);

        LPVOID pBuf = sharedMemory.MapMemory(0, CAPTURED_MEMORY_SIZE);

        if (!pBuf) {
            std::cerr << "Failed to map shared memory.\n";
            return 1;
        }

        unsigned char* rawDataPtr = static_cast<unsigned char*>(pBuf);
        std::vector<unsigned char> rawData(rawDataPtr, rawDataPtr + CAPTURED_MEMORY_SIZE);

        std::cout << "Test reading shared memory data:\n";
        for (size_t i = 0; i < rawData.size(); ++i) {
            std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
                << static_cast<int>(rawData[i]) << " ";
            if ((i + 1) % 16 == 0) std::cout << "\n";
        }
        std::cout << std::dec << "\n";

        sharedMemory.UnmapMemory(pBuf);

        std::cout << "Press Enter to exit...\n";
        std::cin.get();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
