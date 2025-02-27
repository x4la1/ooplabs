#include <cctype>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

enum class Operation
{
	Crypt,
	Decrypt
};

struct Arguments
{
	Operation mode;
	std::string inputFile;
	std::string outputFile;
	int key;
};

bool IsNumber(std::string str)
{
	for (auto item : str)
	{
		if (!std::isdigit(item))
		{
			return false;
		}
	}

	return true;
}


std::optional<Arguments> ParseArguments(const int& argc, char* argv[])
{
	if (argc != 5)
	{
		return std::nullopt;
	}

	Arguments args{};
	std::string firstArgument{ argv[1] };
	if (firstArgument == "crypt")
	{
		args.mode = Operation::Crypt;
	}
	else if (firstArgument == "decrypt")
	{
		args.mode = Operation::Decrypt;
	}
	else
	{
		return std::nullopt;
	}

	args.inputFile = std::string{ argv[2] };
	args.outputFile = std::string{ argv[3] };

	std::string fourthArgument{ argv[4] };
	if (!IsNumber(fourthArgument))
	{
		return std::nullopt;
	}

	int key{};
	try
	{
		key = std::stoi(fourthArgument);
	}
	catch (std::invalid_argument& e)
	{
		return std::nullopt;
	}
	catch (std::out_of_range& e)
	{
		return std::nullopt;
	}

	if (key < 0 || key > 255)
	{
		return std::nullopt;
	}
	args.key = key;

	return args;
}

void PrintUsage()
{
	std::cout << "Usage: Crypt.exe crypt|decrypt <input file> <output file> <key>(0-255)\n";
}

unsigned char MixByte(const unsigned char& byte)
{
	unsigned char mixedByte = 0;
	mixedByte |= ((byte >> 0) & 1) << 2;
	mixedByte |= ((byte >> 1) & 1) << 3;
	mixedByte |= ((byte >> 2) & 1) << 4;
	mixedByte |= ((byte >> 3) & 1) << 6;
	mixedByte |= ((byte >> 4) & 1) << 7;
	mixedByte |= ((byte >> 5) & 1) << 0;
	mixedByte |= ((byte >> 6) & 1) << 1;
	mixedByte |= ((byte >> 7) & 1) << 5;

	return mixedByte;
}

unsigned char CryptByte(const unsigned char& byte, const int& key)
{
	unsigned char cryptedByte = byte ^ key;
	cryptedByte = MixByte(cryptedByte);

	return cryptedByte;
}

void CryptFile(std::ifstream& input, std::ofstream& output, const int& key)
{
	char ch;
	unsigned char byte;
	while (input.get(ch))
	{
		byte = static_cast<unsigned char>(ch);
		byte = CryptByte(byte, key);
		output.put(static_cast<char>(byte));
	}
}

unsigned char UnmixByte(const unsigned char& byte)
{
	unsigned char unmixedByte = 0;
	unmixedByte |= ((byte >> 0) & 1) << 5;
	unmixedByte |= ((byte >> 1) & 1) << 6;
	unmixedByte |= ((byte >> 2) & 1) << 0;
	unmixedByte |= ((byte >> 3) & 1) << 1;
	unmixedByte |= ((byte >> 4) & 1) << 2;
	unmixedByte |= ((byte >> 5) & 1) << 7;
	unmixedByte |= ((byte >> 6) & 1) << 3;
	unmixedByte |= ((byte >> 7) & 1) << 4;

	return unmixedByte;
}

unsigned char DecryptByte(const unsigned char& byte, const int& key)
{
	unsigned char decryptedByte = UnmixByte(byte);
	decryptedByte = decryptedByte ^ key;

	return decryptedByte;
}

void DecryptFile(std::ifstream& input, std::ofstream& output, const int& key)
{
	char ch;
	unsigned char byte;
	while (input.get(ch))
	{
		byte = static_cast<unsigned char>(ch);
		byte = DecryptByte(byte, key);
		output.put(static_cast<char>(byte));
	}
}

int main(int argc, char* argv[]) //вывод ошибки под key
{
	auto arguments = ParseArguments(argc, argv);
	if (arguments == std::nullopt)
	{
		PrintUsage();
		return 1;
	}

	std::ifstream input{ arguments->inputFile, std::ios::binary };
	if (!input.is_open())
	{
		std::cout << "Failed to open input file\n";
		return 1;
	}

	std::ofstream output{ arguments->outputFile, std::ios::binary };
	if (!output.is_open())
	{
		std::cout << "Failed to open output file\n";
		return 1;
	}

	if (arguments->mode == Operation::Crypt)
	{
		CryptFile(input, output, arguments->key);
	}
	else if (arguments->mode == Operation::Decrypt)
	{
		DecryptFile(input, output, arguments->key);
	}

	return 0;
}
