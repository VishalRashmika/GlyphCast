#pragma once

#include "GlyphCallable.h"
#include "Enviroment.h"
#include "Stmt.h"

#include <vector>
#include <any>
#include <string>

class GlyphFunction : public GlyphCallable {
private:
    Function* declaration;
    Enviroment* closure;
    
public:
    GlyphFunction(Function* declaration, Enviroment* closure);
    
    std::any call(Interpreter& interpreter, std::vector<std::any> arguments) override;
    int arity() const override;
    std::string toString() const override;
};