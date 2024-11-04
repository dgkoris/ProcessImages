#pragma once

#include <windows.h>
#include <string>
#include <vector>

/// <summary>
/// Provides functionality to write to a shared memory segment.
/// </summary>
class SharedMemoryWriter {
public:
    /// <summary>
    /// Constructs a SharedMemoryWriter.
    /// </summary>
    /// <param name="name">The name of the shared memory segment to open or create.</param>
    /// <param name="createIfNotExist">Create the shared memory if it doesn't exist.</param>
    /// <param name="size">Size of the shared memory segment.</param>
    /// <exception cref="std::runtime_error">Thrown if the shared memory can't be opened or created.</exception>
    explicit SharedMemoryWriter(const std::string& name, bool createIfNotExist, size_t size);

    /// <summary>
    /// Destroys the SharedMemoryWriter and closes the shared memory handle.
    /// </summary>
    ~SharedMemoryWriter();

    /// <summary>
    /// Writes an integer to the shared memory at the specified offset and updates the offset.
    /// </summary>
    /// <param name="value">The integer value to write.</param>
    /// <param name="offset">Reference to the current offset in the shared memory. Updated after writing.</param>
    void WriteInt(int value, int& offset);

    /// <summary>
    /// Writes a vector of unsigned integers to the shared memory.
    /// </summary>
    /// <param name="data">The vector of unsigned integers to write.</param>
    /// <param name="offset">Reference to the current offset in the shared memory. Updated after writing.</param>
    void WriteBytes(const std::vector<unsigned int>& data, int& offset);

private:
    /// <summary>
    /// Maps a segment of shared memory and returns a pointer to the mapped data.
    /// </summary>
    /// <param name="offset">The offset from the start of the shared memory segment.</param>
    /// <param name="size">The size of the memory segment to map.</param>
    /// <returns>A pointer to the mapped memory or nullptr if the mapping fails.</returns>
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
