#pragma once

#include "Token.h"
#include "RuntimeError.h"
#include "Interpreter.h"

#include <string>

class GlyphCast{
private:
    static bool hadError;
    static bool hadRuntimeError;

    // Interpreter interpreter {};
    // const Interpreter
public:
    // int main(int argc, char* argv[]);
    void runFile(std::string filePath);
    void runPrompt();
    void run(std::string source);
    static void error(int line, std::string message);
    static void error(Token token, std::string message);
    static void report(int line, std::string where, std::string message);
    static void runtimeError(RuntimeError error);
};