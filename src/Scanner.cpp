#include <iostream>
#include <vector>

#include <Token.cpp>
#include "../include/TokenType.h"

class Scanner{
private:
    std::string Source;
    //  new (array list sth)
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    

public:
    Scanner(std::string source){
        Source = source;
    }

    std::vector<Token> scanTokens(){
        while(!isAtEnd()){
            start = current;
            scanToken();
        }
        tokens.emplace_back(TokenType::EOF_TOKEN, "",NULL, line);
        return tokens;
    }


};