#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#define N 15
#define SURNAME "ПРОЩЕНКОВ "

int main()
{
	system("chcp 65001>nul");

	std::ifstream ifs("input.txt");
	std::vector<std::string> mas;

	std::string input{};
	while (std::getline(ifs, input))
	{
		int counter{ std::count(input.begin(), input.end(), ' ') };
		int prob_per_insert{ (counter + N) / N };
		int counter_prob{};
		int count_all_insert{};
		for (int i = 0; i < input.length(); i++)
		{
			if (count_all_insert >= N)
				break;
			if (input[i] == ' ')
			{
				if (counter_prob >= prob_per_insert)
				{
					input.insert(i + 1, SURNAME);
					counter_prob = 0;
					count_all_insert++;
				}
				counter_prob++;
			}
		}
		mas.push_back(input);
	}

	ifs.close();

	std::ofstream ofs("input.txt");
	for (auto& i : mas)
	{
		ofs << i << std::endl;
	}
	ofs.close();


	return bool(std::cout);
}