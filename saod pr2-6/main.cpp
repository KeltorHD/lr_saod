#include "hash_table.hpp"

#include <iostream>
#include <vector>

struct info
{
	std::string key;
	int count;
	int cost;
};

int main()
{
	system("chcp 1251>nul");

	std::vector<info> data;
	std::fstream ifs("file.txt");
	std::string tmp;
	while (ifs >> tmp)
	{
		int count{};
		int cost{};
		ifs >> count >> cost;
		data.push_back({ tmp,count, cost });
	}

	Hash_table hash;

	for (auto& i : data)
	{
		hash.insert(i.key, std::to_string(i.count) + " " + std::to_string(i.cost));
	}

	data.push_back({ "lada", 100, 1 });
	//hash.insert(data[data.size() - 1].key, data[data.size() - 1].count);
	std::cout << "find: " << std::endl;

	for (size_t i = 0; i < data.size(); i++)
	{
		std::string dat{};
		if (hash.find(data[i].key, dat))
		{

			std::cout << "find: " << data[i].key << " count:" << dat[0] << ", cost: " << dat[2] << std::endl;
		}
		else
		{
			std::cout << "not find: " << data[i].key << std::endl;
		}
	}

	return 0;
}