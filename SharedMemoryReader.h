#pragma once

#include <windows.h>
#include <string>
#include <vector>

/// <summary>
/// Provides functionality to read data from a shared memory segment.
/// </summary>
class SharedMemoryReader {
public:
    /// <summary>
    /// Constructs a SharedMemoryReader.
    /// </summary>
    /// <param name="name">The name of the shared memory segment to open.</param>
    /// <exception cref="std::runtime_error">Thrown if the shared memory cannot be opened.</exception>
    explicit SharedMemoryReader(const std::string& name);

    /// <summary>
    /// Destroys the SharedMemoryReader and closes the shared memory handle.
    /// </summary>
    ~SharedMemoryReader();

    /// <summary>
    /// Reads an integer from the shared memory at the specified offset and updates the offset.
    /// </summary>
    /// <param name="offset">Reference to the current offset in the shared memory. Updated after reading.</param>
    /// <returns>The integer read from the shared memory.</returns>
    int ReadInt(int& offset) const;

    /// <summary>
    /// Reads a string of specified length from the shared memory at the given offset and updates the offset.
    /// </summary>
    /// <param name="length">The number of characters to read.</param>
    /// <param name="offset">Reference to the current offset in the shared memory. Updated after reading.</param>
    /// <returns>The string read from the shared memory.</returns>
    std::string ReadString(int length, int& offset) const;

    /// <summary>
    /// Reads a sequence of bytes of specified length from the shared memory at the given offset and updates the offset.
    /// </summary>
    /// <param name="length">The number of bytes to read.</param>
    /// <param name="offset">Reference to the current offset in the shared memory. Updated after reading.</param>
    /// <returns>A vector of unsigned characters containing the bytes read from shared memory.</returns>
    std::vector<unsigned char> ReadBytes(int length, int& offset) const;

private:
    /// <summary>
    /// Maps a segment of shared memory and returns a pointer to the mapped data.
    /// </summary>
    /// <param name="offset">The offset from the start of the shared memory segment.</param>
    /// <param name="size">The size of the memory segment to map.</param>
    /// <returns>A pointer to the mapped memory, or nullptr if the mapping fails.</returns>
    LPVOID MapMemory(DWORD offset, DWORD size) const;

    /// <summary>
    /// Unmaps a previously mapped memory segment.
    /// </summary>
    /// <param name="pBuf">The pointer to the memory segment to unmap.</param>
    void UnmapMemory(LPVOID pBuf) const;

    HANDLE hMapFile_;
    std::wstring name_;

    static constexpr DWORD MAPPING_SIZE = 65536;
};
