#pragma once
#include <unordered_map>


class Variable;
class StackVariable;

class Function {
public:

	std::string Name;
	std::unordered_map<std::string, StackVariable*> Stack;


	std::vector<StackVariable*> FuncVariables;
};