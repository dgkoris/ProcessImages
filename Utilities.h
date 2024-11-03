#pragma once

#include <string>

/// <summary>
/// Utility functions.
/// </summary>
class Utilities {
public:
    /// <summary>
    /// Converts a UTF-8 encoded std::string to a UTF-16 encoded std::wstring.
    /// </summary>
    /// <param name="str">The UTF-8 encoded string.</param>
    /// <returns>A UTF-16 encoded wstring.</returns>
    static std::wstring ConvertToWideString(const std::string& str);
};
