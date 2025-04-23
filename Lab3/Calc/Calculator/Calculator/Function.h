#pragma once
#include <string>

enum class OperationType
{
	Plus,
	Minus,
	Multiply,
	Divide,
	Nothing
};

struct Function
{
public:
	Function() = default;
	Function(const std::string& name, const std::string& opearnd);
	Function(const std::string& name, const std::string& leftOperand, const std::string& operation, const std::string& rightOperand);
	std::string m_name;
	std::string m_leftOperand;
	std::string m_rightOperand;
	OperationType m_operation = OperationType::Nothing;
};