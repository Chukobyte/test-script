#pragma once

#include "lexer.h"
#include "parser.h"
#include "file_loader.h"
#include "interpreter.h"
#include "value.h"
#include "runtime.h"

class ScriptRunner {
  public:
    ScriptRunner(bool debug = false);
    void RunFile(const std::string& fileName);
    void RunString(const std::string& name, const std::string& text);

  private:
    bool debug;

    void Run(const std::string& fileName, const std::string& fileText);
    void PrintOutput(const std::string& text);
    void PrintError(const std::string& text);
    void PrintDebug(const std::string& text);
};
