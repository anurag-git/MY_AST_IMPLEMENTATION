#include <iostream>
#include <exception>
#include <sstream>
#include <stdlib.h>
#include "Parser.h"

using namespace std;

Parser::Parser()
{
		m_Text = NULL;
		m_Token = 0;
		m_TokenVal = 0;
}

Parser::~Parser() {}

bool Parser::isArithOperator(int m_Token)
{
	switch (m_Token)
	{
		case '+':
		case '-':
		case '*':
		case '/':
			return true;
	}

	return false;
}

bool Parser::isOperator(int m_Token)
{
		if(isArithOperator(m_Token) ||
			m_Token == '(' || m_Token == ')')
			return true;

		return false;
}

ASTNode* Parser::expr()
{
	stringstream sstr;
	ASTNode* node;

	node = term();

	switch (m_Token)
	{
		case '+':
			matchToken('+');
			node = makeNode(node, PLUS, expr());
			break;
		case '-':
			matchToken('-');
			node = makeNode(node, MINUS, expr());
			break;
	}

	return node;
}

ASTNode* Parser::term()
{
	ASTNode* node;

	node = factor();

	switch (m_Token)
	{
		case '*':
			matchToken('*');
			node = makeNode(node, MUL, term());
			break;
		case '/':
			matchToken('/');
			node = makeNode(node, DIV, term());
			break;
	}

	return node;
}

ASTNode* Parser::factor()
{
	ASTNode* node;
	stringstream sstr;
	char symbol = m_Token;

	switch (m_Token)
	{
		case '(':
			matchToken('(');
			node = expr();
			matchToken(')');
			return node;
		case '-':
		case '+':
		case '*':
		case '/':
			sstr << "Unexpected token: '" << symbol << "' ";
			throw runtime_error(sstr.str());
			break;
		default:
			getNextToken();
			return makeNumber(m_TokenVal);
	}
}

void Parser::skipWhiteSpaces()
{
	 while(isspace(*m_Text)) m_Text++;
}

void Parser::getNextToken()
{
	skipWhiteSpaces();
	bool isValidToken = false;
  char symbol = *m_Text;
	m_Token = *m_Text++;
	int nextToken = *m_Text;

	//Ignoring the NULL character
	if(m_Token == '\0')
		return;

	if (isdigit(m_Token))
	{
			m_TokenVal = m_Token - '0'; // converting from ascii number to number
			isValidToken = true;

			// this is for multidigit literals
			while (isdigit(*m_Text))
			{
				m_TokenVal = m_TokenVal*10 + *m_Text - '0';
				m_Text++;
			}

			return;
	}

	if(isOperator(m_Token))
		isValidToken = true;

	// For scenarios like "1+", "1-", "1*", "1/"
	if(isArithOperator(m_Token) && nextToken == '\0')
		isValidToken = false;

	if(!isValidToken)
	{
		stringstream sstr;
		sstr << "Unexpected token: '" << symbol << "' ";
		throw runtime_error(sstr.str());
	}
}

void Parser::matchToken(char token)
{
		stringstream sstr;
		if (m_Token != token)
		{
				sstr << "Expected Token: '" << token << "' ";
				throw runtime_error(sstr.str());
    }

    getNextToken();
}

ASTNode* Parser::makeNode(ASTNode* left, ASTNodeType type, ASTNode* right)
{
	 ASTNode* node = new ASTNode;
	 node->Type = type;
	 node->Left = left;
	 node->Right = right;

	 return node;
}

ASTNode* Parser::makeNumber(double value)
{
	 ASTNodeNumber* node = new ASTNodeNumber;
	 node->Type = NUM;
	 node->Value = value;

	 return (ASTNode*) node;
}

ASTNode* Parser::parse(const char* input)
{
		m_Text = input;
		getNextToken();
		return expr();
}
