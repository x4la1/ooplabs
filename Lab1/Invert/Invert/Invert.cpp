#include <cmath>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
// 4 2	обработать
using Matrix = std::vector<std::vector<double>>;

const std::set<char> validDigits{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '-' };

bool IsValidChar(char ch)
{
	if (!validDigits.count(ch))
	{
		return false;
	}
	return true;
}

bool IsTokenContainInvalidSymbols(const std::string& token)
{
	return token.find("-.") != std::string::npos
		|| token.find(".-") != std::string::npos;
}

bool IsValidNumber(const std::string& token) //доработать проверки не проходят 1 1 1(пробелы)
{
	if (token.empty())
	{
		return false;
	}

	if (token[0] == '.' || token[0] == '0')
	{
		return false;
	}

	if (IsTokenContainInvalidSymbols(token))
	{
		return false;
	}

	uint32_t dotCount = 0;
	uint32_t minusCount = 0;
	for (size_t i = 1; i < token.length(); i++)
	{
		if (!IsValidChar(token[i]))
		{
			return false;
		}

		if (token[i] == '.')
		{
			dotCount++;
			if (dotCount > 1)
			{
				return false;
			}
		}
		if (token[i] == '-')
		{
			return false;
		}

		
	}

	return true;
}

bool IsNumber(std::string token)
{
	if (!IsValidNumber(token))
	{
		return false;
	}

	try
	{
		std::stod(token);
	}
	catch (std::out_of_range& e)
	{
		return false;
	}
	catch (std::invalid_argument& e)
	{
		return false;
	}

	return true;
}

bool ReadRow(std::istream& input, std::vector<double>& row)
{
	std::string line{};
	if (!std::getline(input, line))
	{
		std::cout << "Invalid matrix format\n";
		return false;
	}

	std::vector<std::string> buff{};
	std::string token{};
	std::stringstream ss{ line };
	while (std::getline(ss, token, '\t'))
	{
		buff.push_back(token);
	}
	if (buff.size() != 3)
	{
		std::cout << "Invalid matrix format\n";	
	}

	uint32_t column = 0;
	for (std::string token: buff)
	{
		column++;
		if (!IsNumber(token))
		{
			std::cout << "Invalid matrix\n";
			return false;
		}
		row[column - 1] = std::stod(token);
	}

	return true;
}

bool IsInvalidRemainingInput(std::istream& input)
{
	std::string line{};
	return std::getline(input, line) && !line.empty();
}

bool ReadMatrixFromStdin(std::istream& input, Matrix& matrix) //stream
{
	for (int rows = 0; rows < 3; rows++)
	{
		if (!ReadRow(input, matrix[rows]))
		{
			return false;
		}
	}

	return true;
}

bool ReadMatrixFromFile(std::ifstream& input, Matrix& matrix)
{
	for (int rows = 0; rows < 3; rows++)
	{
		if (!ReadRow(input, matrix[rows]))
		{
			return false;
		}
	}

	if (IsInvalidRemainingInput(input))
	{
		std::cout << "Invalid matrix format\n";
		return false;
	}

	return true;
}

double FindDeterminant(const Matrix& matrix)
{
	return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
		- matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
		+ matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}

bool InvertMatrix(const Matrix& matrix, Matrix& invertedMatrix)
{
	double determinant = FindDeterminant(matrix);
	if (determinant == 0.0)
	{
		std::cout << "Non-invertible\n";
		return false;
	}

	double invertedDeterminant = 1.0 / determinant;
	invertedMatrix[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) * invertedDeterminant;
	invertedMatrix[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) * invertedDeterminant;
	invertedMatrix[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) * invertedDeterminant;
	invertedMatrix[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) * invertedDeterminant;
	invertedMatrix[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) * invertedDeterminant;
	invertedMatrix[1][2] = (matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2]) * invertedDeterminant;
	invertedMatrix[2][0] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) * invertedDeterminant;
	invertedMatrix[2][1] = (matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1]) * invertedDeterminant;
	invertedMatrix[2][2] = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) * invertedDeterminant;

	return true;
}

void PrintMatrix(const Matrix& matrix)
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			std::cout << std::fixed << std::setprecision(3) << matrix[i][j];
			if (j != 2)
			{
				std::cout << "\t";
			}
			else
			{
				std::cout << "\n";
			}
		}
	}
}

void PrintHelp()
{
	std::cout << "This program inverts 3x3 matrix\n"
			  << "Usage: invert.exe filename OR invert.exe\n"
			  << "filename: A file containing a 3x3 matrix, the numbers are tab-separated\n"
			  << "If file is not provided matrix input via stdin\n";
}

Matrix CreateZeroMatrix()
{

	return {
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 }
	};
}

int main(int argc, char* argv[])
{
	Matrix matrix = CreateZeroMatrix();

	if (argc > 2)
	{
		std::cout << "Type invert.exe -h for help\n";
		return 1;
	}

	if (argc == 1)
	{
		if (!ReadMatrixFromStdin(std::cin, matrix))
		{
			return 1;
		}
	}
	else if (argc == 2)
	{
		if (std::string{ argv[1] } == "-h")
		{
			PrintHelp();
			return 0;
		}

		std::ifstream input(argv[1]);
		if (!input.is_open())
		{
			std::cout << "Failed to open '" << argv[1] << "'\n";
			return 1;
		}

		if (!ReadMatrixFromFile(input, matrix))
		{
			return 1;
		}
	}

	Matrix invertedMatrix = CreateZeroMatrix();

	if (InvertMatrix(matrix, invertedMatrix))
	{
		PrintMatrix(invertedMatrix);
		return 0;
	}

	return 0;
}
