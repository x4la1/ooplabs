#include "Calculator.h"
#include <iostream>
#include <iomanip>
#include <regex>
#include <map>
#include <optional>
#include <memory>
//unique_ptr

void Calculator::CreateVar(const std::string& identifier)
{

	if (IsIdentifierExist(identifier))
	{
		throw std::invalid_argument("Name already exists\n");
	}

	std::shared_ptr<Variable> variable(new Variable(identifier));
	m_variables.insert(std::make_pair(variable->m_name, variable));
}


void Calculator::LetVariableWithNumber(const std::string& identifier, const double& value)
{
	std::optional<std::shared_ptr<Variable>> foundedVariable = FindVariable(identifier);

	if (foundedVariable != std::nullopt)
	{
		foundedVariable.value()->m_value = value;
		return;
	}

	if (IsIdentifierExist(identifier)) //isfunctionexist
	{
		throw std::invalid_argument("Name already exists\n");
	}

	std::shared_ptr<Variable> variable(new Variable(identifier));
	variable->m_value = value;
	m_variables.insert(std::make_pair(identifier, variable));
}

void Calculator::LetVariableWithVariable(const std::string& identifier1, const std::string& identifier2)
{
	std::optional<std::shared_ptr<Variable>> foundedVariable1 = FindVariable(identifier1);
	std::optional<std::shared_ptr<Variable>> foundedVariable2 = FindVariable(identifier2);
	std::optional<std::shared_ptr<Function>> foundedFunction2 = FindFunction(identifier2);

	if (foundedVariable2 == std::nullopt && foundedFunction2 == std::nullopt)
	{
		throw std::invalid_argument("Name does not exist\n");
	}

	if (foundedVariable1 != std::nullopt) //has_value()
	{
		if (foundedVariable2.has_value())
		{
			foundedVariable1.value()->m_value = foundedVariable2.value()->m_value;
		}
		else
		{
			foundedVariable1.value()->m_value = GetFunctionResult(foundedFunction2.value());
		}

		return;
	}

	if (IsIdentifierExist(identifier1)) //IsFunctionexist
	{
		throw std::invalid_argument("Name already exists\n");
	}

	std::shared_ptr<Variable> variable(new Variable(identifier1));
	if (foundedVariable2.has_value())
	{
		variable->m_value = foundedVariable2.value()->m_value;
	}
	else
	{
		variable->m_value = GetFunctionResult(foundedFunction2.value());
	}

	m_variables.insert(std::make_pair(variable->m_name, variable));
}

void Calculator::CreateBinaryFunction(const std::string& identifier1, const std::string& identifier2, const std::string& operation, const std::string& identifier3)
{
	std::optional<std::shared_ptr<Variable>> foundedVariable1 = FindVariable(identifier2);
	std::optional<std::shared_ptr<Function>> foundedFunction1 = FindFunction(identifier2);
	std::optional<std::shared_ptr<Variable>> foundedVariable2 = FindVariable(identifier3);
	std::optional<std::shared_ptr<Function>> foundedFunction2 = FindFunction(identifier3);
	std::string leftOperandName;
	std::string rightOperandName;

	if ((foundedVariable1 == std::nullopt && foundedFunction1 == std::nullopt) || (foundedVariable2 == std::nullopt && foundedFunction2 == std::nullopt))
	{
		throw std::invalid_argument("Name does not exist\n");
	}
	//find identificator
	if (foundedFunction1 != std::nullopt)
	{
		leftOperandName = foundedFunction1.value()->m_name;
	}
	else
	{
		leftOperandName = foundedVariable1.value()->m_name;
	}

	if (foundedFunction2 != std::nullopt)
	{
		rightOperandName = foundedFunction2.value()->m_name;
	}
	else
	{
		rightOperandName = foundedVariable2.value()->m_name;
	}

	m_functions.insert(std::make_pair(identifier1, (new Function(identifier1, leftOperandName, operation, rightOperandName))));
}

