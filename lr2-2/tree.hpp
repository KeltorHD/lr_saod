#pragma once

#include <iostream>

template<typename key, typename data>
class Bin_tree
{
public:
	Bin_tree() = default;
	~Bin_tree() = default;

	void insert(const key& k, const data& d)
	{
		if (!this->root)
		{
			this->root = std::make_shared<node>();
			this->root->k = k;
			this->root->d = d;
		}
		else
		{
			this->insert(this->root, k, d);
		}
	}
	void print(std::ostream& os) const
	{
		std::cout << "Дерево:" << std::endl;

		size_t level{ 0 };
		if (this->root)
		{
			this->print(2, os, this->root, level);
		}

		std::cout << std::endl;
	}

private:
	struct node;
	using ptr_t = std::shared_ptr<node>;

	struct node
	{
		key k;
		data d;
		ptr_t left{ nullptr };
		ptr_t right{ nullptr };
	};

	ptr_t root;

	void insert(ptr_t to_insert, const key& k, const data& d)
	{
		if (to_insert->k > k)
		{
			if (to_insert->left)
			{
				this->insert(to_insert->left, k, d);
			}
			else
			{
				to_insert->left = std::make_shared<node>();
				to_insert->left->k = k;
				to_insert->left->d = d;
			}
		}
		else if (to_insert->k < k)
		{
			if (to_insert->right)
			{
				this->insert(to_insert->right, k, d);
			}
			else
			{
				to_insert->right = std::make_shared<node>();
				to_insert->right->k = k;
				to_insert->right->d = d;
			}
		}
	}
	void print(size_t rln, std::ostream& os, ptr_t to_print, size_t& level) const
	{
		for (size_t l = 0; l < level; l++)
		{
			std::cout << "    ";
		}
		std::cout << (rln <2 ? (rln == 0 ? "Левый у" : "Правый у")  : "У") << "зел " << to_print << " Данные в узле: " << to_print->k << ", " << to_print->d << std::endl;

		level++;
		if (to_print->left)
		{
			this->print(0, os, to_print->left, level);
		}
		if (to_print->right)
		{
			this->print(1, os, to_print->right, level);
		}
		level--;
	}
};