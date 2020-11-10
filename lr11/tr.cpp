#include "tr.h"

void load(std::ifstream& ifs, Tree& tr)
{
	std::string field;
	size_t type;

	while (ifs >> type)
	{
		std::getline(ifs, field);
		tr.add(Tree::node_t(type), field);
	}
}

void first(std::ifstream& ifs, Tree& tr)
{
	std::string field;
	size_t type;

	while (ifs >> type)
	{
		std::getline(ifs, field);
		if (Tree::node_t(type) == Tree::node_t::worker)
		{
			std::cout << "Результат поиска работника " << << tr.find(Tree::node_t(type), field) << std::endl;
		}
	}
}
