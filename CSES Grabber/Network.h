#pragma once
#define CURL_STATICLIB
#include <curl/curl.h>
#include <string>
#include "Log.h"
#include <iostream>
#include <vector>

size_t writedata(char* buffer, size_t size, size_t nmemb, void* userp);

class Network
{
	public:
	CURL* curl;
	CURLcode res;
	Network();
	std::vector<Log> get(int id, std::string probname, std::string login_id);
};