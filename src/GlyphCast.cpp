#include <iostream>
#include <fstream>

#include "sysexits.h"

// function prototypes
void runFile(std::string filePath);
void runPrompt();
void run(std::string source);

int main(int argc, char* argv[]){
    if (argc > 2){
        std::cerr << "Usage: glyph [script]" << std::endl;
        exit(EX_USAGE);
    }
    else if (argc == 2){
        runFile(argv[1]);
    }
    else{
        runPrompt();
    }

    return 0;
}   

void runFile(std::string filePath){
    std::ifstream inputFile(filePath);
    std::string fileData;

    while(getline(inputFile,fileData)){std::cout << fileData << std::endl;}
    std::cout << "File Loaded Successfully" << std::endl;
    run(fileData);
    // todo:if had error exit
}

void runPrompt(){
    std::string command;
    while(std::getline(std::cin, command)){
        run(command);
        // todo:haderror = false;
    }
}

void run(std::string source){

}