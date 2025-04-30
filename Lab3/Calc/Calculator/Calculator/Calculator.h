#pragma once
#include <map>
#include <string>
#include "Function.h"
#include "Variable.h"
#include <optional>
#include <memory>
#include <regex>

class Calculator //убрать имя из структур
{
public:
	void Print(const std::string& name);
	void PrintVars() const;
	void PrintFunctions();
	void CreateVar(const std::string& identidier);
	void LetVariableWithNumber(const std::string& identifier, const double& value);
	void LetVariableWithVariable(const std::string& identifier1, const std::string& identifier2);
	void CreateUnaryFunction(const std::string& identifier1, const std::string& identifier2);
	void CreateBinaryFunction(const std::string& identifier1, const std::string& identifier2, const std::string& operation, const std::string& identifier3); //naming

private:
	bool IsIdentifierExist(const std::string& variableName) const;
	std::optional<std::shared_ptr<Variable>> FindVariable(const std::string& name);
	std::optional<std::shared_ptr<Function>> FindFunction(const std::string& name);
	double GetFunctionResult(std::shared_ptr<Function>& function);
	double Calculate(const double& leftValue, const double& rightValue, const OperationType& operation) const;
	std::map<std::string, std::shared_ptr<Variable>> m_variables;
	std::map<std::string, std::shared_ptr<Function>> m_functions;
};