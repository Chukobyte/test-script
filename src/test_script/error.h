#pragma once

#include "file.h"
#include "context.h"

enum class ErrorType {
    NONE,
    ERROR,
    ILLEGAL_CHARACTER,
    INVALID_SYNTAX,
    RUNTIME_ERROR
};

struct Error {
    ErrorType type = ErrorType::NONE;
    std::string details;
    FilePosition start = {};
    FilePosition end = {};
    Context* context = nullptr;
};

namespace ErrorUtils {
std::string GetErrorString(const Error& error);
};
