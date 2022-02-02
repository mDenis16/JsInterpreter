#pragma once
#include <vector>

enum DataType {
	DT_Pointer,
	DT_Integer
};
class Variable;
class StackVariable;

class Expression {
public:
	std::vector<StackVariable*> variables;
	int OperationsSize = 0;
};
class StackVariable {
public:
	void* data;
};
class Variable : public StackVariable {
public:

	void* data;
	std::string Name;
	Expression* expression;
	void RuntimeExpression();
};


