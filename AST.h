#pragma once

enum ASTNodeType
{
   PLUS,
   MINUS,
   MUL,
   DIV,
   NUM
};

struct ASTNode
{
  public:
    ASTNodeType Type;
    ASTNode*    Left;
    ASTNode*    Right;
};

struct ASTNodeNumber
{
  public:
     ASTNodeType Type;
     double      Value;
};
