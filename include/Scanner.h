#pragma once

#include "TokenType.h"
#include "Token.h"
#include <string>
#include <unordered_map>
#include <vector>

class Scanner{
private:
    std::unordered_map<std::string, TokenType> keywords = {
        {"and",   AND},
        {"class", CLASS},
        {"else",  ELSE},
        {"false", FALSE},
        {"for",   FOR},
        {"fun",   FUN},
        {"if",    IF},
        {"nil",   NIL},
        {"or",    OR},
        {"print", PRINT},
        {"return",RETURN},
        {"super", SUPER},
        {"this",  THIS},
        {"true",  TRUE},
        {"var",   VAR},
        {"while", WHILE}
    };
    
    std::string source;
    std::vector<Token> tokens;
    int start {0};
    int current {0};
    int line {1};

    void scanToken();
    void addToken(TokenType _type);
    void addToken(TokenType _type, std::any _literal);
    bool isAtEnd();
    bool isAlpha(char _character);
    bool isDigit(char _character);
    bool isAlphaNumeric(char _character);
    char peek();
    char peekNext();
    char advance();
    bool match(char _expected);
    void identifier();
    void number();
    void string();

public:
    Scanner(std::string _sourceData);
    std::vector<Token> scanTokens();
    
};