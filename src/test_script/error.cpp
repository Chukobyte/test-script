#include "error.h"

namespace {
std::string GetErrorTypeString(const ErrorType& type) {
    switch (type) {
    case ErrorType::ILLEGAL_CHARACTER: {
        return "Illegal Character";
    }
    case ErrorType::INVALID_SYNTAX: {
        return "Invalid Syntax";
    }
    case ErrorType::RUNTIME_ERROR: {
        return "Runtime Error";
    }
    case ErrorType::ERROR: {
        return "Error";
    }
    default: {
        return "None";
    }
    }
}

std::string GenerateTraceback(const Error& error) {
    Context* context = error.context;
    FilePosition start = error.start;
    std::string resultString;
    while (context != nullptr) {
        resultString += "\nFile: " + error.start.fileName + ", line: " + std::to_string(start.line + 1) + ", in: " + context->displayName + "\n" + resultString;
        start = context->parentEntryPosition;
        context = context->parentContext;
    }
    return "Traceback (most recent call last):\n" + resultString;
}

std::string GetErrorDetailsString(const std::string& errorTypeName, const Error& error) {
    switch (error.type) {
    case ErrorType::ILLEGAL_CHARACTER:
    case ErrorType::INVALID_SYNTAX:
    case ErrorType::ERROR: {
        const std::string& positionLine = "\nFile: " + error.start.fileName + ", line: " + std::to_string(error.start.line + 1) + ", pos: " + std::to_string(error.start.index);
        return error.details + positionLine;
    }
    case ErrorType::RUNTIME_ERROR: {
        return GenerateTraceback(error) + error.details;
    }
    default: {
        return "N/A";
    }
    }
}
}

namespace ErrorUtils {
std::string GetErrorString(const Error& error) {
    const std::string& errorTypeName = GetErrorTypeString(error.type);
    return "ERROR: " + errorTypeName + "\n" +
           "DETAILS: " + GetErrorDetailsString(errorTypeName, error);
}
}
