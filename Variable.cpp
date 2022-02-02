
#include "lexertk.h"
#include "Expression.hpp"
#include "Variable.h"
#include <iostream>

void Variable::RuntimeExpression() {

	if (expression->variables.size() <= 0) return;

	int value = *(int*)data;

	for (size_t i = 0; i < expression->variables.size(); i++)
	{
		value += *(int*)expression->variables[i]->data;
	}

	*(int*)data = value;
	
	std::cout << "Variable < " << Name  << "  >  evaluated at runtime with value " << value << std::endl;
}