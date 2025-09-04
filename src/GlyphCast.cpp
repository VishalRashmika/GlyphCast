
#include "GlyphCast.h"
#include "sysexits.h"
#include "Scanner.h"
#include "Parser.h"
#include "Expr.h"
#include "AstPrinter.h"

#include <iostream>
#include <fstream>

bool GlyphCast::hadError = false;
bool GlyphCast::hadRuntimeError = false;

int main(int argc, char* argv[]){
    GlyphCast glyph;
    if (argc > 2){
        std::cerr << "Usage: glyph [script]" << std::endl;
        exit(EX_USAGE);
    }
    else if (argc == 2){
        glyph.runFile(argv[1]);
    }
    else{
        glyph.runPrompt();
    }

    return 0;
}   

void GlyphCast::runFile(std::string filePath){
    std::ifstream inputFile(filePath);
    std::string fileData;

    while(getline(inputFile,fileData)){}
    std::cout << "File Loaded Successfully" << std::endl;
    run(fileData);
    
    if(hadError){
        exit(EX_DATAERR);
    }
    if (hadRuntimeError){
        exit(EX_SOFTWARE);
    }
}

void GlyphCast::runPrompt(){
    while (true) {
        std::cout << "> ";
        std::string command;
        if (!std::getline(std::cin, command)) break;

        run(command);
        hadError = false;
    }
}

void GlyphCast::run(std::string source){
    Scanner scammer {source};
    std::vector<Token> tokens = scammer.scanTokens();
    Parser parser {tokens};
    Expr* expression = parser.parse();

    if(hadError) return;

    Interpreter interpreter {};
    // std::cout << AstPrinter().print(expression) << std::endl;
    interpreter.interpret(expression);
}

void GlyphCast::error(int line, std::string message){
    report(line, "", message);
}

void GlyphCast::report(int line, std::string where, std::string message){
    std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
    hadError = true;
}

void GlyphCast::error(Token token, std::string message){
    if(token.type == TokenType::END_OF_FILE){
        report(token.line, " at end", message);
    }
    else{
        report(token.line, " at '" + token.lexeme + "'", message);
    }
}

void GlyphCast::runtimeError(RuntimeError error){
    std::cerr << error.what() << "\n[line " << error.token.line << "]\n" << std::endl;
    hadRuntimeError = true;
}