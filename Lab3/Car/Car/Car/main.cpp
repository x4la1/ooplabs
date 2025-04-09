#include "Car.h"
#include <iostream>
#include <map>
#include <string>
#include <windows.h>

const std::map<std::string, int> COMMAND_CODE = {
	{ "Info", 1 },
	{ "EngineOn", 2 },
	{ "EngineOff", 3 },
	{ "SetGear", 4 },
	{ "SetSpeed", 5 },
	{ "Exit", 6 }
};

std::string DirectionToString(const Direction& direction)
{
	if (direction == Direction::Backward)
	{
		return "backward";
	}
	if (direction == Direction::Forward)
	{
		return "forward";
	}

	return "standing still";
}

std::string GetEngineStatus(const bool& isTurnedOn)
{
	if (isTurnedOn)
	{
		return "on";
	}

	return "off";
}

void Info(const Car& car)
{
	std::cout << "Engine: " << GetEngineStatus(car.IsTurnedOn()) << "\n"
			  << "Direciton: " << DirectionToString(car.GetDirection()) << "\n"
			  << "Speed: " << car.GetSpeed() << "\n"
			  << "Gear: " << car.GetGear() << "\n";
}

bool StringToNumber(const std::string& line, int& value)
{
	int number;
	try
	{
		number = std::stoi(line);
	}
	catch (std::invalid_argument& e)
	{
		return false;
	}
	catch (std::out_of_range& e)
	{
		return false;
	}

	value = number;
	return true;
}

void SetupConsoleCP()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
}

int main()
{
	SetupConsoleCP();
	Car car;
	std::string command{};
	std::map<std::string, int>::const_iterator foundedCode{};
	int value{};
	std::string argument{};
	while (true)
	{
		std::cin >> command;
		foundedCode = COMMAND_CODE.find(command);

		if (foundedCode == COMMAND_CODE.end())
		{
			std::cout << "Unknown command\n";
			continue;
		}

		switch (COMMAND_CODE.at(command))
		{
		case 1:
			Info(car);
			break;
		case 2:
			car.TurnOnEngine();
			break;
		case 3:
			car.TurnOffEngine();
			break;
		case 4:
			std::cin >> argument;

			if (!StringToNumber(argument, value))
			{
				std::cout << "Invalid command argument\n";
				break;
			}

			car.SetGear(value);
			break;
		case 5:
			std::cin >> argument;

			if (!StringToNumber(argument, value))
			{
				std::cout << "Invalid command argument\n";
				break;
			}

			car.SetSpeed(value);
			break;
		case 6:
			return 0;
		default:
			break;
		}
	}

	return 0;
}
