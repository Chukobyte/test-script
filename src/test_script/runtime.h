#pragma once

#include "value.h"
#include "error.h"

class RunTimeResult {
  public:
    ValueNumber value = {};
    Error error = {};

    RunTimeResult Register(const RunTimeResult& runTimeResult) {
        return RunTimeResult { runTimeResult.value, runTimeResult.error };
    }

    RunTimeResult Register(const ValueNumber& valueNumber) {
        return RunTimeResult { valueNumber, valueNumber.error };
    }

    RunTimeResult Success(const ValueNumber& valueNumber) {
        return RunTimeResult{ valueNumber, valueNumber.error };
    }

    RunTimeResult Failure(const Error& error) {
        return RunTimeResult{ {}, error };
    }
};
