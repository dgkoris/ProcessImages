#include "SharedMemoryWriter.h"
#include <sstream>
#include <stdexcept>
#include <iostream>

SharedMemoryWriter::SharedMemoryWriter(const std::string& name, bool createIfNotExist, size_t size)
    : name_(std::wstring(name.begin(), name.end())) {

    hMapFile_ = createIfNotExist
        ? CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, static_cast<DWORD>(size), name_.c_str())
        : OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, name_.c_str());

    if (!hMapFile_) {
        DWORD error = GetLastError();
        std::ostringstream oss;
        oss << "Failed to " << (createIfNotExist ? "create" : "open")
            << " shared memory: " << name << ". Error code: " << error;
        throw std::runtime_error(oss.str());
    }
}

SharedMemoryWriter::~SharedMemoryWriter() {
    if (hMapFile_) CloseHandle(hMapFile_);
}

void SharedMemoryWriter::WriteInt(int value, int& offset) {
    LPVOID pBuf = MapMemory(static_cast<DWORD>(offset), sizeof(int));
    std::memcpy(pBuf, &value, sizeof(int));
    UnmapMemory(pBuf);
    offset += sizeof(int);
}

void SharedMemoryWriter::WriteBytes(const std::vector<unsigned int>& data, int& offset) {
    LPVOID pBuf = MapMemory(static_cast<DWORD>(offset), static_cast<DWORD>(data.size() * sizeof(unsigned int)));
    std::memcpy(pBuf, data.data(), data.size() * sizeof(unsigned int));
    UnmapMemory(pBuf);
    offset += static_cast<int>(data.size() * sizeof(unsigned int));
}

LPVOID SharedMemoryWriter::MapMemory(DWORD offset, DWORD size) const {
    DWORD alignedOffset = (offset / MAPPING_SIZE) * MAPPING_SIZE;
    DWORD delta = offset - alignedOffset;
    LPVOID pBuf = MapViewOfFile(hMapFile_, FILE_MAP_ALL_ACCESS, 0, alignedOffset, delta + size);

    if (!pBuf) {
        std::ostringstream oss;
        oss << "Failed to map shared memory at offset " << offset << " with size " << size
            << ". Aligned offset: " << alignedOffset << ", Total size requested: " << (delta + size)
            << ". Error code: " << GetLastError();
        throw std::runtime_error(oss.str());
    }

    return static_cast<unsigned char*>(pBuf) + delta;
}

void SharedMemoryWriter::UnmapMemory(LPVOID pBuf) const {
    UnmapViewOfFile(pBuf);
}
