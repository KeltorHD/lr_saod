#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "binaryTree.h"

int main()
{
	system("chcp 1251>nul");

	std::ofstream ofs("data.txt");
	std::vector<int> v;
	while (v.size() < 256)
	{
		int tmp{ rand() % 256 };
		if (std::find(v.begin(), v.end(), tmp) == v.end())
		{
			v.push_back(tmp);
			ofs << tmp << " " << (tmp % 2 == 0 ? "a" : "b") << std::endl;
		}
	}
	ofs.close();

	int id;
	std::string str;
	std::ifstream ifs("data.txt");
	BinaryTree<data_t> binTree;
	size_t length{};
	while (ifs >> id >> str)
	{
		binTree.add({ id, str });
		length++;
	}
	ifs.close();

	binTree.print(std::cout);
	std::cout << std::endl;

	for (size_t i = 0; i < 2 * length; i++)
	{
		data_t d{ rand() % 256, "" };
		binTree.find_inc(d);
	}

	binTree.print(std::cout);
	std::cout << std::endl;

	binTree.rebuild();

	binTree.print(std::cout);
	std::cout << std::endl;

	return bool(std::cout);
}