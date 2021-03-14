#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	system("chcp 1251>nul");
	std::vector<int> mas;
	const size_t length{ 500 };

	for (size_t i = 0; i < length; i++)
	{
		mas.push_back(rand() % 100);
	}
	std::sort(mas.begin(), mas.end());

	{
		bool find_done{ false };
		size_t left{ 0 }, rigth{ length - 1 }, mid{};
		size_t count{};

		int key{ 50 };

		while (left <= rigth && !find_done)
		{
			mid = (left + rigth) / 2; /*середина*/
			if (mas[mid] == key) find_done = true;
			else if (mas[mid] > key) rigth = mid - 1;
			else left = mid + 1;
			count++;
		}

		if (find_done)
			std::cout << "Найден: " << key << " " << count << std::endl;
		else
			std::cout << "Не найден" << std::endl;
	}

	{
		size_t current{}, left{}, right{ length - 1 }, mid{};
		int key{ 50 };
		bool find_done{ false };
		size_t count{};

		while (left <= right && !find_done)
		{
			mid = left + ((key - mas[left]) * (right - left)) / (mas[right] - mas[left]);
			if (mas[mid] < key) left = mid + 1;
			else if (mas[mid] > key) right = mid - 1;
			else find_done = true;
			count++;
		}
			if (find_done)
				std::cout << "Найден: " << key << " " << count << std::endl;
			else
				std::cout << "Не найден" << std::endl;
	}
}