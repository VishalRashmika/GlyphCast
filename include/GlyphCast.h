#pragma once

#include <iostream>

class GlyphCast{
private:
    static bool hadError;
public:
    // int main(int argc, char* argv[]);
    void runFile(std::string filePath);
    void runPrompt();
    void run(std::string source);
    static void error(int line, std::string message);
    static void report(int line, std::string where, std::string message);
};