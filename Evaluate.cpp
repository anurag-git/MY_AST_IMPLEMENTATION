#include "Evaluate.h"
#include "AST.h"

#include <iostream>
using namespace std;

//Empty construtor and destructor
Evaluate::Evaluate() {}
Evaluate::~Evaluate() {}

double Evaluate::calculate(ASTNode* ast)
{
	 if(ast == NULL)
			throw runtime_error("Incorrect syntax tree!");

	 if(ast->Type == NUM)
	 {
	 		ASTNodeNumber* astNum = (ASTNodeNumber*) ast;
			return astNum->Value;
	 }
	 else
	 {
			 double v1 = calculate(ast->Left);
			 double v2 = calculate(ast->Right);
			 switch(ast->Type)
			 {
				 case PLUS:  return v1 + v2;
				 case MINUS: return v1 - v2;
				 case MUL:   return v1 * v2;
				 case DIV:   return v1 / v2;
				 default:
				 	break;
			 }
		}

	 return 0;
}
