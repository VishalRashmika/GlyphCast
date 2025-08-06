#include <iostream>
#include <fstream>
#include <vector>

//forward decleration
void ASTdefinition(std::string outputPath, std::string baseFileName, std::vector<std::string> expressionTypes);
    

int main(int argc, char* argv[]){
    // todo: input validation : should have atleast one parameter
}


void ASTdefinition(std::string outputPath, std::string baseFileName, std::vector<std::string> expressionTypes){
    std::string outputFilePath = outputPath + "/" + baseFileName + ".h";
    std::ofstream fileWriter(outputPath);
}