#pragma once

#include "Token.h"
#include "Expr.h"

#include <vector>

class Parser{
public:
    std::vector<Token> tokens;
    int current = 0;

    Parser(std::vector<Token> tokens);
};