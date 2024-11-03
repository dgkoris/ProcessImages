#include "Utilities.h"
#include <windows.h>

std::wstring Utilities::ConvertToWideString(const std::string& str) {

    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size_needed);

    return wstr;
}
