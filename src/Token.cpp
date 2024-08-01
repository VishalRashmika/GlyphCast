#include <iostream>
#include <any>

#include "../include/TokenType.h"

class Token{
private:
    TokenType Type;
    std::string Lexeme;
    std::any Literal;
    int Line;

public:
    Token(TokenType type, std::string lexeme, std::any literal, int line){
        Type = type;
        Lexeme = lexeme;
        Literal = literal;
        Line = line;
    }

    
    std::string toString()
    {
        return std::to_string(static_cast<int>(Type)) + ", lexeme: '" + Lexeme + "' , literal: '" + Literal() + "'";
    }
};