#pragma once

#include <vector>
#include <string>
#include <iostream>

class Tree
{
public:
	Tree();
	~Tree();

	enum class node_t
	{
		body,       /*корпус*/
		department, /*департамент*/
		kab,        /*кабинет*/
		worker,     /*работники*/
		count
	};
	void add(node_t type, std::string field);
	bool find(const node_t& type, const std::string& field) const;

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
	bool find(const node_t& type, const std::string& field, node* in_find) const;
};