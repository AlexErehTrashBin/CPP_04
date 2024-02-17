#pragma once

#include "stdafx.h"

inline auto getWideCStringFromInput() -> wchar_t* {
    // Write function that reads a wide character string from the standard input
    auto var = wstring();
    std::getline(wcin, var);
    const auto stringSize = var.size() + 1;
    auto* result = new wchar_t[stringSize];
    wcsncpy(result, var.data(), stringSize);
    result[stringSize] = '\0';
    return result;
}

inline auto getIntFromInput() -> int {
    auto var = wstring();
    std::getline(wcin, var);
    const auto stringSize = var.size() + 1;
    auto* result = new wchar_t[stringSize];
    wcsncpy(result, var.data(), stringSize);
    return _wtoi(result);
}

inline auto getFloatFromInput() -> float {
    auto var = wstring();
    wcin >> var;
    return stof(var);
}
