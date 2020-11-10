#include <iostream>
#include <fstream>
#include "tree.h"
#include "tr.h"

int main()
{
	system("chcp 65001>nul");
	
	std::ifstream ifs("data.txt");
	
	Tree tree;
	load(ifs, tree);

	first(ifs, tree);

	return 1;
}