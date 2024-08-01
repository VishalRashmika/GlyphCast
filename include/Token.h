#include <iostream>
#include <any>

#include "TokenType.h"

class Token{
private:
    TokenType type;
    std::string lexeme;
    std::any literal;
    int line;

public:
    Token(TokenType type, std::string lexeme, std::any literal, int line);
    std::string toString();
    
};