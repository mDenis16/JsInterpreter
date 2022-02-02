/*
 *****************************************************************
 *                 Simple C++ Lexer Toolkit Library              *
 *                                                               *
 * Lexer Examples                                                *
 * Author: Arash Partow (2001)                                   *
 * URL: http://www.partow.net/programming/lexertk/index.html     *
 *                                                               *
 * Copyright notice:                                             *
 * Free use of the Simple C++ Lexer Toolkit Library is permitted *
 * under the guidelines and in accordance with the MIT License.  *
 * http://www.opensource.org/licenses/MIT                        *
 *                                                               *
 *****************************************************************
*/


#include <iostream>
#include <string>
#include <vector>

#include "lexertk.h"
#include "Parser.hpp"
#include "Function.hpp"
#include "Variable.h"




void example06()
{
    
    JsParser parser;
   
   
     std::string f =
        "function CalculateAngle( yaw ) { var ionel = -15; var ionica = 5; var samp = ionel + (ionica); }";


    Function Function;

    int function_count = 0;

   
    parser.ProcessFunction(f, Function);

    for (auto& var : Function.Stack) {
        std::cout << "Stack variable " << var.first << std::endl;
    }
    
   
    auto last = Function.FuncVariables.back();

    (reinterpret_cast<Variable*>(last))->RuntimeExpression();

   
    std::cin >> function_count;
}

int main()
{
    /*example01();
    example02();
    example03();
    example04();
    example05();*/
    example06();

    return 0;
}