#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

void display(int* mas, int length);

void input(int* mas, int length);
void inputRand(int* mas, int length);
void inputHand(int* mas, int length);
void inputFile(int* mas, int length, const std::string& file);

int main()
{
	/*
	Дана последовательность целых положительных чисел.
	Каждое число может принимать значение от 100 до 10e9. 
	Необходимо посчитать, сколько чисел в данной последовательности имеют уникальные две последние цифры
	*/
	system("chcp 65001>nul");
	srand(time(0));

	int length{0};
	int* mas{ nullptr };
	int masRemainder[100]{ 0 };

	/*Ввод кол-ва элементов*/
	std::cout << "Введите кол-во элементов: ";
	while (length <= 0)
	{
		std::cin >> length;
		if (length <= 0)
		{
			std::cout << "Ошибка, число неположительно, введите еще раз: ";
		}
	}
	mas = new int[length];

	/*заполнение*/
	input(mas, length);
	int isDisplay{ -1 };
	std::cout << "Выводить массив? (1-да, 0 - нет) ";
	while (isDisplay < 0 || isDisplay > 1)
	{
		std::cin >> isDisplay;
		if (isDisplay < 1 || isDisplay > 2)
		{
			std::cout << "Ошибка, введите еще раз: ";
		}
	}
	if (isDisplay) { display(mas, length); std::cout << std::endl; };

	/*выполнение алгоритма*/
	int countUnique{ 0 };
	for (int i = 0; i < length; i++)
	{
		masRemainder[mas[i] % 100]++;
	}
	for (int i = 0; i < 100; i++)
	{
		if (masRemainder[i] == 1)
			countUnique++;
	}
	std::cout << "Количество чисел, имеющих уникальные две последние цифры: " << countUnique << std::endl;

	delete[] mas;

	return 0;
}

void display(int* mas, int length)
{
	std::cout << "{ ";
	for (int i = 0; i < length; i++)
	{
		if (i != (length - 1))
			std::cout << mas[i] << ", ";
		else
			std::cout << mas[i] << " }";
	}
}

void input(int* mas, int length)
{
	int sw{ -1 };
	std::string file;

	while (sw <= 0 || sw >= 4)
	{
		std::cout << "Как заполнить массив? (1 - с клавиатуры, 2 - из файла, 3 - рандомно в диапазоне): ";
		std::cin >> sw;
		switch (sw)
		{
		case 1:
			inputHand(mas, length);
			break;
		case 2:
			std::cout << "Введите название файла вместе с расширением: ";
			std::cin >> file;
			inputFile(mas, length, file);
			break;
		case 3:
			inputRand(mas, length);
			break;
		}
	}
}

void inputRand(int* mas, int length)
{
	for (int i = 0; i < length; i++)
	{
		mas[i] = rand() % (100'000'0000 - 100 + 1) + 100;
	}
}

void inputHand(int* mas, int length)
{
	for (int i = 0; i < length; i++)
	{
		std::cout << "Элемент " << i << ": ";
		std::cin >> mas[i];
	}
}

void inputFile(int* mas, int length, const std::string& file)
{
	std::ifstream fin;
	fin.open(file);
	bool isError{ false };

	if (fin.is_open())
	{
		for (int i = 0; i < length; i++)
		{
			if (!(fin >> mas[i]))
			{
				isError = true;
				std::cout << "Ошибка при вводе, ввод из консоли. " << std::endl;
				break;
			}
		}
	}
	else
	{
		std::cout << "Не удается открыть файл, ввод из консоли. " << std::endl;
		isError = true;
	}

	fin.close();

	if (isError)
	{
		inputHand(mas, length);
	}
}