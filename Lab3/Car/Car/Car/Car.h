#include <iostream>
#include <map>

enum class Direction
{
	Forward,
	StandStill,
	Backward,
};

class Car
{
public:
	Car();
	bool TurnOnEngine();
	bool SetGear(const int& gear);
	bool SetSpeed(const int& speed);
	bool TurnOffEngine();
	int GetSpeed() const;
	int GetGear() const;
	bool IsTurnedOn() const;
	Direction GetDirection() const;

private:
	bool IsValidGear(const int& gear);
	bool SetBackwardGear();
	int m_speed;
	int m_gear;
	bool m_isEngineTurnedOn;
	Direction m_direction;
	const std::map<int, std::pair<int, int>> m_gearSpeedRanges = {
		{ -1, { 0, 20 } },
		{ 0, { 0, 150 } },
		{ 1, { 0, 30 } },
		{ 2, { 20, 50 } },
		{ 3, { 30, 60 } },
		{ 4, { 40, 90 } },
		{ 5, { 50, 150 } }
	};
};