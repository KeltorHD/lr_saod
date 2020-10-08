#include "deque.h"
#include <iostream>

int main()
{
	system("chcp 65001>nul"); /*utf-8*/

	Deque<int> d;

	std::cout << "Заполнение дэка" << std::endl;
	for (size_t i = 0; i < 10; i++)
	{
		d.pushBack(i);
	}
	std::cout << "Длина дэка: " << d.length() << std::endl;
	
	try
	{
		std::cout << "Верхний элемент: " << d.Front() << std::endl;
		std::cout << "Нижний элемент: " << d.Back() << std::endl;
		std::cout << "Выполнено без ошибок" << std::endl;
	}
	catch (std::out_of_range & e)
	{
		std::cout << e.what() << std::endl;
	}

	for (size_t i = 0; i < 5; i++)
	{
		std::cout << "d.popFront(): " << d.popFront() << std::endl;
	}
	std::cout << "Длина дэка: " << d.length() << std::endl;
	for (size_t i = 0; i < 5; i++)
	{
		std::cout << "d.popBack(): " << d.popBack() << std::endl;
	}
	std::cout << "Длина дэка: " << d.length() << std::endl;

	try
	{
		std::cout << "Нижний элемент: " << d.popBack() << std::endl;
	}
	catch (std::out_of_range & e)
	{
		std::cout << "Ошибка: " << e.what() << std::endl;
	}
	std::cout << "Длина дэка: " << d.length() << std::endl;

	std::cout << "DONE." << std::endl;

	return bool(std::cout);
}