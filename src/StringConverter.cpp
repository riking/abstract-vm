//
// Created by Kane York on 4/16/18.
//

#include "StringConverter.hpp"

#include "StaticError.hpp"

#include <cstdio>
#include <string>
#include <vector>

template <>
std::string StringConverter::MakeString<int8_t>(int8_t value) const {
    return std::to_string(value);
}
template <>
std::string StringConverter::MakeString<int16_t>(int16_t value) const {
    return std::to_string(value);
}
template <>
std::string StringConverter::MakeString<int32_t>(int32_t value) const {
    return std::to_string(value);
}

template <>
std::string StringConverter::MakeString<float>(float value) const {
    int size = std::snprintf(NULL, 0, "%.9g", value);
    if (size < 0) {
        throw StaticError("snprintf failure");
    }
    std::vector<char> buf(size + 1);
    size = std::snprintf(buf.data(), size + 1, "%.9g", value);
    if (size < 0) {
        throw StaticError("snprintf failure");
    }
    return std::string(buf.data(), size);
}

template <>
std::string StringConverter::MakeString<double>(double value) const {
    int size = std::snprintf(NULL, 0, "%.17g", value);
    if (size < 0) {
        throw StaticError("snprintf failure");
    }
    std::vector<char> buf(size + 1);
    size = std::snprintf(buf.data(), size + 1, "%.17g", value);
    if (size < 0) {
        throw StaticError("snprintf failure");
    }
    return std::string(buf.data(), size);
}
