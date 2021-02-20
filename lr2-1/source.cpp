#include <iostream>

constexpr int length = 100;

void rand_input(std::pair<int, int>* mas, int length)
{
	for (size_t i = 0; i < length; i++)
	{
		mas[i].first = rand() % 10;
		mas[i].second = rand() % 100 + 1;
	}
}

void print(std::pair<int, int>* mas, int length)
{
	for (size_t i = 0; i < length; i++)
	{
		std::cout << mas[i].first << "(" << mas[i].second << ")" << std::endl;
	}
}

void sort_insertions(std::pair<int, int>* mas, int length)
{
	for (int i = 1; i < length; i++)
		for (int j = i; j > 0 && mas[j - 1].first >= mas[j].first; j--)
			if (mas[j - 1].first == mas[j].first)
				if (mas[j - 1].second > mas[j].second)
					std::swap(mas[j - 1], mas[j]);
				else break;
			else
				std::swap(mas[j - 1], mas[j]);
}

int main()
{
	std::pair<int, int> mas[length];

	/*input*/
	rand_input(mas, length);

	/*sort*/
	sort_insertions(mas, length);

	/*print*/
	print(mas, length);

	return bool(std::cout);
}