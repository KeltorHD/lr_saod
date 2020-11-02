#pragma once

template <typename T>
class Queue
{
public:
	Queue();
	~Queue();

	/*methods*/
	void push(const T& data);
	bool pop(T& data);
	size_t length() const;
	static size_t bite_per_element();

private:
	Queue(const Queue& q) = delete;
	Queue(Queue&& q) = delete;

	const Queue& operator=(const Queue& q) = delete;
	const Queue& operator=(Queue&& q) = delete;

	struct node
	{
		node* child;
		T data;

		node(T _data)
		{
			data = _data;
			child = nullptr;
		}
		node(T _data, node* _child)
		{
			data = _data;
			child = _child;
		}
	};

	node* top;
	node* end;
	size_t len;

};

template<typename T>
inline Queue<T>::Queue()
{
	this->top = this->end = nullptr;
	this->len = 0;
}

template<typename T>
inline Queue<T>::~Queue()
{
	node* tmp;
	while (this->top != nullptr)
	{
		tmp = this->top;
		this->top = this->top->child;
		delete tmp;
	}
}

template<typename T>
inline void Queue<T>::push(const T& data)
{
	node* tmp = new node(data);
	this->len++;

	if (!this->top) /*первый элемент*/
	{
		this->top = tmp;
		this->end = this->top;
	}
	else
	{
		this->end->child = tmp;
	}
	this->end = tmp;
}

template<typename T>
inline bool Queue<T>::pop(T& data)
{
	if (!this->top)
	{
		return false;
	}
	else
	{
		data = this->top->data;
		this->len--;
		node* tmp = this->top;
		this->top = this->top->child;
		delete tmp;

		if (this->len == 0)
			this->end = nullptr;

		return true;
	}
}

template<typename T>
inline size_t Queue<T>::bite_per_element()
{
	return sizeof(T) + sizeof(node*);
}

template<typename T>
inline size_t Queue<T>::length() const
{
	return this->len;
}