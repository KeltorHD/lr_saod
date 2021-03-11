#pragma once

#include "tree.hpp"

#include <iostream>
#include <string>
#include <vector>

int main()
{
	system("chcp 1251>nul");
	Bin_tree<int, std::string> tree;

	std::vector<int> keys{ 8,3,1,6,4,10,14,7,13 };

	for (auto& i : keys)
	{
		tree.insert(i, "<очень нужные данные>");
	}

	tree.print(std::cout);

	return 0;
}