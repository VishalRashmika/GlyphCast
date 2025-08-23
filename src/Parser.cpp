# include "Parser.h"
#include "GlyphCast.h"

Parser::Parser(std::vector<Token> tokens){
    this->tokens = tokens;
}

Expr* Parser::parse(){
    try{
        return expression();
    }
    catch(ParseError error){
        return NULL;
    }
}

Expr* Parser::expression(){
    return equality();
}

Expr* Parser::equality(){
    Expr* expr = comparison();
    while(match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)){
        Token oper = previous();
        Expr* right = comparison();
        expr = new Binary(expr, oper, right);
    }
    return expr;
}

Expr* Parser::comparison(){
    Expr* expr = term();

    while(match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL)){
        Token oper= previous();
        Expr* right = term();
        expr = new Binary(expr, oper, right);
    }
    return expr;
}

Expr* Parser::term(){
    Expr* expr = factor();
    
    while(match(TokenType::MINUS, TokenType::PLUS)){
        Token oper = previous();
        Expr* right = factor();
        expr = new Binary(expr, oper, right);
    }
    return expr;
}

Expr* Parser::factor(){
    Expr* expr = unary();
    
    while(match(TokenType::SLASH, TokenType::STAR)){
        Token oper = previous();
        Expr* right = unary();
        expr = new Binary(expr, oper, right);
    }
    return expr;
}

Expr* Parser::unary(){
    if(match(TokenType::BANG, TokenType::MINUS)){
        Token oper = previous();
        Expr* right = unary();
        return new Unary(oper, right);
    }

    return primary();
}

Expr* Parser::primary(){
    if(match(TokenType::FALSE)){
        return new Literal(false);
    }
    if(match(TokenType::TRUE)){
        return new Literal(true);
    }
    if(match(TokenType::NIL)){
        return new Literal(NULL);
    }

    if(match(TokenType::NUMBER, TokenType::STRING)){
        return new Literal(previous().literal);
    }

    if(match(TokenType::LEFT_PAREN)){
        Expr* expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return new Grouping(expr);
    }
    throw error(peek(), "Expect expression.");
}

bool Parser::match(TokenType type){
    if(check(type)){
        advance();
        return true;
    }
    return false;
}

template<typename... T>
bool Parser::match(TokenType first, T... rest){
    // fold expression: check(first) OR check(any of rest...)
    if((check(first) || ... || check(rest))){
        advance();
        return true;
    }
    return false;
}

Token Parser::consume(TokenType type, std::string message){
    if(check(type)){
        return advance();
    }

    throw error(peek(), message);
}

bool Parser::check(TokenType type){
    if(isAtEnd()){
        return false;
    }
    return peek().type == type;
}

Token Parser::advance(){
    if(!isAtEnd()){
        current++;
    }
    return previous();
}

bool Parser::isAtEnd(){
    return peek().type == END_OF_FILE;
}

Token Parser::peek(){
    return tokens[current];
}

Token Parser::previous(){
    return tokens[current - 1];
}

Parser::ParseError Parser::error(Token token, std::string message){
    GlyphCast::error(token, message);
    return ParseError(message);
}