#pragma once
#include "Controller.h"
#include <iostream>

const std::map<std::string, uint32_t> COMMAND_CODES = {
		{"var", 1},
		{"let", 2},
		{"fn", 3},
		{"print", 4},
		{"printvars", 5},
		{"printfns", 6}
};

void Controller::HandleCommand(const std::string& line) //выделить обрабоку в отельный класс
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
		HandlePrint(restLine);
		break;
	case 5:
		m_calculator.PrintVars();
		break;
	case 6:
		m_calculator.PrintFunctions();
		break;
	default:
		break;
	}
}

void Controller::HandleVar(const std::string& restLine)
{
	const std::regex varRegex(R"(^([a-zA-Z_]\w*)$)");
	std::string line = DeleteSpaces(restLine);

	std::smatch match;
	if (!std::regex_match(line, match, varRegex))
	{
		throw std::invalid_argument("Invalid usage\n");
	}
	std::string identifier = match[1].str();

	m_calculator.CreateVar(identifier);
}

void Controller::HandleLet(const std::string& restLine)
{
	std::string line = DeleteSpaces(restLine);
	const std::regex letDouble(R"(^([a-zA-Z_]\w*)=([-]?(0|[1-9]\d*)(\.\d+)?)\s*$)");
	const std::regex letVariable(R"(^([a-zA-Z_]\w*)=([a-zA-Z_]\w*)$)");

	std::smatch match;
	if (std::regex_match(line, match, letDouble))
	{
		m_calculator.LetVariableWithNumber(match[1], std::stod(match[2]));
	}
	else if (std::regex_match(line, match, letVariable))
	{
		m_calculator.LetVariableWithVariable(match[1], match[2]);
	}
	else
	{
		throw std::invalid_argument("Invalid usage\n");
	}
}
void Controller::HandleFunction(const std::string& restLine)
{
	std::string line = DeleteSpaces(restLine);
	std::smatch match;
	const std::regex unaryFunctionRegex(R"(^([a-zA-Z_]\w*)=([a-zA-Z_]\w*)$)");
	const std::regex binaryFunctionRegex(R"(^([a-zA-Z_]\w*)=([a-zA-Z_]\w*)([+\-*/])([a-zA-Z_]\w*)$)");

	if (std::regex_match(line, match, unaryFunctionRegex))
	{
		m_calculator.CreateUnaryFunction(match[1], match[2]);
	}
	else if (std::regex_match(line, match, binaryFunctionRegex))
	{
		m_calculator.CreateBinaryFunction(match[1], match[2], match[3], match[4]);
	}
	else
	{
		throw std::invalid_argument("Invalid usage\n");
	}
}
void Controller::HandlePrint(const std::string& restLine)
{
	std::string line = DeleteSpaces(restLine);
	const std::regex printRegex(R"(^([a-zA-Z_]\w*)$)");
	std::smatch match;

	if (std::regex_match(line, match, printRegex))
	{
		m_calculator.Print(match[1]);
	}
	else
	{
		throw std::invalid_argument("Invalid usage\n");
	}
}

std::string Controller::DeleteSpaces(const std::string& line) const
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