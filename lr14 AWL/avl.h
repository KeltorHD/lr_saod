#pragma once

#include <cstdint>


template<typename T>
class AVL
{
public:
	AVL() : top(nullptr) {}
	~AVL() { this->clear(this->top); };

	void add(const T& value);

private:
	struct node
	{
		T value;
		uint8_t height;
		node* left;
		node* right;

		node(const T& value) :left(nullptr), right(nullptr), value(value), height(1) {}

		uint8_t get_height() { this->height ? this->height : 0; }
		uint8_t bal_factor() { this->left->get_height() - this->right->get_height(); }
		void fix_height() 
		{
			uint8_t hl = this->left->get_height();
			uint8_t hr = this->right->get_height();
			this->height = (hl > hr ? hl : hr) + 1;
		}
	};

	node* top;

	node* rotate_right(node* to_rotate);
	node* rotate_left(node* to_rotate);
	node* balance(node* to_balance);

	void add_r(node*& to_add, const T& value);

	void clear(node* to_delete);
};

template<typename T>
inline void AVL<T>::add(const T& value)
{
	if (!this->top)
	{
		this->top = new node(value);
		return;
	}

	if (value < this->top->value)
	{
		this->add_r(this->top->left, value);
	}
	else
	{
		this->add_r(this->top->right, value);
	}
	this->balance(this->top);
}

template<typename T>
inline AVL<T>::node* AVL<T>::rotate_right(node* to_rotate)
{
	node* q = to_rotate->left;
	to_rotate->left = q->right;
	q->right = to_rotate;
	to_rotate->fix_height();
	to_rotate->fix_height();
	return q;
}

template<typename T>
inline AVL<T>::node* AVL<T>::rotate_left(node* to_rotate)
{
	node* p = to_rotate->right;
	to_rotate->right = p->left;
	p->left = to_rotate;
	to_rotate->fix_height();
	p->fix_height();
	return p;
}

template<typename T>
inline AVL<T>::node* AVL<T>::balance(node* to_balance)
{
	to_balance->fix_height();
	if (to_balance->bal_factor() == 2)
	{
		if (to_balance->right->bal_factor() < 0)
			to_balance->right = this->rotate_right(to_balance->right);
		return this->rotate_left(to_balance);
	}
	if (to_balance->bal_factor() == -2)
	{
		if (to_balance->left->bal_factor() > 0)
			to_balance->left = this->rotate_left(to_balance->left);
		return this->rotate_right(to_balance);
	}
	return to_balance; // балансировка не нужна
}

template<typename T>
inline void AVL<T>::add_r(node*& to_add, const T& value)
{
	if (!to_add)
	{
		to_add = new node(value);
		return;
	}

	if (value < to_add->value)
	{
		this->add_r(to_add->left, value);
	}
	else
	{
		this->add_r(to_add->right, value);
	}
	balance(to_add);
}

template<typename T>
inline void AVL<T>::clear(node* to_delete)
{
	if (to_delete)
	{
		this->clear(to_delete->left);
		this->clear(to_delete->right);
		delete to_delete;
	}
}
