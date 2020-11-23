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

	void add(const T_field& field);                     /*добавление элемента в дерево*/
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

		node(const T_field& field)
			:field(field), count_find(0), left(nullptr), right(nullptr) {};
	};

	bool isRebuid = false;
	node* top = nullptr;

	void clear(node* to_delete);
	void add_r(const T_field& field, node*& to_add);
	void print_r(std::ostream& os, int level, const node* to_print) const;
};

template<typename T_field>
inline BinaryTree<T_field>::~BinaryTree()
{
	this->clear(this->top);
}

template<typename T_field>
inline void BinaryTree<T_field>::add(const T_field& field)
{
	if (this->isRebuid)
		throw "невозможно изменить дерево!";

	if (!this->top) /*если нет элементов*/
	{
		this->top = new node(field);
	}
	else
	{
		this->add_r(field, (field < this->top->field) ? this->top->left : this->top->right);
	}
}

template<typename T_field>
inline void BinaryTree<T_field>::print(std::ostream& os) const
{
	int level{ 0 };
	this->print_r(os, level, this->top);
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
inline void BinaryTree<T_field>::add_r(const T_field& field, node*& to_add)
{
	if (!to_add)
	{
		to_add = new node(field);
	}
	else
	{
		this->add_r(field, (field < to_add->field) ? to_add->left : to_add->right);
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
