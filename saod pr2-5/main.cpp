#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

#include "Hash.h"

int main()
{
	std::vector<data> data;
	std::fstream ifs("file.txt");
	std::string tmp;
	while (ifs >> tmp)
	{
		int count{};
		int cost{};
		ifs >> count >> cost;
		data.push_back({ tmp,count, cost });
	}

	Hash hash;

	for (auto& i : data)
	{
		hash.insert(i.key, i.count, i.cost);
	}

	data.push_back({ "lada", 100 });
	//hash.insert(data[data.size() - 1].key, data[data.size() - 1].count);
	std::cout << "find: " << std::endl;

	for (size_t i = 0; i < data.size(); i++)
	{
		int count{};
		int cost{};
		if (hash.find(data[i].key, count, cost))
		{
			std::cout << "done: " << data[i].key << " count:" << count << ", cost: " << cost << std::endl;
		}
		else
		{
			std::cout << "not done: " << data[i].key<< std::endl;
		}
	}

}