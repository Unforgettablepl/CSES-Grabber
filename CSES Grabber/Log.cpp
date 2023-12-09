#include "Log.h"
#include <map>

std::map<std::string, int> lookup = {
	{"full", 1},
	{"zero", 2},
	{"partial", 3},
	{"busted", 4},
	{"pending", 5},
	{"compile-err", 6},
};

Log::Log(std::string time, std::string res, int prob, std::string probname)
{
	year = stoi(time.substr(0, 4));
	month = stoi(time.substr(5, 2));
	day = stoi(time.substr(8, 2));
	hour = stoi(time.substr(11, 2));
	minute = stoi(time.substr(14, 2));
	second = stoi(time.substr(17, 2));
	result = lookup[res];
	problem_id = prob;
	problem_name = probname;
}

bool Log::operator<(const Log& other) const
{
	if(year != other.year)
		return year < other.year;
	if(month != other.month)
		return month < other.month;
	if(day != other.day)
		return day < other.day;
	if(hour != other.hour)
		return hour < other.hour;
	if(minute != other.minute)
		return minute < other.minute;
	if(second != other.second)
		return second < other.second;
	return false;
}

Log::operator std::string() const
{
	std::string ans = std::to_string(year) + '-';
	if(month < 10)
		ans += '0';
	ans += std::to_string(month) + '-';
	if(day < 10)
		ans += '0';
	ans += std::to_string(day) + ' ';
	if(hour < 10)
		ans += '0';
	ans += std::to_string(hour) + ':';
	if(minute < 10)
		ans += '0';
	ans += std::to_string(minute) + ':';
	if(second < 10)
		ans += '0';
	ans += std::to_string(second) + ' ';
	if(result == 1)
		ans += "Accepted";
	else if(result == 2)
		ans += "Wrong answer";
	else if(result == 3)
		ans += "Partial";
	else if(result == 4)
		ans += "Busted";
	else if(result == 5)
		ans += "Pending";
	else if(result == 6)
		ans += "Compilation Error";
	ans += ' ';
	ans += std::to_string(problem_id);
	ans+= ' ';
	ans+= problem_name;
	return ans;
}
