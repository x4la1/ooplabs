#include "Function.h"
#include <map>

const std::map<std::string, OperationType> OPERATION_TYPES = {
	{"+", OperationType::Plus},
	{"-", OperationType::Minus},
	{"*", OperationType::Multiply},
	{"/", OperationType::Divide}
};


Function::Function(const std::string& name, const std::string& opearnd)
{
	m_leftOperand = opearnd;
	m_name = name;
}
Function::Function(const std::string& name, const std::string& leftOperand, const std::string& operation, const std::string& rightOperand)
{
	m_operation = OPERATION_TYPES.find(operation)->second;
	m_name = name;
	m_leftOperand = leftOperand;
	m_rightOperand = rightOperand;
}