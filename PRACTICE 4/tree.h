#pragma once

#include <vector>
#include <string>
#include <iostream>

class Tree
{
public:
	Tree();
	~Tree();

	void add(size_t depth, std::string field);
	void find_print(const std::string& field) const;

private:
	struct node
	{
		std::string field;
		std::vector<node*> next;

		node(std::string field_)
		{
			field = field_;
		}
	};
	node* head;

	void clear(node* to_delete);
	void find_print(const std::string& field, node* in_find) const;
};