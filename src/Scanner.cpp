#include <iostream>
#include <vector>

#include <Token.cpp>
#include "../include/TokenType.h"
#include "Glyphcast.cpp"
class Scanner{
private:
    std::string Source;
    //  new (array list sth)
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;

public:
    Scanner(std::string source){
        Source = source;
    }

    bool isAtEnd(){
        return current >= static_cast<int>(Source.size());
    }

    std::vector<Token> scanTokens(){
        while(!isAtEnd()){
            start = current;
            scanToken();
        }
        tokens.emplace_back(TokenType::EOF_TOKEN, "",NULL, line);
        return tokens;
    }

    void scanToken(){
        auto c = advance();
        switch (c) {
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;
        case '!': addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
        case '=': addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
        case '<': addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
        case '>': addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
        case ' ':
        case '\r':
        case '\t':
        case '\n': line++; break;

        case '/':
            if (match('/')) {
                // tning to do
                while(peek() != '\n' && );
            } else {
                addToken(TokenType::SLASH);
            }
        break;

        case '"': string(); break;

        default : error(line, "Unexpected character."); break;
        }
    }

    void Scanner::string()
    {
        while (peek() != '"' && !isAtEnd()) {
            if (peek() == '\n') {
                ++line;
            }
            advance();
        }

        // Unterminated string
        if (isAtEnd()) {
            error(line, "Unterminated string.");
        }

        advance(); // the closing '"'

        // Trim the surrounding quotes
        addToken(TokenType::STRING, Source.substr(start + 1, current - start - 2));
    }


    bool match (char expected){
        if (isAtEnd()){
            return false;
        }
        if (Source.at(current) != expected){
            return false;
        }
        current ++;
        return true;
    }

    char peek() {
        if (isAtEnd()) {
            return '\0';
        }
        return Source.at(current);
    }

    char advance(){
        ++current;
        return Source.at(current - 1);
    }

    void addToken(TokenType type, std::any literal)
    {
        tokens.emplace_back(type, Source.substr(start, current - start), literal, line);
    }

    void addToken(TokenType type)
    {
        tokens.emplace_back(type, Source.substr(start, current - start), line);
    }
};