#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "tree.h"
#include "tr.h"

int main()
{
	system("chcp 65001>nul");
	
	Tree tree;
	auto v = load(tree);

	std::sort(v.begin(), v.end());
	v.erase(std::unique(v.begin(), v.end()), v.end());

	first(tree, v);

	std::cout << std::endl;

	second(tree, v);

	return 1;
}