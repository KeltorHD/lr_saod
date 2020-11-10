#include "tr.h"

std::vector<std::string> load(Tree& tr)
{
	std::ifstream ifs("data.txt");
	std::vector<std::string> v;

	std::string field;
	size_t type;

	while (ifs >> type)
	{
		std::getline(ifs, field);
		tr.add(Tree::node_t(type), field);
		if (Tree::node_t(type) == Tree::node_t::worker)
			v.push_back(field);
	}
	ifs.close();
	return v;
}

void first(const Tree& tr, const std::vector<std::string>& v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << "Результат поиска работника " << v[i] << ": " << tr.find(v[i]) << std::endl;
	}
}

void second(const Tree& tr, const std::vector<std::string>& v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << "Количество включений в дерево работника " << v[i] << ": " << tr.count_element(v[i]) << std::endl;
	}
}
