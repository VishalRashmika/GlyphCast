# include "Parser.h"
# include "GlyphCast.h"

#include <memory>

Parser::Parser(std::vector<Token> tokens){
    this->tokens = tokens;
}

std::vector<Stmt*> Parser::parse(){
    std::vector<Stmt*> statements;

    while(!isAtEnd()){
        Stmt* stmt = declaration();
        if(stmt != nullptr) {
            statements.push_back(stmt);
        }
    }
    return statements;
}


Expr* Parser::expression(){
    return assignment();
}

Stmt* Parser::declaration(){
    try{
        if(match(TokenType::VAR)) return varDeclaration();
        return statement();
    }
    catch(ParseError error){
        synchronize();
        return nullptr;
    }
}


Stmt* Parser::statement(){
    if(match(TokenType::PRINT)) return printStatement();
    if(match(TokenType::LEFT_BRACE)) return new Block(block());

    return expressionStatement();
}

Stmt* Parser::printStatement(){
    Expr *expr = expression();
    consume(TokenType::SEMICOLON, "Expect ';' after value.");
    return new Print(expr);
}

Stmt* Parser::varDeclaration(){
    Token name = consume(TokenType::IDENTIFIER, "Expect variable name.");
    Expr* initializer = NULL;
    if(match(TokenType::EQUAL)){
        initializer = expression();
    }

    consume(TokenType::SEMICOLON, "Expect ';' after variable declaration.");
    return new Var(name, initializer);
}

Stmt* Parser::expressionStatement(){
    Expr *expr = expression();
    consume(TokenType::SEMICOLON, "Expect ';' after expression.");
    return new Expression(expr);
}

std::vector<Stmt*> Parser::block(){
    std::vector<Stmt*> statements;

    while(!check(TokenType::RIGHT_BRACE) && !isAtEnd()){
        statements.push_back(declaration());
    }

    consume(TokenType::RIGHT_BRACE, "Expect '}' after block.");
    return statements;
}

Expr* Parser::assignment(){
    Expr* expr = equality();

    if(match(TokenType::EQUAL)){
        Token equals = previous();
        Expr* value = assignment();

        if(Variable* e = dynamic_cast<Variable*>(expr)){
            Token name = e->name;
            return new Assign(name, value);
        }
        error(equals, "Invalid assignment target.");
    }
    return expr;
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

    if(match(TokenType::IDENTIFIER)){
        return new Variable(previous());
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
    bool result = peek().type == END_OF_FILE;
    return result;
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

void Parser::synchronize(){
    advance();
    
    while(!isAtEnd()){
        if(previous().type == TokenType::SEMICOLON) return;
        
        switch(peek().type){
            case TokenType::CLASS:
            case TokenType::FUN:
            case TokenType::VAR:
            case TokenType::FOR:
            case TokenType::IF:
            case TokenType::WHILE:
            case TokenType::PRINT:
            case TokenType::RETURN:
                return;
        }
        advance();
    }
}