void Calculator::CreateUnaryFunction(const std::string& identifier1, const std::string& identifier2)
{
	std::optional<std::shared_ptr<Variable>> foundedVariable = FindVariable(identifier2);
	std::optional<std::shared_ptr<Function>> foundedFunction = FindFunction(identifier2);
	//is identifier exist
	if (foundedVariable == std::nullopt && foundedFunction == std::nullopt)
	{
		throw std::invalid_argument("Name does not exist\n");
	}

	if (IsIdentifierExist(identifier1))
	{
		throw std::invalid_argument("Name already exists\n");
	}

	if (foundedFunction != std::nullopt)
	{
		m_functions.insert(std::make_pair(identifier1, std::shared_ptr<Function>(new Function(identifier1, foundedFunction.value()->m_name))));
	}
	else
	{
		m_functions.insert(std::make_pair(identifier1, std::shared_ptr<Function>(new Function(identifier1, foundedVariable.value()->m_name))));
	}

}

double Calculator::GetFunctionResult(std::shared_ptr<Function>& function)
{
	std::optional<std::shared_ptr<Variable>> foundedVariable1;
	std::optional<std::shared_ptr<Function>> foundedFunction1;
	std::optional<std::shared_ptr<Variable>> foundedVariable2;
	std::optional<std::shared_ptr<Function>> foundedFunction2;
	double leftValue, rightValue = NAN_VALUE;

	foundedFunction1 = FindFunction(function->m_leftOperand);
	foundedVariable1 = FindVariable(function->m_leftOperand);

	if (!foundedFunction1.has_value())
	{
		leftValue = foundedVariable1.value()->m_value;
	}
	else if (!foundedVariable1.has_value())
	{
		leftValue = GetFunctionResult(foundedFunction1.value());
	}

	if (function->m_operation == OperationType::Nothing)
	{
		return leftValue;
	}

	foundedFunction2 = FindFunction(function->m_rightOperand);
	foundedVariable2 = FindVariable(function->m_rightOperand);

	if (!foundedFunction2.has_value())
	{
		rightValue = foundedVariable2.value()->m_value;
	}
	else if (!foundedVariable2.has_value())
	{
		rightValue = GetFunctionResult(foundedFunction2.value());
	}


	if (leftValue == NAN_VALUE || rightValue == NAN_VALUE)
	{
		return NAN_VALUE;
	}

	return Calculate(leftValue, rightValue, function->m_operation);
}

double Calculator::Calculate(const double& leftValue, const double& rightValue, const OperationType& operation) const
{
	switch (operation)
	{
	case OperationType::Plus:
		return leftValue + rightValue;
	case OperationType::Minus:
		return leftValue - rightValue;
	case OperationType::Multiply:
		return leftValue * rightValue;
	case OperationType::Divide:
		if (rightValue == 0.0)
		{
			return NAN_VALUE;
		}
		return leftValue / rightValue;
	default:
		break;
	}
}

std::optional<std::shared_ptr<Function>> Calculator::FindFunction(const std::string& name)
{//get?
	for (auto functions : m_functions)
	{
		if (functions.first == name)
		{
			return functions.second;
		}
	}

	return std::nullopt;
}

void Calculator::Print(const std::string& name)
{
	bool isFound = false;

	for (auto variable : m_variables)
	{
		if (variable.first == name)
		{
			std::cout << variable.first << ":" << std::fixed << std::setprecision(3) << variable.second->m_value << "\n";
			isFound = true;
			return;
		}
	}

	for (auto function : m_functions)
	{
		if (function.first == name)
		{
			isFound = true;
			std::cout << function.first << ":" << std::fixed << std::setprecision(3) << GetFunctionResult(function.second) << "\n";
		}
	}

	if (isFound == false)
	{
		throw std::invalid_argument("Name does not exist\n");
	}
}

void Calculator::PrintVars() const
{
	for (auto variable : m_variables)
	{
		std::cout << variable.first << ":" << std::fixed << std::setprecision(3) << variable.second->m_value << "\n";
	}
}

void Calculator::PrintFunctions()
{
	for (auto function : m_functions)
	{
		std::cout << function.first << ":" << std::fixed << std::setprecision(3) << GetFunctionResult(function.second) << "\n";
	}
}

bool Calculator::IsIdentifierExist(const std::string& variableName) const
{
	for (auto variable : m_variables)
	{
		if (variable.first == variableName)
		{
			return true;
		}
	}

	for (auto function : m_functions)
	{
		if (function.first == variableName)
		{
			return true;
		}
	}

	return false;
}

std::optional<std::shared_ptr<Variable>> Calculator::FindVariable(const std::string& name)
{
	for (auto& variable : m_variables)
	{
		if (variable.first == name)
		{
			return variable.second;
		}
	}

	return std::nullopt;
}