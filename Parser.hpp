#pragma once

class Function;

class JsParser : public lexertk::parser_helper
{
public:
    bool ProcessFunction(std::string& func_def, Function& fd);
  
    bool ProcessVariable(Function& func);


};