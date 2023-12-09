#pragma once
#include <string>


class Log
{
public:
	int hour, minute, second, day, month, year, result, problem_id;
	std::string problem_name;
	Log(std::string time,std::string res, int prob, std::string probname);
	bool operator<(const Log& other) const;
	operator std::string() const;
};

