#include <iostream>
#include <fstream>
#include <string>
#include "Network.h"
#include "Log.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

std::ifstream fin;
std::ofstream fout;

int main()
{
	fin.open("cses_list.txt");
	Network network;
	std::string login_id;
	if(getenv("CSES_COOKIE")==nullptr){
		std::cout << "Enter login id: ";
		std::cin >> login_id;
	} else
	{
		login_id = std::string(getenv("CSES_COOKIE"));
	}
	std::string output;
	std::cout << "Enter output file name: ";
	std::cin >> output;
	fout.open(output);
	std::vector<Log> logs;
	std::vector<std::string> probnames(300);
	for(int i=0;i<300;i++)std::getline(fin, probnames[i]);
	int repeat = 0;
	for(int i=1;i<=300;i++)
	{
		std::string probname = probnames[i];
		std::cout << "Downloading submission history for " << probname << '\n';
		try
		{
			int id = stoi(probname.substr(0, probname.find(' ')));
			probname = probname.substr(probname.find(' ') + 1);
			std::vector<Log> log = network.get(id, probname, login_id);
            logs.insert(logs.end(), log.begin(), log.end());
			repeat = 0;
		}
		catch(std::runtime_error&e)
		{
			repeat++;
			std::cout << e.what() << '\n';
			if (repeat == 6)
			{
				std::cout << "Failed to download after 5 attempts.\n";
				std::cout << "Enter Login ID again: ";
				std::cin >> login_id;
				i--;
				continue;
			}
			std::cout << "Waiting for " << pow(2,repeat) << "s\n";
            std::this_thread::sleep_for(std::chrono::seconds(int(pow(2,repeat))));
			i--;
		}
	}
	std::sort(logs.begin(), logs.end());
	for(auto&i:logs)
		fout << std::string(i) << '\n';
	fin.close();
	fout.close();
	std::cout << "Done!\n";
}