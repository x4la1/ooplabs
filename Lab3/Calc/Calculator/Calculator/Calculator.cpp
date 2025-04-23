#include "Calculator.h"
#include <iostream>
#include <iomanip>
#include <regex>
#include <map>
#include <optional>
#include <memory>

const std::map<std::string, uint32_t> COMMAND_CODES = {
		{"var", 1},
		{"let", 2},
		{"fn", 3},
		{"print", 4},
		{"printvars", 5},
		{"printfns", 6}
};

void Calculator::HandleCommand(const std::string& line)
{
	std::string command, restLine;
	size_t spacePosition = line.find(' ');

	if (spacePosition != std::string::npos) {
		command = line.substr(0, spacePosition);
		restLine = line.substr(spacePosition + 1);
	}
	else {
		command = line;
	}

	uint32_t code;
	auto result = COMMAND_CODES.find(command);
	if (result == COMMAND_CODES.end())
	{
		throw std::invalid_argument("Unknown command\n");
	}
	code = result->second;

	switch (code)
	{
	case 1:
		HandleVar(restLine);
		break;
	case 2:
		HandleLet(restLine);
		break;
	case 3:
		HandleFunction(restLine);
		break;
	case 4:
		Print(restLine);
		break;
	case 5:
		PrintVars();
		break;
	case 6:
		PrintFunctions();
		break;
	default:
		break;
	}
}

void Calculator::HandleVar(const std::string& restLine)
{
	const std::regex varRegex(R"(^([a-zA-Z_]\w*)$)");
	std::string line = DeleteSpaces(restLine);

	std::smatch match;
	if (!std::regex_match(line, match, varRegex))
	{
		throw std::invalid_argument("Invalid usage\n");
	}
	std::string identifier = match[1].str();

	if (IsIdentifierExist(identifier))
	{
		throw std::invalid_argument("Name already exists\n");
	}

	std::shared_ptr<Variable> variable(new Variable(identifier));
	m_variables.insert(std::make_pair(variable->m_name, variable));
}

void Calculator::HandleLet(const std::string& restLine)
{
	std::string line = DeleteSpaces(restLine);
	const std::regex letDouble(R"(^([a-zA-Z_]\w*)=([-]?(0|[1-9]\d*)(\.\d+)?)\s*$)");
	const std::regex letVariable(R"(^([a-zA-Z_]\w*)=([a-zA-Z_]\w*)$)");

	std::smatch match;
	if (std::regex_match(line, match, letDouble))
	{
		ProcessLetWithNumber(match);
	}
	else if (std::regex_match(line, match, letVariable))
	{
		ProcessLetWithVariable(match);
	}
	else
	{
		throw std::invalid_argument("Invalid usage\n");
	}

}

void Calculator::ProcessLetWithNumber(const std::smatch& match)
{
	std::string identifier = match[1];
	double value = std::stod(match[2]);
	std::optional<std::shared_ptr<Variable>> foundedVariable = FindVariable(identifier);

	if (foundedVariable != std::nullopt)
	{
		foundedVariable.value()->m_value = value;
		return;
	}

	if (IsIdentifierExist(identifier))
	{
		throw std::invalid_argument("Name already exists\n");
	}

	std::shared_ptr<Variable> variable(new Variable(identifier));
	variable->m_value = value;
	m_variables.insert(std::make_pair(identifier, variable));
}

void Calculator::ProcessLetWithVariable(const std::smatch& match)
{
	std::string identifier1 = match[1];
	std::string identifier2 = match[2];
	std::optional<std::shared_ptr<Variable>> foundedVariable1 = FindVariable(identifier1);
	std::optional<std::shared_ptr<Variable>> foundedVariable2 = FindVariable(identifier2);

	if (foundedVariable2 == std::nullopt)
	{
		throw std::invalid_argument("Name does not exist\n");
	}

	if (foundedVariable1 != std::nullopt)
	{
		foundedVariable1.value()->m_value = foundedVariable2.value()->m_value;
		return;
	}

	if (IsIdentifierExist(identifier1))
	{
		throw std::invalid_argument("Name already exists\n");
	}

	std::shared_ptr<Variable> variable(new Variable(identifier1));
	variable->m_value = foundedVariable2.value()->m_value;
	m_variables.insert(std::make_pair(variable->m_name, variable));
}

void Calculator::HandleFunction(const std::string& restLine)
{
	std::string line = DeleteSpaces(restLine);
	std::smatch match;
	const std::regex unaryFunctionRegex(R"(^([a-zA-Z_]\w*)=([a-zA-Z_]\w*)$)");
	const std::regex binaryFunctionRegex(R"(^([a-zA-Z_]\w*)=([a-zA-Z_]\w*)([+\-*/])([a-zA-Z_]\w*)$)");

	if (std::regex_match(line, match, unaryFunctionRegex))
	{
		ProcessUnaryFunction(match);
	}
	else if (std::regex_match(line, match, binaryFunctionRegex))
	{
		ProcessBinaryFunction(match);
	}
	else
	{
		throw std::invalid_argument("Invalid usage\n");
	}

}

void Calculator::ProcessBinaryFunction(const std::smatch& match)
{
	std::string identifier1 = match[1];
	std::string identifier2 = match[2];
	std::string identifier3 = match[4];
	std::string operation = match[3];
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

void Calculator::ProcessUnaryFunction(const std::smatch& match)
{
	std::string identifier1 = match[1];
	std::string identifier2 = match[2];
	std::optional<std::shared_ptr<Variable>> foundedVariable = FindVariable(identifier2);
	std::optional<std::shared_ptr<Function>> foundedFunction = FindFunction(identifier2);

	if (foundedVariable == std::nullopt && foundedFunction == std::nullopt)
	{
		throw std::invalid_argument("Name does not exist\n");
	}

	if (IsIdentifierExist(identifier1))
	{
		throw std::invalid_argument("Name already exists\n");
	}

	if (foundedFunction != nullptr)
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
	else if(!foundedVariable1.has_value())
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
{
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

std::string Calculator::DeleteSpaces(const std::string& line) const
{
	std::string stringWithoutSpaces;
	for (char ch : line)
	{
		if (!isspace(ch))
		{
			stringWithoutSpaces.push_back(ch);
		}
	}

	return stringWithoutSpaces;
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