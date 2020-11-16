#include <iostream>
#include <fstream>
#include "tree.h"

int main()
{
	system("chcp 65001>nul");

	Tree tr;

	std::ifstream ifs("data.txt");

	std::string field;
	size_t depth;

	while (ifs >> depth)
	{
		std::getline(ifs, field);
		field.erase(field.begin());
		tr.add(depth, field);
	}
	ifs.close();

	tr.find_print("Кисло-молочное");

	return bool(std::cout);
}