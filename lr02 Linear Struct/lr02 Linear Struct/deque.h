#pragma once
#include <stdexcept>

template <class item>
class Deque
{
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


public:
	/*konstr*/
	Deque() = default;
	Deque(const Deque&);
	Deque(Deque&&);
	~Deque() { this->clear(); };
	
	/*destr*/
	Deque& operator=(const Deque&);
	Deque& operator=(Deque&&);

	/*methods*/
	void pushFront(item value) throw();
	void pushBack(item value) throw();

	item popFront() throw();
	item popBack() throw();

	item Front() throw();
	item Back() throw();

	void clear() noexcept;
	size_t length() noexcept;
};

template<class item>
inline Deque<item>::Deque(const Deque& d)
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
inline Deque<item>::Deque(Deque&& d)
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
inline Deque<item>& Deque<item>::operator=(const Deque& d)
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
inline Deque<item>& Deque<item>::operator=(Deque&& d)
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
inline void Deque<item>::pushFront(item value)
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
inline void Deque<item>::pushBack(item value)
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
inline item Deque<item>::popFront()
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
		throw std::out_of_range("Нет элементов в ДЭКЕ");
	}
}

template<class item>
inline item Deque<item>::popBack() throw()
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
		throw std::out_of_range("Нет элементов в ДЭКЕ");
	}
}

template<class item>
inline item Deque<item>::Front()
{
	if (this->head)
		return this->head->field;
	else
		throw std::out_of_range("Нет элементов в ДЭКЕ");
}

template<class item>
inline item Deque<item>::Back() throw()
{
	if (this->tail)
		return this->tail->field;
	else
		throw std::out_of_range("Нет элементов в ДЭКЕ");
}

template<class item>
inline void Deque<item>::clear() noexcept
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
inline size_t Deque<item>::length() noexcept
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