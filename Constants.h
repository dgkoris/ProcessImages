#pragma once

#include <windows.h>
#include <string>

// Shared memory constants
const std::string SHARED_MEMORY_NAME = "Local\\SharedMemoryImages";
const int MAX_IMAGE_NAME_LENGTH = 256;
constexpr DWORD MAPPING_SIZE = 65536; // Size of the shared memory mapping region.
