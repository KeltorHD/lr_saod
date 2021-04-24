#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> delim(std::string str, std::string delim)
{
	std::vector<std::string> arr;
	size_t prev = 0;
	size_t next;
	size_t delta = delim.length();

	while ((next = str.find(delim, prev)) != std::string::npos)
	{
		arr.push_back(str.substr(prev, next - prev));
		prev = next + delta;
	}

	arr.push_back(str.substr(prev));

	return arr;
}

int main()
{
	std::ifstream file("graph.txt");
	if (!file.is_open())
	{
		std::cout << "NOT OPEN GRAPH.TXT" << std::endl;
		return 1;
	}

	std::vector<std::vector<int>> graph;
	std::vector<std::string> file_vec;
	std::vector<int> name_ver;

	{
		std::string tmp;
		while (std::getline(file, tmp))
		{
			file_vec.push_back(tmp);
			name_ver.push_back(std::atoi(delim(tmp, ":")[0].c_str()));
		}
	}

	for (size_t i = 0; i < file_vec.size(); i++)
	{
		file_vec[i].erase(std::remove(file_vec[i].begin(), file_vec[i].end(), ' '), file_vec[i].end());
		std::cout << file_vec[i] << std::endl;
	}

	graph.resize(file_vec.size());
	for (size_t i = 0; i < file_vec.size(); i++)
	{
		graph[i].resize(file_vec.size());
	}

	for (size_t i = 0; i < file_vec.size(); i++)
	{
		int first = std::atoi(delim(file_vec[i], ":")[0].c_str());
		/*int first = std::atoi(delim(delim(file_vec[i], ":")[1], " ")[0].c_str());*/
		
		if (file_vec.size() >= 1)
		{
			std::vector<std::string> seconds{ delim(delim(file_vec[i], ":")[1], ",") };

			for (size_t j = 0; j < seconds.size(); j++)
			{
				//std::cout << "second[i]: " << seconds[i] << std::endl;
				int second = std::atoi(seconds[j].c_str());

				std::cout << "connect " << first << "-" << second << std::endl;

				int f_first = std::distance(name_ver.begin(), std::find(name_ver.begin(), name_ver.end(), first));
				int s_second = std::distance(name_ver.begin(), std::find(name_ver.begin(), name_ver.end(), second));
				graph[f_first][s_second] = 1;
				graph[s_second][f_first] = 1;
			}
		}
	}

	std::cout << "\t";
	for (size_t i = 0; i < name_ver.size(); i++)
	{
		std::cout << name_ver[i] << "\t";
	}
	std::cout << std::endl;
	for (size_t i = 0; i < graph.size(); i++)
	{
		std::cout << name_ver[i] << "\t";
		for (size_t j = 0; j < graph[i].size(); j++)
		{
			std::cout << graph[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}