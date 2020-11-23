#include <iostream>
#include <string>
#include "binaryTree.h"

//struct data_t
//{
//	int id;
//	std::string data;
//
//	bool operator==(const data_t& d)
//	{
//		return this->id == d.id;
//	}
//};


int main()
{
	system("chcp 65001>nul");

	BinaryTree<data_t> binTree;

	binTree.add({ 1, "HELLO" });
	binTree.add({ -1, "HELL" });
	binTree.add({ 2, "ELLO" });

	binTree.print(std::cout);

	return bool(std::cout);
}