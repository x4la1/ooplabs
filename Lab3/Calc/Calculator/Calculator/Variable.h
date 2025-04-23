#pragma once
#include <string>
#include <limits>

const double NAN_VALUE = std::numeric_limits<double>::quiet_NaN();

class Variable
{
public:
	Variable() = default;
	Variable(const std::string& name);
	std::string m_name;
	double m_value = NAN_VALUE;
};