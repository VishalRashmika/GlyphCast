#pragma once

#include "Token.h"
#include "Expr.h"

#include <vector>
#include <any>

class Block;
class Expression;
class Print;
class Var;

class StmtVisitor{
public:
	virtual std::any visitStmtBlock(Block* expr) = 0;
	virtual std::any visitStmtExpression(Expression* expr) = 0;
	virtual std::any visitStmtPrint(Print* expr) = 0;
	virtual std::any visitStmtVar(Var* expr) = 0;
};

class Stmt{
public:
	virtual std::any Accept(StmtVisitor* visitor) = 0;
	virtual ~Stmt(){}
};

class Block: public Stmt{
public:
	std::vector<Stmt*> statements;

	Block(std::vector<Stmt*> statements){
		this->statements = statements;
	}

	std::any Accept(StmtVisitor* visitor) override{
		return visitor->visitStmtBlock(this);
	}
};

class Expression: public Stmt{
public:
	Expr* expression;

	Expression(Expr* expression){
		this->expression = expression;
	}

	std::any Accept(StmtVisitor* visitor) override{
		return visitor->visitStmtExpression(this);
	}
};

class Print: public Stmt{
public:
	Expr* expression;

	Print(Expr* expression){
		this->expression = expression;
	}

	std::any Accept(StmtVisitor* visitor) override{
		return visitor->visitStmtPrint(this);
	}
};

class Var: public Stmt{
public:
	Token name;
	Expr* initializer;

	Var(Token name, Expr* initializer){
		this->name = name;
		this->initializer = initializer;
	}

	std::any Accept(StmtVisitor* visitor) override{
		return visitor->visitStmtVar(this);
	}
};

