#include <stdio.h>
#include "Parser.h"
#include "Evaluate.h"
#include <iostream>
#include <math.h>

using namespace std;

void Test(const char* text)
{
   Parser parser;

   try
   {
      ASTNode* ast = parser.parse(text);

      try
      {
         Evaluate eval;
         double val = eval.calculate(ast);

         std::cout << "\"" << text << " = " << floor(val) << "\" \t " << "PASSED" << std::endl;
      }
      catch(std::exception& ex)
      {
        std::cout << "\"" << text << "\"\t" << "Evaluation Exception Caught: " << "\"" << ex.what() << "\"" << std::endl;
      }

      delete ast;
   }
   catch(std::exception& ex)
   {
      std::cout <<  "\"" << text << "\"\t" << "Parser Exception Caught: " << "\"" << ex.what() << "\"" << std::endl;
   }
}

int main(int argc, char* argv[])
{
   cout << "===================================" << endl;
   cout << "Valid Scenarios" << endl;
   cout << "===================================" << endl;
   Test("1+2*3");
   Test("1+2+3+4");
   Test("1*2*3*4");
   Test("1/2/3/4");
   Test("1*2+3*4");
   Test("1+2*3+4");
   Test("(1+2)*(3+4)");
   Test("1+(2*3)*(4+5)");
   Test("1+(2*3)/4+5");
   Test("125");
   Test("125+2*33");
   Test("(4 + 5 * (7 - 3)) - 2");
   Test("4+5+7/2");
   Test("10 + 4");
   Test("1+3");
   Test("1 + 2");
   Test("(3)");

   cout << "===================================" << endl;
   cout << "Invalid Scenarios" << endl;
   cout << "===================================" << endl;
   Test("1 + 2.5");
   Test("-1+(-2)");
   Test("-1+(-2.0)");
   Test("   1*2,5");
   Test("   1*2.5e2");
   Test("M1 + 2.5");
   Test("1 + 2&5");
   Test("1 * 2.5.6");
   Test("1 ** 2.5");
   Test("*1 / 2.5");
   Test("/1 / 2.5");
   Test("-4+5+7/2");
   Test("1+");
   Test("1-");
   Test("1/");
   Test("1*");
   Test("1 + +");
   Test("(1");
   Test("(+3)");
   Test("+1");
   Test("-1");
   Test("*1");
   Test("/1");
   Test("-10");
   Test("5.5");
   return 0;
}
