
#include "GlyphCast.h"
#include "sysexits.h"
#include "Scanner.h"
#include <iostream>
#include <fstream>

bool GlyphCast::hadError = false;

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

    for (int i = 0; i < tokens.size(); i++){
        std::cout << tokens[i].toString() << std::endl;
    }
}

void GlyphCast::error(int line, std::string message){
    report(line, "", message);
}

void GlyphCast::report(int line, std::string where, std::string message){
    std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
    hadError = true;
}