#include "SharedMemoryReader.h"
#include "Utilities.h"
#include <sstream>
#include <stdexcept>
#include <iostream>

SharedMemoryReader::SharedMemoryReader(const std::string& name) : name_(Utilities::ConvertToWideString(name)) {
    hMapFile_ = OpenFileMapping(FILE_MAP_READ, FALSE, name_.c_str());
    if (!hMapFile_) {
        std::ostringstream oss;
        oss << "Failed to open shared memory '" << name << "' (Error code: " << GetLastError() << ").\n"
            << "Ensure the SharedMemoryManager is running and BMP images are loaded into shared memory.";
        throw std::runtime_error(oss.str());
    }
}

SharedMemoryReader::~SharedMemoryReader() {
    if (hMapFile_ && hMapFile_ != INVALID_HANDLE_VALUE) {
        CloseHandle(hMapFile_);
    }
}

LPVOID SharedMemoryReader::MapMemory(DWORD offset, DWORD size) const {
    LPVOID pBuf = MapViewOfFile(hMapFile_, FILE_MAP_READ, 0, offset, offset + size);

    if (pBuf == nullptr) {
        std::cerr << "Failed to map memory at offset " << offset << " with size " << size << ". Error code: " << GetLastError() << "\n";
    }
    else {
        std::cout << "Mapped memory at offset: " << offset << ", size: " << size << "\n";
    }

    return pBuf;
}

void SharedMemoryReader::UnmapMemory(LPVOID pBuf) const {
    UnmapViewOfFile(pBuf);
}
