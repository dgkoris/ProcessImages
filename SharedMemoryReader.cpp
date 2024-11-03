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

int SharedMemoryReader::ReadInt(int& offset) const {
    LPVOID pBuf = MapMemory(offset, sizeof(int));
    int value;
    std::memcpy(&value, pBuf, sizeof(int));
    UnmapMemory(pBuf);
    offset += sizeof(int);
    return value;
}

std::string SharedMemoryReader::ReadString(int length, int& offset) const {
    LPVOID pBuf = MapMemory(offset, length);
    std::string value(static_cast<char*>(pBuf), length);
    UnmapMemory(pBuf);
    offset += length;
    return value;
}

std::vector<unsigned char> SharedMemoryReader::ReadBytes(int length, int& offset) const {
    LPVOID pBuf = MapMemory(offset, length);
    std::vector<unsigned char> value(static_cast<unsigned char*>(pBuf), static_cast<unsigned char*>(pBuf) + length);
    UnmapMemory(pBuf);
    offset += length;
    return value;
}

LPVOID SharedMemoryReader::MapMemory(DWORD offset, DWORD size) const {
    DWORD alignedOffset = (offset / MAPPING_SIZE) * MAPPING_SIZE;
    DWORD delta = offset - alignedOffset;
    LPVOID pBuf = MapViewOfFile(hMapFile_, FILE_MAP_READ, 0, alignedOffset, delta + size);

    if (pBuf == nullptr) {
        std::ostringstream oss;
        oss << "Failed to map memory at offset " << offset << " with size " << size << ". Error code: " << GetLastError();
        throw std::runtime_error(oss.str());
    }

    return static_cast<unsigned char*>(pBuf) + delta;
}

void SharedMemoryReader::UnmapMemory(LPVOID pBuf) const {
    UnmapViewOfFile(pBuf);
}
