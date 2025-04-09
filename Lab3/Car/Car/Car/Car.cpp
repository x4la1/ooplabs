#include "Car.h"

int Car::GetSpeed() const
{
	return m_speed;
}

int Car::GetGear() const
{
	return m_gear;
}

bool Car::IsTurnedOn() const
{
	return m_isEngineTurnedOn;
}

Direction Car::GetDirection() const
{
	return m_direction;
}

bool Car::TurnOffEngine()
{
	if (m_gear == 0 && m_speed == 0) 
	{
		m_isEngineTurnedOn = false;
		return true;
	}

	std::cout << "Car must be stopped and in neutral gear\n";
	return false;
}

bool Car::TurnOnEngine()
{
	m_isEngineTurnedOn = true;
	return true;
}

Car::Car()
{
	m_isEngineTurnedOn = false;
	m_speed = 0;
	m_gear = 0;
	m_direction = Direction::StandStill;
}

bool Car::SetBackwardGear()
{
	if (m_gear != -1 && m_speed != 0) // 2 20 false; 2 0 true; -1 1 true; -1 0 true;
	{
		std::cout << "Cannot reverse while moving\n";
		return false;
	}

	m_gear = -1;
	return true;
}

bool Car::SetGear(const int& gear)
{
	if (!Car::IsValidGear(gear))
	{
		return false;
	}

	if (!m_isEngineTurnedOn && gear != 0)
	{
		std::cout << "Ñannot set gear while engine is off\n";
		return false;
	}

	if (gear == 0)
	{
		m_gear = 0;
		return true;
	}

	if (gear == -1)
	{
		return Car::SetBackwardGear();
	}

	if (m_direction == Direction::Backward)
	{
		std::cout << "Cannot set forward gear while car moving backward\n";
		return false;
	}

	if (m_speed < GEAR_SPEED_RANGES.at(gear).first || m_speed > GEAR_SPEED_RANGES.at(gear).second)
	{
		std::cout << "Unsuitable current speed\n";
		return false;
	}
	
	m_gear = gear;
	return true;
}

bool Car::IsValidGear(const int& gear)
{
	if (gear < -1 || gear > 5)
	{
		std::cout << "Invalid gear\n";
		return false;
	}

	return true;
}

bool Car::SetSpeed(const int& speed)
{
	if (speed < 0)
	{
		std::cout << "Speed cannot be negative\n";
		return false;
	}

	if (!m_isEngineTurnedOn)
	{
		std::cout << "Cannot set speed while engine is off\n";
		return false;
	}

	if (m_gear == 0 && speed > m_speed)
	{
		std::cout << "Cannot accelerate on neutral\n";
		return false;
	}

	if (speed < GEAR_SPEED_RANGES.at(m_gear).first || speed > GEAR_SPEED_RANGES.at(m_gear).second)
	{
		std::cout << "Speed is out of gear range\n";
		return false;
	}

	m_speed = speed;
	if (m_gear == -1 && speed > 0)
	{
		m_direction = Direction::Backward;
	}

	if (m_gear >= 1 && speed > 0)
	{
		m_direction = Direction::Forward;
	}

	if (speed == 0)
	{
		m_direction = Direction::StandStill;
	}

	return true;
}