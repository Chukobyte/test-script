#pragma once

#include <utility>
#include <sstream>
#include <cmath>

#include "file.h"
#include "token.h"

enum class NumberType {
    NOT_A_NUMBER,
    INT,
    FLOAT
};

struct ValueContainer {
    int valueInt = 0;
    float valueFloat = 0.0f;

    float GetFloat() const {
        return valueInt + valueFloat;
    }
};

struct ValueNumber {
    NumberType type = NumberType::NOT_A_NUMBER;
    std::string stringValue;
    ValueContainer value = {};
    FilePosition start = {};
    FilePosition end = {};
    Error error = {};
    Context* context = nullptr;

    ValueNumber() = default;
    explicit ValueNumber(const Token& token, FilePosition start = {}, FilePosition end = {}, Context* context = nullptr);
    explicit ValueNumber(float floatValue, Context* context = nullptr);
    explicit ValueNumber(int intValue, Context* context = nullptr);
    explicit ValueNumber(Error error, Context* context = nullptr);

    ValueNumber AddedTo(const ValueNumber& otherNumber);
    ValueNumber SubbedBy(const ValueNumber& otherNumber);
    ValueNumber MultipliedBy(const ValueNumber& otherNumber);
    ValueNumber DividedBy(const ValueNumber& otherNumber);
    ValueNumber PoweredBy(const ValueNumber& otherNumber);

    template<typename T>
    T ConvertStringValueToNumber(const std::string& value) {
        std::stringstream numberStream(value);
        T numberValue;
        numberStream >> numberValue;
        return numberValue;
    }
};
