#include "script_runner.h"

ScriptRunner::ScriptRunner(bool debug) : debug(debug) {}

void ScriptRunner::PrintDebug(const std::string& text) {
    if (debug) {
        std::cout << text << std::endl;
    }
}

void ScriptRunner::PrintError(const std::string& text) {
    std::cerr << text << std::endl;
}

void ScriptRunner::PrintOutput(const std::string& text) {
    std::cout << text << std::endl;
}

void ScriptRunner::RunFile(const std::string& fileName) {
    File file = FileLoader::LoadFile(fileName);
    Run(fileName, file.text);
}

void ScriptRunner::RunString(const std::string& name, const std::string& text) {
    Run(name, text);
}

void ScriptRunner::Run(const std::string& fileName, const std::string& fileText) {
    Lexer lexer = Lexer(fileName, fileText);
    TokenResult tokenResult = lexer.MakeTokens();
    const std::string &tokenResultString = "Token Result String:\n" + LexerUtils::GetTokenResultString(tokenResult);

    if (tokenResult.error.type == ErrorType::NONE) {
        PrintDebug(tokenResultString);
        Parser parser = Parser(tokenResult.tokens);
        ParseResult abstractSyntaxTree = parser.Parse();
        if (abstractSyntaxTree.error.type == ErrorType::NONE) {
            PrintDebug("\nNode String:\n" + NodeUtils::GetNodeString(abstractSyntaxTree.node));
            Interpreter interpreter = Interpreter();
            Context* rootContext = new Context{ "<program>" };
            RunTimeResult runTimeResult = interpreter.Visit(abstractSyntaxTree.node, rootContext);
            if (runTimeResult.error.type != ErrorType::NONE) {
                PrintError(ErrorUtils::GetErrorString(runTimeResult.error));
            } else {
                PrintOutput(runTimeResult.value.stringValue);
            }
            delete rootContext;
        } else {
            PrintError(ErrorUtils::GetErrorString(abstractSyntaxTree.error));
        }
        parser.ClearNodeData();
    } else {
        PrintError(tokenResultString);
    }
}
