#pragma once

#include <vector>
#include <any>
#include <string>

class Interpreter;

class GlyphCallable {
public:
    virtual ~GlyphCallable() = default;
    
    virtual std::any call(Interpreter& interpreter, std::vector<std::any> arguments) = 0;
    virtual int arity() const = 0;
    virtual std::string toString() const = 0;
};