#include "Interpreter.h"
#include "RuntimeError.h"

void Interpreter::interpret(Expr* expr){
    try{
        std::any value = evaluate(expr);
        std::cout << stringify(value) << std::endl;
    }
    catch(RuntimeError error){
        GlyphCast::runtimeError(error);
    }
    
}

std::any Interpreter::evaluate(Expr* expr) {
    return expr->Accept(this);
}

std::any Interpreter::visitExprGrouping(Grouping* expr) {
    return evaluate(expr->expression);
}

std::any Interpreter::visitExprLiteral(Literal* expr) {
    return expr->value;
}

std::any Interpreter::visitExprUnary(Unary* expr) {
    std::any right = evaluate(expr->right);

    switch (expr->op.type)
    {
    case BANG:
        return !isTruthy(right);
    case MINUS:
        checkNumberOperand(expr->op, right);
        return - std::any_cast<float>(right);
    }

    return {};
}

std::any Interpreter::visitExprBinary(Binary* expr) {
    std::any left = evaluate(expr->left);
    std::any right = evaluate(expr->right);

    switch (expr->op.type){
    case GREATER:
        checkNumberOperands(expr->op, left, right);
        return (std::any_cast<float> (left) > std::any_cast<float> (right));
    case GREATER_EQUAL:
        checkNumberOperands(expr->op, left, right);
        return (std::any_cast<float> (left) >= std::any_cast<float> (right));
    case LESS:
        checkNumberOperands(expr->op, left, right);
        return (std::any_cast<float> (left) < std::any_cast<float> (right));
    case LESS_EQUAL:
        checkNumberOperands(expr->op, left, right);
        return (std::any_cast<float> (left) <= std::any_cast<float> (right));
    case MINUS:
        checkNumberOperands(expr->op, left, right);
        return (std::any_cast<float> (left) - std::any_cast<float> (right));
    case SLASH:
        checkNumberOperands(expr->op, left, right);
        return (std::any_cast<float> (left) / std::any_cast<float> (right));
    case STAR:
        checkNumberOperands(expr->op, left, right);
        return (std::any_cast<float> (left) * std::any_cast<float> (right));
    case PLUS:
        if (left.type() == typeid(float) && right.type() == typeid(float)){
            return (std::any_cast<float> (left) + std::any_cast<float> (right));
        }
        if (left.type() == typeid(std::string) && right.type() == typeid(std::string)){
            return (std::any_cast<std::string> (left) + std::any_cast<std::string> (right));
        }
        throw RuntimeError(expr->op, "Operands must be two numbers or two strings.");
    case EQUAL_EQUAL: 
        return isEqual(left, right);
    case BANG_EQUAL: 
        return !isEqual(left, right);

    }

    return {};
}  

void Interpreter::checkNumberOperand(Token oper, std::any operand){
    if (operand.type() == typeid(float)) return;
    throw RuntimeError(oper, "Operand must be a number.");
}

void Interpreter::checkNumberOperands(Token oper, std::any left, std::any right){
    if (left.type() == typeid(float) && right.type() == typeid(float)) return;
    throw RuntimeError(oper, "Operands must be a numbers.");
}

bool Interpreter::isTruthy(std::any object){
    if (object.type() == typeid(nullptr)) return false;
    if (object.type() == typeid(bool)) {
        return std::any_cast<bool>(object);
    }
    return true;
}

bool Interpreter::isEqual(std::any a, std::any b){
    if (a.type() == typeid(nullptr) && b.type() == typeid(nullptr)) {
        return true;
    }
    if (a.type() == typeid(nullptr)) return false;

    if (a.type() == typeid(std::string) && b.type() == typeid(std::string)) {
        return std::any_cast<std::string>(a) == std::any_cast<std::string>(b);
    }
    if (a.type() == typeid(float) && b.type() == typeid(float)) {
        return std::any_cast<float>(a) == std::any_cast<float>(b);
    }
    if (a.type() == typeid(bool) && b.type() == typeid(bool)) {
        return std::any_cast<bool>(a) == std::any_cast<bool>(b);
    }

    return false;
}

std::string Interpreter::stringify(std::any object){
    if (object.type() == typeid(nullptr)) return "nil";

    if (object.type() == typeid(float)) {
        std::string text = std::to_string(std::any_cast<float>(object));
        if (text[text.length() - 2] == '.' && text[text.length() - 1] == '0') {
            text = text.substr(0, text.length() - 2);
        }
        return text;
    }

    if (object.type() == typeid(std::string)) {
        return std::any_cast<std::string>(object);
    }
    if (object.type() == typeid(bool)) {
        return std::any_cast<bool>(object) ? "true" : "false";
    }

    return "Error in stringify: object type not recognized.";
}