#include <string>
#include <vector>

struct Token
{
	bool isOperand;
	char operand;
	int value;
};

std::vector<Token> TokenizeExpression(const std::string& expression);
int CalculateExpression(const std::string& expression);

