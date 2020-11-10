#include "tree.h"

Tree::Tree()
{
	this->head = new node("head");
}

Tree::~Tree()
{
	this->clear(this->head);
}

void Tree::add(node_t type, std::string field)
{
	switch (type)	
	{
	case Tree::node_t::body:
		this->head->next.push_back(new node(field));
		break;
	default:
		try
		{
			node* sw{ this->head };
			for (size_t i = 0; i < size_t(type); i++)
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
}

bool Tree::find(const std::string& field) const
{
	bool isFind{ false };
	for (size_t i = 0; i < this->head->next.size(); i++)
	{
		isFind = this->find(field, this->head->next[i]);
		if (isFind)
			return true;
	}
	return false;
}

size_t Tree::count_element(const std::string& field) const
{
	size_t count{};
	for (size_t i = 0; i < this->head->next.size(); i++)
	{
		count += this->count_element(field, this->head->next[i]);
	}
	return count;
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

bool Tree::find(const std::string& field, node* in_find) const
{
	if (in_find->field == field)
	{
		return true;
	}
	else
	{
		bool isFind{ false };
		for (size_t i = 0; i < in_find->next.size(); i++)
		{
			isFind = this->find(field, in_find->next[i]);
			if (isFind)
				return true;
		}
		return false;
	}
}

size_t Tree::count_element(const std::string& field, node* in_count) const
{
	size_t count{};
	if (in_count->field == field)
		count++;

	for (size_t i = 0; i < in_count->next.size(); i++)
	{
		count += this->count_element(field, in_count->next[i]);
	}
	return count;
}
