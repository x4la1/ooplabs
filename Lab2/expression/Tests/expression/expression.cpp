#include "expression.h"
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

const std::string OPERAND_SYMBOLS{ "()+*" };

std::vector<Token> TokenizeExpression(const std::string& expression)
{
	std::vector<Token> tokens{};

	for (size_t i = 0; i < expression.size(); ++i)
	{
		if (isspace(expression.at(i)))
		{
			continue;
		}

		if (OPERAND_SYMBOLS.find(expression.at(i)) != std::string::npos)
		{
			tokens.push_back({ true, expression.at(i), 0 });
		}
		else
		{
			size_t endNumberPosition = i;
			if (expression.at(i) == '-')
			{
				endNumberPosition++;
			}

			while (endNumberPosition < expression.size() && isdigit(expression.at(endNumberPosition)))
			{
				endNumberPosition++;
			}

			int number = std::stoi(expression.substr(i, endNumberPosition - i));
			tokens.push_back({ false, ' ', number });
			i = endNumberPosition - 1;
		}
	}

	return tokens;
}

int InitResult(const char& operand)
{
	if (operand == '+')
	{
		return 0;
	}

	return 1;
}

int CalculateSubExpression(const char& operand, const int& argsCount, std::stack<int>& values)
{
	int result = InitResult(operand);
	if (argsCount == 1)
	{
		result = values.top();
		values.pop();
	}
	else
	{
		for (int j = 0; j < argsCount; ++j)
		{
			if (operand == '+')
			{
				result += values.top();
			}
			else
			{
				result *= values.top();
			}
			values.pop();
		}
	}

	return result;
}

int CalculateExpression(const std::string& expression)
{
	std::vector<Token> tokens = TokenizeExpression(expression);
	std::stack<int> values{};
	std::stack<char> operands{};
	std::stack<int> argumentsCount{};

	for (size_t i = 0; i < tokens.size(); ++i)
	{
		if (tokens.at(i).isOperand && tokens.at(i).operand == '(')
		{
			i++;
			operands.push(tokens.at(i).operand);
			argumentsCount.push(0);
		}
		else if (tokens.at(i).isOperand && tokens.at(i).operand == ')')
		{
			char operand = operands.top();
			operands.pop();
			int argsCount = argumentsCount.top();
			argumentsCount.pop();

			int result = CalculateSubExpression(operand, argsCount, values);
			values.push(result);

			if (!argumentsCount.empty())
			{
				argumentsCount.top()++;
			}
		}
		else
		{
			values.push(tokens.at(i).value);
			argumentsCount.top()++;
		}
	}

	return values.top();
}
