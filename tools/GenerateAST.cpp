#include "Utility.h"

#include <iostream>
#include <fstream>
#include <vector>

const std::string baseFileName = "Expr";

//forward decleration
void ASTDefinition(std::string outputPath, std::string baseFileName, std::vector<std::string> expressionTypes);
void visitorDefinition(std::ofstream& fileWriter, std::vector<std::string>& expressionTypes);

int main(int argc, char* argv[]){
    // todo: input validation : should have atleast one parameter
    std::string outputPath = argv[1];
    std::vector<std::string> exprTypes;
    exprTypes = {
        "Binary   : Expr* left, Token op, Expr* right",
        "Grouping : Expr* expression",
        "Literal  : std::any value",
        "Unary    : Token op, Expr* right"
    };

    ASTDefinition(outputPath, baseFileName, exprTypes);
    std::cout << "end of program" << std::endl;
}


void ASTDefinition(std::string outputPath, std::string baseFileName, std::vector<std::string> expressionTypes){
    std::string outputFilePath = outputPath + "/" + baseFileName + ".h";
    std::ofstream fileWriter(outputFilePath);

    fileWriter << "#pragma once\n" << std::endl;
    fileWriter << "#include \"Token.h\"\n" << std::endl;
    fileWriter << "#include <iostream>\n#include <vector>\n#include <memory>\n#include <any>\n" << std::endl;

    for (int i = 0; i < expressionTypes.size(); i++){
        std::string exprClassName = trim(split(expressionTypes[i], ": ")[0]);

        fileWriter << "class " << exprClassName << ";" << std::endl;
    }
    fileWriter << std::endl;

    // visitor code



    fileWriter.close();
}


void visitorDefinition(std::ofstream& fileWriter, std::vector<std::string>& expressionTypes){
    fileWriter << "class " << baseFileName << "Visitor{" << std::endl;

    for (int i = 0; i < expressionTypes.size(); i++){
        std::string visitExprName = trim(split(expressionTypes[i], ": ")[0]);
        
        fileWriter << "\tvirtual std::any visit" << visitExprName << baseFileName << "(std::shared_ptr<" << visitExprName << "> " << toLower(baseFileName) << ") = 0;\n";
    }
}