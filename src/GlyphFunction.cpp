#include "GlyphFunction.h"
#include "ReturnException.h"
#include "Interpreter.h"

GlyphFunction::GlyphFunction(Function* declaration, Enviroment* closure) {
    this->declaration = declaration;
    this->closure = closure;
}

std::any GlyphFunction::call(Interpreter& interpreter, std::vector<std::any> arguments) {
    Enviroment* enviroment = new Enviroment(closure);

    for(size_t i = 0; i < declaration->params.size(); i++) {
        enviroment->define(declaration->params[i].lexeme, arguments[i]);
    }

    try {
        interpreter.executeBlock(declaration->body, enviroment);
    } catch(const ReturnException& returnValue) {
        return returnValue.value;
    } catch(...) {
        // Re-throw any other exceptions
        throw;
    }

    // If no return statement was executed, return nil
    return std::any();
}

int GlyphFunction::arity() const {
    return declaration->params.size();
}

std::string GlyphFunction::toString() const {
    return "<fn " + declaration->name.lexeme + ">";
}