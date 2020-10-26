#pragma once
#include <stdexcept>
#include <initializer_list>

template <class item>
class List
{
public:
	/*konstr*/
	List() = default;
	List(const std::initializer_list<item>& list);
	List(const List&);
	List(List&&);
	~List() { this->clear(); };

	/*destr*/
	List& operator=(const List&);
	List& operator=(List&&);

	/*methods*/
	void pushFront(item value) throw();
	void pushBack(item value) throw();

	item popFront() throw();
	item popBack() throw();

	void clear() noexcept;
	size_t length() const noexcept;
	bool find(const item& value) const noexcept;

	item& operator[](size_t pos) throw();
	const item& operator[](size_t pos) const throw();

private:
	struct node
	{
		node* next;
		item field;
		node() { next = nullptr; };
		node(item value) { next = nullptr; field = value; }
		node(node* next, item value) { next = next; field = value; };
	};

	node* head = nullptr;
	node* tail = nullptr;

};

template<class item>
inline List<item>::List(const std::initializer_list<item>& list)
{
	for (auto& element : list)
	{
		this->pushBack(element);
	}
}

template<class item>
inline List<item>::List(const List& d)
{
	if (d.head)
	{
		this->head = new node(d.head->field);
		node* tmp_d = d.head;
		node* tmp_t = this->head;
		while (tmp_d != d.tail)
		{
			tmp_t->next = new node(tmp_d->next->field);
			tmp_t = tmp_t->next;
			tmp_d = tmp_d->next;
		}

		if (d.head == d.tail)
			this->tail = this->head;
		else
			this->tail = tmp_t;
	}
}

template<class item>
inline List<item>::List(List&& d)
{
	if (d.head)
	{
		this->head = new node(d.head->field);
		node* tmp_d = d.head;
		node* tmp_t = this->head;
		while (tmp_d != d.tail)
		{
			tmp_t->next = new node(tmp_d->next->field);
			tmp_t = tmp_t->next;
			tmp_d = tmp_d->next;
		}

		if (d.head == d.tail)
			this->tail = this->head;
		else
			this->tail = tmp_t;

		d.clear();
	}
}

template<class item>
inline List<item>& List<item>::operator=(const List& d)
{
	if (&d == this)
		return *this;

	this->clear();

	if (d.head)
	{
		this->head = new node(d.head->field);
		node* tmp_d = d.head;
		node* tmp_t = this->head;
		while (tmp_d != d.tail)
		{
			tmp_t->next = new node(tmp_d->next->field);
			tmp_t = tmp_t->next;
			tmp_d = tmp_d->next;
		}

		if (d.head == d.tail)
			this->tail = this->head;
		else
			this->tail = tmp_t;
	}
	else
	{
		this->head = nullptr;
		this->tail = nullptr;
	}
}

template<class item>
inline List<item>& List<item>::operator=(List&& d)
{
	if (&d == this)
		return *this;

	this->clear();
	this->clear();

	if (d.head)
	{
		this->head = new node(d.head->field);
		node* tmp_d = d.head;
		node* tmp_t = this->head;
		while (tmp_d != d.tail)
		{
			tmp_t->next = new node(tmp_d->next->field);
			tmp_t = tmp_t->next;
			tmp_d = tmp_d->next;
		}

		if (d.head == d.tail)
			this->tail = this->head;
		else
			this->tail = tmp_t;

		d.clear();
	}
	else
	{
		this->head = nullptr;
		this->tail = nullptr;
	}
}

template<class item>
inline void List<item>::pushFront(item value)
{
	if (!this->head)
	{
		this->head = new node(value);
		this->tail = this->head;
	}
	else
	{
		node* tmp = this->head;
		this->head = new node(tmp, value);
	}
}

template<class item>
inline void List<item>::pushBack(item value)
{
	if (!this->head)
	{
		this->head = new node(value);
		this->tail = this->head;
	}
	else
	{
		node* tmp = new node(value);
		this->tail->next = tmp;
		this->tail = tmp;
	}
}

template<class item>
inline item List<item>::popFront()
{
	if (this->head)
	{
		if (this->head != this->tail)
		{
			item tmp = this->head->field;
			node* tmp_next = this->head->next;
			delete this->head;
			this->head = tmp_next;
			return tmp;
		}
		else
		{
			item tmp = this->head->field;
			delete this->head;
			this->head = nullptr;
			this->tail = nullptr;
			return tmp;
		}
	}
	else
	{
		throw std::out_of_range("Нет элементов в СПИСКЕ");
	}
}

template<class item>
inline item List<item>::popBack() throw()
{
	if (this->head)
	{
		if (this->head != this->tail)
		{
			node* tmp = this->head;
			while (tmp->next != this->tail) { tmp = tmp->next; }
			item value = this->tail->field;
			delete this->tail;
			this->tail = tmp;
			this->tail->next = nullptr;
			return value;
		}
		else
		{
			item tmp = this->head->field;
			delete this->head;
			this->head = nullptr;
			this->tail = nullptr;
			return tmp;
		}
	}
	else
	{
		throw std::out_of_range("Нет элементов в СПИСКЕ");
	}
}

template<class item>
inline void List<item>::clear() noexcept
{
	if (this->head)
	{
		if (this->head != this->tail)
		{
			while (this->head != this->tail)
			{
				node* tmp = this->head->next;
				delete this->head;
				this->head = tmp;
			}
			delete this->head;
			this->head = nullptr;
			this->tail = nullptr;
		}
		else
		{
			delete this->head;
			this->head = nullptr;
			this->tail = nullptr;
		}
	}
}

template<class item>
inline size_t List<item>::length() const noexcept
{
	if (this->head)
	{
		size_t counter{ 1 };
		node* tmp = this->head;
		while (tmp != this->tail)
		{
			counter++;
			tmp = tmp->next;
		}
		return counter;
	}

	return 0;
}

template<class item>
inline bool List<item>::find(const item& value) const noexcept
{
	size_t l = this->length();
	node* tmp = this->head;
	if (l == 0) return false;

	for (size_t i = 0; i < l; i++)
	{
		if (tmp->field == value)
			return true;
	}
	return false;
}

template<class item>
inline item& List<item>::operator[](size_t pos) throw()
{
	if (pos >= this->length() || !this->head)
		throw std::out_of_range("Обращение к несуществующему элементу СПИСКА || длина СПИСКА равна нулю");

	node* tmp = this->head;
	for (size_t i = 0; i < pos; i++)
	{
		tmp = tmp->next;
	}
	return tmp->field;
}

template<class item>
inline const item& List<item>::operator[](size_t pos) const throw()
{
	if (pos >= this->length() || !this->head)
		throw std::out_of_range("Обращение к несуществующему элементу СПИСКА || длина СПИСКА равна нулю");

	node* tmp = this->head;
	for (size_t i = 0; i < pos; i++)
	{
		tmp = tmp->next;
	}
	return tmp->field;
}
