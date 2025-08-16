#pragma once

#include "Token.h"

#include <any>

class Binary;
class Grouping;
class Literal;
class Unary;

class Visitor{
public:
	virtual std::any visitExprBinary(Binary* expr) = 0;
	virtual std::any visitExprGrouping(Grouping* expr) = 0;
	virtual std::any visitExprLiteral(Literal* expr) = 0;
	virtual std::any visitExprUnary(Unary* expr) = 0;
};

class Expr{
public:
	virtual std::any Accept(Visitor* visitor) = 0;
	virtual ~Expr(){}
};

class Binary: public Expr{
public:
	Expr* left;
	Token op;
	Expr* right;

	Binary(Expr* left, Token op, Expr* right){
		this->left = left;
		this->op = op;
		this->right = right;
	}

	std::any Accept(Visitor* visitor) override{
		return visitor->visitExprBinary(this);
	}
};

class Grouping: public Expr{
public:
	Expr* expression;

	Grouping(Expr* expression){
		this->expression = expression;
	}

	std::any Accept(Visitor* visitor) override{
		return visitor->visitExprGrouping(this);
	}
};

class Literal: public Expr{
public:
	std::any value;

	Literal(std::any value){
		this->value = value;
	}

	std::any Accept(Visitor* visitor) override{
		return visitor->visitExprLiteral(this);
	}
};

class Unary: public Expr{
public:
	Token op;
	Expr* right;

	Unary(Token op, Expr* right){
		this->op = op;
		this->right = right;
	}

	std::any Accept(Visitor* visitor) override{
		return visitor->visitExprUnary(this);
	}
};

