#pragma once

#include <string>

#include "file.h"

struct Context {
    std::string displayName;
    Context* parentContext = nullptr;
    FilePosition parentEntryPosition = {};
};
