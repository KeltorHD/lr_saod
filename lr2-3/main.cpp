#include "hash_table.hpp"

#include <iostream>
#include <vector>

struct info
{
	std::string id;
	std::string data;
};

int main()
{
	system("chcp 1251>nul");
	Hash_table table;

	std::fstream file("data.txt");
	std::vector<info> datas;

	size_t length{ 5 }; /*количество студентов в файлике*/
	
	for (size_t i = 0; i < length; i++)
	{
		info tmp;
		std::getline(file, tmp.id);
		std::getline(file, tmp.data);

		std::cout << tmp.id << " " << tmp.data << std::endl;
		
		datas.push_back(tmp);
		table.insert(tmp.id, tmp.data);
	}

	/*поиск*/
	for (size_t i = 0; i < length; i++)
	{
		std::string data{};
		if (table.find(datas[i].id, data))
		{
			std::cout << "Студент " << datas[i].id << "найден, данные: " << data << std::endl;
		}
		else
		{
			std::cout << "Студент " << datas[i].id << " не найден" << std::endl;
		}
	}

	return 0;
}