#include <iostream>
#include <fstream>
#include "avl.h"

struct data
{
	int id;
	char field;

};

std::ostream& operator<<(std::ostream& os, const data& d)
{
	os << d.id << " " << d.field;
	return os;
}

bool operator<(const data& d1, const data& d2)
{
	return d1.id < d2.id;
}

bool operator>(const data& d1, const data& d2)
{
	return d1.id > d2.id;
}

int main()
{
	system("chcp 65001>nul");

	AVL<data> tree;

	std::ifstream ifs("data.txt");

	int id{};
	char field{};
	size_t length{};
	while (ifs >> id >> field)
	{
		tree.add({ id, field });
		length++;
	}
	ifs.close();

	tree.print(std::cout);
	std::cout << std::endl;

	/*tree.remove({ 190,'f' });
	tree.print(std::cout);
	std::cout << std::endl;*/

	for (size_t i = 0; i < length; i++)
	{
		tree.remove({ int(i),'f' });
		tree.print(std::cout);
		std::cout << std::endl;
	}

	return bool(std::cout);
}