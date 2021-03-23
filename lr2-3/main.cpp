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

	size_t length{ 5 }; /*���������� ��������� � �������*/
	
	/*��������� ������ �� ����� � ���������� �� � �������*/
	for (size_t i = 0; i < length; i++)
	{
		info tmp;
		std::getline(file, tmp.id);
		std::getline(file, tmp.data);
		
		datas.push_back(tmp);
		table.insert(tmp.id, tmp.data);
	}

	/*����� ������ � �������� �� �������*/
	for (size_t i = 0; i < length; i++)
	{
		std::string data{};
		if (table.find(datas[i].id, data))
		{
			std::cout << "������� " << datas[i].id << " ������, ������: " << data << std::endl;
		}
		else
		{
			std::cout << "������� " << datas[i].id << " �� ������" << std::endl;
		}
	}

	/*����� ��������, �������� ��� � �������*/
	std::string data{};
	if (table.find("�����", data))
	{
		std::cout << "������� " << "�����" << " ������, ������: " << data << std::endl;
	}
	else
	{
		std::cout << "������� " << "�����" << " �� ������" << std::endl;
	}

	return 0;
}