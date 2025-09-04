#pragma once

#include "Expr.h"
#include "GlyphCast.h"

#include <any>
#include <string>
#include <iostream>

class Interpreter : public Visitor
{
private:
    void checkNumberOperand(Token oper, std::any operand);
    void checkNumberOperands(Token oper, std::any left,std::any right);
    bool isTruthy(std::any object);
    bool isEqual(std::any a, std::any b);
    std::string stringify(std::any object);
    std::any evaluate(Expr* expr);

public:
    void interpret(Expr* expr);//
    std::any visitExprLiteral(Literal* expr) override;
    std::any visitExprUnary(Unary* expr) override;
    std::any visitExprGrouping(Grouping* expr) override;
    std::any visitExprBinary(Binary* expr) override;
};
