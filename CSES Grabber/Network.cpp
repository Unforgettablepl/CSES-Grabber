#include "Network.h"

size_t writedata(char* buffer, size_t size, size_t nmemb, void* userp)
{
	reinterpret_cast<std::string*>(userp)->append(buffer, size * nmemb);
	return size * nmemb;
}


Network::Network()
{
	curl = curl_easy_init();
	if(curl == nullptr)
	{
		std::cerr << "Curl failed to initialize\n";
		exit(-1);
	}
}

std::vector<Log> Network::get(int id, std::string probname, std::string login_id)
{
	std::string html;
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writedata);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);
	curl_easy_setopt(curl, CURLOPT_URL, ("https://cses.fi/problemset/view/" + std::to_string(id)).c_str());
    curl_easy_setopt(curl, CURLOPT_COOKIE, ("PHPSESSID="+login_id).c_str());
	res = curl_easy_perform(curl);
	if(res != CURLE_OK)
	{
		std::cerr << "Curl error: " << curl_easy_strerror(res) << '\n';
		exit(-1);
	}
	int curr_parse = html.find("Your submissions");
	if(curr_parse == std::string::npos)
	{
		throw std::runtime_error("Logged Out");
	}
	std::vector<Log> ans;
	while(true)
	{
		curr_parse = html.find("result", curr_parse);
		if(curr_parse == std::string::npos)
			break;
		curr_parse = html.find('>', curr_parse + 1);
		curr_parse++;
		int result_parse = html.find("icon", curr_parse);
		result_parse += 5;
		Log log(html.substr(curr_parse, html.find('<', curr_parse) - curr_parse), html.substr(result_parse, html.find('"', result_parse + 1) - result_parse), id, probname);
		ans.emplace_back(log);
	}
	curl_easy_reset(curl);
	return ans;
}
