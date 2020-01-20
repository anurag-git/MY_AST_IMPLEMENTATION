#pragma once
#include "AST.h"

class Parser {
private:
	ASTNode* expr();
	ASTNode* exprNext();
	ASTNode* term();
	ASTNode* termNext();
	ASTNode* factor();

	void getNextToken();
	void skipWhiteSpaces();
	void matchToken(char token);
	bool isArithOperator(int m_Token);
	bool isOperator(int m_Token);

	ASTNode* makeNode(ASTNode* left, ASTNodeType type, ASTNode* right);
	ASTNode* makeNumber(double value);

	const char* m_Text;
	int m_Token;
	int m_TokenVal;

public:
	ASTNode* parse(const char* input);
	Parser();
	~Parser();
};
