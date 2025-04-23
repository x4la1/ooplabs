#pragma once
#include <map>
#include <string>
#include "Function.h"
#include "Variable.h"
#include <optional>
#include <memory>
#include <regex>

class Calculator
{
public:
	void HandleCommand(const std::string& command);

private:
	void Print(const std::string& name);
	void PrintVars() const;
	void PrintFunctions();
	void HandleVar(const std::string& restLine);
	void HandleLet(const std::string& restLine);
	void HandleFunction(const std::string& restLine);
	bool IsIdentifierExist(const std::string& variableName) const;
	std::string DeleteSpaces(const std::string& line) const;
	std::optional<std::shared_ptr<Variable>> FindVariable(const std::string& name);
	std::optional<std::shared_ptr<Function>> FindFunction(const std::string& name);
	void ProcessLetWithNumber(const std::smatch& match);
	void ProcessLetWithVariable(const std::smatch& match);
	void ProcessUnaryFunction(const std::smatch& match);
	void ProcessBinaryFunction(const std::smatch& match);
	double GetFunctionResult(std::shared_ptr<Function>& function);
	double Calculate(const double& leftValue, const double& rightValue, const OperationType& operation) const;
	std::map<std::string, std::shared_ptr<Variable>> m_variables;
	std::map<std::string, std::shared_ptr<Function>> m_functions;
};