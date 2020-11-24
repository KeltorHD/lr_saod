#pragma once

#include <iostream>

struct data_t
{
	int id;
	std::string data;

	bool operator==(const data_t& d) const
	{
		return this->id == d.id;
	}
	bool operator<(const data_t& d) const
	{
		return this->id < d.id;
	}
	friend std::ostream& operator<<(std::ostream& os, const data_t& d)
	{
		os << "id: " << d.id << ", data: " << d.data;
		return os;
	}
};

template <typename T_field>
class BinaryTree
{
public:
	BinaryTree() = default;
	~BinaryTree();

	BinaryTree(const BinaryTree&) = delete;
	BinaryTree& operator=(const BinaryTree&) = delete;

	void add(const T_field& field, const size_t& count_find = 0);                     /*добавление элемента в дерево*/
	/*поиск производится с помощью перегрузки ==, < для типа T_field*/
	const T_field& find(const T_field& field) const;    /*поиск элемента без икремента количества обращений*/
	const T_field& find_inc(const T_field& field);      /*поиск элемента с инкрементом количества обращения*/

	void print(std::ostream& os) const;                 /*печатаем дерево вместе с количеством обращений к элементам*/

	void rebuild();                                     /*перестроить дерево в соответствии с количеством обращений к элементам*/

private:
	struct node
	{
		T_field field;
		size_t count_find;
		node* left;
		node* right;

		node(const T_field& field, const size_t& count_find = 0)
			:field(field), count_find(count_find), left(nullptr), right(nullptr) {};
	};

	bool isRebuid = false;
	node* top = nullptr;

	void clear(node* to_delete);
	void add_r(const T_field& field, node*& to_add, const size_t& count_find = 0);
	void print_r(std::ostream& os, int level, const node* to_print) const;
	const T_field& find_inc_r(const T_field& field, node* to_find);
	const T_field& find_r(const T_field& field, node* to_find) const;
	void detour(node* to_detour, std::vector<node*>& nodes);
};

template<typename T_field>
inline BinaryTree<T_field>::~BinaryTree()
{
	this->clear(this->top);
}

template<typename T_field>
inline void BinaryTree<T_field>::add(const T_field& field, const size_t& count_find)
{
	if (this->isRebuid)
		throw "невозможно изменить дерево!";

	if (!this->top) /*если нет элементов*/
	{
		this->top = new node(field, count_find);
	}
	else
	{
		this->add_r(field, (field < this->top->field) ? this->top->left : this->top->right, count_find);
	}
}

template<typename T_field>
inline const T_field& BinaryTree<T_field>::find(const T_field& field) const
{
	if (this->top)
	{
		if (this->top->field == field)
		{
			return this->top->field;
		}
		else
		{
			if (field < this->top->field)
			{
				return this->find_r(field, this->top->left);
			}
			else
			{
				return this->find_r(field, this->top->right);
			}
		}
	}

	return T_field();
}

template<typename T_field>
inline const T_field& BinaryTree<T_field>::find_inc(const T_field& field)
{
	if (this->top)
	{
		if (this->top->field == field)
		{
			this->top->count_find++;
			return this->top->field;
		}
		else
		{
			if (field < this->top->field)
			{
				return this->find_inc_r(field, this->top->left);
			}
			else
			{
				return this->find_inc_r(field, this->top->right);
			}
		}
	}

	return T_field();
}

template<typename T_field>
inline void BinaryTree<T_field>::print(std::ostream& os) const
{
	int level{ 0 };
	this->print_r(os, level, this->top);
}

template<typename T_field>
inline void BinaryTree<T_field>::rebuild()
{
	std::vector<node*> nodes;
	if (this->top)
	{
		node* tmp = new node(*this->top);
		tmp->left = nullptr;
		tmp->right = nullptr;
		tmp->count_find = this->top->count_find;
		nodes.push_back(tmp);
		this->detour(this->top->left, nodes);
		this->detour(this->top->right, nodes);
	}

	auto f{ [](node* t1, node* t2)
		{
			return t1->count_find < t2->count_find;
		} };
	this->clear(this->top);
	this->top = nullptr;

	while (nodes.size())
	{
		auto max{ std::max_element(nodes.begin(), nodes.end(), f) };
		this->add((*max)->field, (*max)->count_find);
		nodes.erase(max);
	}
}

template<typename T_field>
inline void BinaryTree<T_field>::clear(node* to_delete)
{
	if (to_delete)
	{
		this->clear(to_delete->left);
		this->clear(to_delete->right);
		delete to_delete;
	}
}

template<typename T_field>
inline void BinaryTree<T_field>::add_r(const T_field& field, node*& to_add, const size_t& count_find)
{
	if (!to_add)
	{
		to_add = new node(field, count_find);
	}
	else
	{
		this->add_r(field, (field < to_add->field) ? to_add->left : to_add->right, count_find);
	}
}

template<typename T_field>
inline void BinaryTree<T_field>::print_r(std::ostream& os, int level, const node* to_print) const
{
	if (!to_print)
		return;

	int l = level;
	for (size_t i = 0; i < l; i++)
	{
		os << "-";
	}
	os << to_print->field << ", count_find: " << to_print->count_find << std::endl;

	l++;

	this->print_r(os, l, to_print->left);
	this->print_r(os, l, to_print->right);
}

template<typename T_field>
inline const T_field& BinaryTree<T_field>::find_inc_r(const T_field& field, node* to_find)
{
	if (to_find)
	{
		if (to_find->field == field)
		{
			to_find->count_find++;
			return to_find->field;
		}
		else
		{
			if (field < to_find->field)
			{
				return this->find_inc_r(field, to_find->left);
			}
			else
			{
				return this->find_inc_r(field, to_find->right);
			}
		}
	}
	return T_field();
}

template<typename T_field>
inline const T_field& BinaryTree<T_field>::find_r(const T_field& field, node* to_find) const
{
	if (to_find)
	{
		if (to_find->field == field)
		{
			return to_find->field;
		}
		else
		{
			if (field < to_find->field)
			{
				return this->find_r(field, to_find->left);
			}
			else
			{
				return this->find_r(field, to_find->right);
			}
		}
	}
	return T_field();
}

template<typename T_field>
inline void BinaryTree<T_field>::detour(node* to_detour, std::vector<node*>& nodes)
{
	if (to_detour)
	{
		node* tmp = new node(*to_detour);
		tmp->left = nullptr;
		tmp->right = nullptr;
		tmp->count_find = to_detour->count_find;
		nodes.push_back(tmp);
		this->detour(to_detour->left, nodes);
		this->detour(to_detour->right, nodes);
	}
}
