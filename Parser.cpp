#include <vector>
#include "lexertk.h"
#include "Parser.hpp"
#include "Function.hpp"
#include "Variable.h"
#include "Expression.hpp"
#include <iostream>


bool JsParser::ProcessFunction(std::string& func_def, Function& fd)
{
    if (!init(func_def))
        return false;

    if (!token_is(token_t::e_symbol, "function"))
        return false;

    if (!token_is_then_assign(token_t::e_symbol, fd.Name))
        return false;



    if (!token_is(token_t::e_lbracket))
        return false;

    if (!token_is(token_t::e_rbracket))
    {
        std::vector<std::string> var_list;

        for (; ; )
        {
        // (x,y,z,....w)
        if (!token_is_then_assign(token_t::e_symbol, var_list))
            return false;

        if (token_is(token_t::e_rbracket))
            break;

        if (!token_is(token_t::e_comma))
            return false;
        }

        //var_list.swap(fd.var_list);
    }

    std::size_t body_begin = current_token().position;
    std::size_t body_end = current_token().position;

    int bracket_stack = 0;

    if (!token_is(token_t::e_lcrlbracket, e_hold))
        return false;

    for (; ; )
    {
        body_end = current_token().position;

        /*if (token_is(token_t::e_symbol, "var"))
          std::cout << " current_token() " << current_token().to_str(current_token().type);*/


        if (token_is(token_t::e_symbol, "var")) {
            ProcessVariable(fd);
        }

        if (token_is(token_t::e_lcrlbracket)) {
            bracket_stack++;

        }
        else if (token_is(token_t::e_rcrlbracket))
        {
            if (0 == --bracket_stack)
                break;
        }
        else
        {
            if (lexer().finished())
                return false;



            next_token();
        }
    }

    std::size_t size = body_end - body_begin + 1;

    /* fd.body = func_def.substr(body_begin, size);


     const std::size_t index = body_begin + size;

     if (index < func_def.size())
         func_def = func_def.substr(index, func_def.size() - index);
     else
         func_def = "";*/

    return true;
}

bool JsParser::ProcessVariable(Function& func)
{


    Variable* var = new Variable();

    var->expression = new Expression();

    func.FuncVariables.push_back(var);

    std::string val;



    if (!token_is_then_assign(token_t::e_symbol, var->Name))
        return false;

    std::cout << "Processing variable name < " << var->Name << " > for function " << func.Name << std::endl;


    if (!token_is(token_t::e_eq))
        return false;


    token_t previous = {};

    for (;; ) {



        if (!(current_token().type == token_t::e_number || current_token().type == token_t::e_add || current_token().type == token_t::e_sub || current_token().type == token_t::e_symbol))
            break;


        /*
        
        var samp = 5;

        var ion = samp + 3;

        
        */
        if ((previous.type == token_t::e_add || previous.type == token_t::e_sub)) {
            if (previous.type == current_token().type) {
                std::cout << "Uncaught SyntaxError: Invalid left-hand side expression in postfix operation" << std::endl;
                return false;
            }
        }

        
        if (current_token().type == token_t::e_number) {
            StackVariable* variable = new StackVariable();
     
            variable->data = std::malloc(sizeof(int));

            std::string stack_Var = current_token().value;


            if ((previous.type == token_t::e_add || previous.type == token_t::e_sub) )
            {
                std::cout << "corrected number val " << std::endl;
                std::cout << "current possition " << current_token().position << " and previous " << previous.position << std::endl;

                stack_Var = previous.value + stack_Var;
            }

            *(int*)variable->data = std::stoi(stack_Var);
            var->expression->variables.push_back(variable);
            func.Stack[var->Name] = variable;

            std::cout << "Added variable " << var->Name << " to expression stack function with value " << std::stoi(current_token().value) << std::endl;
        }
        else if (current_token().type == token_t::e_symbol) {
          
            auto itx = func.Stack.find(current_token().value);
            if (itx != func.Stack.end()) {
                var->expression->variables.push_back(itx->second);

                var->data = std::malloc(sizeof(int));

                *(int*)var->data = 0;

                std::cout << "Mearsa si cu symbolu " << std::endl;

                func.Stack[var->Name] = var;
            }
            else {
                std::cout << "Couldn't find variable " << var->Name << " in function stack." << std::endl;
            }
          
        }
        else if (current_token().type == token_t::e_add){
            var->expression->OperationsSize++;
        }
        


         previous = current_token();

         std::cout << current_token().to_str(current_token().type) << std::endl;

         next_token();
    }
       
       
 /*   next_token();*/
    
    return true;
}
