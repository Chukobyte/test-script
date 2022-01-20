#include "value.h"

ValueNumber::ValueNumber(const Token& token, FilePosition start, FilePosition end, Context* context) : stringValue(token.value), start(std::move(start)), end(std::move(end)), context(context) {
    if (token.type == TokenType::INT) {
        value.valueInt = ConvertStringValueToNumber<int>(token.value);
        type = NumberType::INT;
    } else if (token.type == TokenType::FLOAT) {
        value.valueFloat = ConvertStringValueToNumber<float>(token.value);
        type = NumberType::FLOAT;
    }
}

ValueNumber::ValueNumber(float floatValue, Context* context) : type(NumberType::FLOAT), stringValue(std::to_string(floatValue)), context(context) {
    value.valueFloat = floatValue;
}

ValueNumber::ValueNumber(int intValue, Context* context) : type(NumberType::INT), stringValue(std::to_string(intValue)), context(context) {
    value.valueInt = intValue;
}

ValueNumber::ValueNumber(Error error, Context* context) : error(std::move(error)), context(context) {}

ValueNumber ValueNumber::AddedTo(const ValueNumber& otherNumber) {
    if (type == NumberType::FLOAT || otherNumber.type == NumberType::FLOAT) {
        const float newFloat = value.GetFloat() + otherNumber.value.GetFloat();
        return ValueNumber(newFloat, context);
    } else {
        const int newInt = value.valueInt + otherNumber.value.valueInt;
        return ValueNumber(newInt, context);
    }
}

ValueNumber ValueNumber::SubbedBy(const ValueNumber& otherNumber) {
    if (type == NumberType::FLOAT || otherNumber.type == NumberType::FLOAT) {
        const float newFloat = value.GetFloat() - otherNumber.value.GetFloat();
        return ValueNumber(newFloat, context);
    } else {
        const int newInt = value.valueInt - otherNumber.value.valueInt;
        return ValueNumber(newInt, context);
    }
}

ValueNumber ValueNumber::MultipliedBy(const ValueNumber& otherNumber) {
    if (type == NumberType::FLOAT || otherNumber.type == NumberType::FLOAT) {
        const float newFloat = value.GetFloat() * otherNumber.value.GetFloat();
        return ValueNumber(newFloat, context);
    } else {
        const int newInt = value.valueInt * otherNumber.value.valueInt;
        return ValueNumber(newInt, context);
    }
}

ValueNumber ValueNumber::DividedBy(const ValueNumber& otherNumber) {
    // TODO: Compare with epsilon!
    if (otherNumber.value.GetFloat() == 0.0f) {
        return ValueNumber(Error{
            ErrorType::RUNTIME_ERROR,
            "Division by zero",
            otherNumber.start,
            otherNumber.end,
            context
        });
    }
    if (type == NumberType::FLOAT || otherNumber.type == NumberType::FLOAT) {
        const float newFloat = value.GetFloat() / otherNumber.value.GetFloat();
        return ValueNumber(newFloat, context);
    } else {
        const int newInt = value.valueInt / otherNumber.value.valueInt;
        return ValueNumber(newInt, context);
    }
}

ValueNumber ValueNumber::PoweredBy(const ValueNumber& otherNumber) {
    if (type == NumberType::FLOAT || otherNumber.type == NumberType::FLOAT) {
        const float newFloat = pow(value.GetFloat(), otherNumber.value.GetFloat());
        return ValueNumber(newFloat, context);
    } else {
        const int newInt = pow(value.valueInt, otherNumber.value.valueInt);
        return ValueNumber(newInt, context);
    }
}
