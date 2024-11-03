#pragma once

#include <windows.h>
#include <string>
#include <stdexcept>

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

private:
    HANDLE hMapFile_;
    std::wstring name_;
};
