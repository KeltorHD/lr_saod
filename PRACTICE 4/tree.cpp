#include "tree.h"

Tree::Tree()
{
	this->head = new node("head");
}

Tree::~Tree()
{
	this->clear(this->head);
}

void Tree::add(size_t depth, std::string field)
{
	try
	{
		node* sw{ this->head };
		for (size_t i = 0; i < depth; i++)
		{
			sw = sw->next[sw->next.size() - 1];
		}
		sw->next.push_back(new node(field));
	}
	catch (...)
	{
		std::cout << "nullptr" << std::endl;
	}
}

void Tree::find_print(const std::string& field) const
{
	for (size_t i = 0; i < this->head->next.size(); i++)
	{
		this->find_print(field, this->head->next[i]);
	}
}

void Tree::clear(node* to_delete)
{
	if (to_delete)
	{
		for (size_t i = 0; i < to_delete->next.size(); i++)
		{
			this->clear(to_delete->next[i]);
		}
		delete to_delete;
	}
}

void Tree::find_print(const std::string& field, node* in_find) const
{
	if (in_find->field == field)
	{
		std::cout << "Элементы: " << std::endl;
		for (size_t i = 0; i < in_find->next.size(); i++)
		{
			std::cout << i + 1 << ": " << in_find->next[i]->field << std::endl;
		}
	}
	else
	{
		for (size_t i = 0; i < in_find->next.size(); i++)
		{
			this->find_print(field, in_find->next[i]);
		}
	}
}