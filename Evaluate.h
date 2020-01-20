#pragma once
#include "AST.h"

class Evaluate {
public:
	double calculate(ASTNode* ast);
	Evaluate();
	~Evaluate();
};
