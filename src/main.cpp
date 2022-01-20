#include "test_script/script_runner.h"

int main(int argv, char** args) {
    ScriptRunner runner(false);
    // Script runner can either run a file or a string
    runner.RunFile(R"(scripts\test.ss)");
//    runner.RunString("main", "10 + 5");
    return 0;
}
