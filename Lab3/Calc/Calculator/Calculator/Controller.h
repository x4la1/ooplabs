#pragma once
#include "Calculator.h"

class Controller
{
public:
	void HandleCommand(const std::string& line);

private:
	void HandleVar(const std::string& restLine);
	void HandleLet(const std::string& restLine);
	void HandleFunction(const std::string& restLine);
	void HandlePrint(const std::string& restLine);
	std::string DeleteSpaces(const std::string& line) const;
	Calculator m_calculator;
};