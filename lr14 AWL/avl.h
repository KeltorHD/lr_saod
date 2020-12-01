#pragma once

#include <iostream>
#include <cstdint>


template<typename value_t>
class AVL
{
public:
	AVL() : top(nullptr) {}
	~AVL() { this->clear(this->top); };

	void add(const value_t& value);
	void remove(const value_t& value);

	void print(std::ostream& os) const;

private:
	struct node
	{
		value_t value;
		uint8_t height;
		node* left;
		node* right;

		node(const value_t& value) :left(nullptr), right(nullptr), value(value), height(1) {}
	};

	node* top;

	/*работа с node*/
	uint8_t get_height(node* p) { return p ? p->height : 0; }
	uint8_t bal_factor(node* p) { return get_height(p->right) - get_height(p->left); }
	void fix_height(node* p)
	{
		uint8_t hl = get_height(p->left);
		uint8_t hr = get_height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}

	/*операции над node*/
	node* rotate_right(node* to_rotate);
	node* rotate_left(node* to_rotate);
	node* balance(node* to_balance);
	node* findmin(node* p);
	node* removemin(node* p);

	node* add_r(node* to_add, const value_t& value);
	node* remove_r(node* to_remove, const value_t& value);
	void print_r(std::ostream& os, int level, node* to_print) const;

	void clear(node* to_delete);
};

template<typename value_t>
inline void AVL<value_t>::add(const value_t& value)
{
	if (!this->top)
	{
		this->top = new node(value);
		return;
	}

	if (value < this->top->value)
	{
		this->top->left = this->add_r(this->top->left, value);
	}
	else
	{
		this->top->right = this->add_r(this->top->right, value);
	}
	this->top = this->balance(this->top);
}

template<typename value_t>
inline void AVL<value_t>::remove(const value_t& value)
{
	if (this->top)
	{
		if (value < this->top->value)
			this->top->left = remove_r(this->top->left, value);
		else if (value > this->top->value)
			this->top->right = remove_r(this->top->right, value);
		else //  value == top->value
		{
			node* q = this->top->left;
			node* r = this->top->right;
			delete this->top;
			if (!r) 
			{
				this->top = q;
				return;
			}
			node* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			this->top = balance(min);
		}
		this->top = this->balance(this->top);
	}
}

template<typename value_t>
inline void AVL<value_t>::print(std::ostream& os) const
{
	int level{ 0 };
	this->print_r(os, level, this->top);
}

template<typename value_t>
inline typename AVL<value_t>::node* AVL<value_t>::rotate_right(node* to_rotate)
{
	node* q = to_rotate->left;
	to_rotate->left = q->right;
	q->right = to_rotate;
	fix_height(to_rotate);
	fix_height(q);
	return q;
}

template<typename value_t>
inline typename AVL<value_t>::node* AVL<value_t>::rotate_left(node* to_rotate)
{
	node* p = to_rotate->right;
	to_rotate->right = p->left;
	p->left = to_rotate;
	fix_height(to_rotate);
	fix_height(p);
	return p;
}

template<typename value_t>
inline typename AVL<value_t>::node* AVL<value_t>::balance(node* to_balance)
{
	fix_height(to_balance);
	if (bal_factor(to_balance) == 2)
	{
		if (bal_factor(to_balance->right) < 0)
			to_balance->right = this->rotate_right(to_balance->right);
		return this->rotate_left(to_balance);
	}
	if (bal_factor(to_balance) == -2)
	{
		if (bal_factor(to_balance->left) > 0)
			to_balance->left = this->rotate_left(to_balance->left);
		return this->rotate_right(to_balance);
	}
	return to_balance; // балансировка не нужна
}

template<typename value_t>
inline typename AVL<value_t>::node* AVL<value_t>::findmin(node* p)
{
	return p->left ? findmin(p->left) : p;
}

template<typename value_t>
inline typename AVL<value_t>::node* AVL<value_t>::removemin(node* p)
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

template<typename value_t>
inline typename AVL<value_t>::node* AVL<value_t>::add_r(node* to_add, const value_t& value)
{
	if (!to_add)
	{
		to_add = new node(value);
		return to_add;
	}

	if (value < to_add->value)
	{
		to_add->left = this->add_r(to_add->left, value);
	}
	else
	{
		to_add->right = this->add_r(to_add->right, value);
	}
	return balance(to_add);
}

template<typename value_t>
inline typename AVL<value_t>::node* AVL<value_t>::remove_r(node* to_remove, const value_t& value)
{
	if (value < to_remove->value)
		to_remove->left = remove_r(to_remove->left, value);
	else if (value > to_remove->value)
		to_remove->right = remove_r(to_remove->right, value);
	else //  value == to_remove->value
	{
		node* q = to_remove->left;
		node* r = to_remove->right;
		delete to_remove;
		if (!r)
		{
			return q;
		}
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return this->balance(to_remove);
}

template<typename value_t>
inline void AVL<value_t>::print_r(std::ostream& os, int level, node* to_print) const
{
	if (!to_print)
		return;

	int l = level;
	for (size_t i = 0; i < l; i++)
	{
		os << "-";
	}
	os << to_print->value << std::endl;

	l++;

	this->print_r(os, l, to_print->left);
	this->print_r(os, l, to_print->right);
}

template<typename value_t>
inline void AVL<value_t>::clear(node* to_delete)
{
	if (to_delete)
	{
		this->clear(to_delete->left);
		this->clear(to_delete->right);
		delete to_delete;
	}
}
