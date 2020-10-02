#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

struct Item
{
	std::string name;
	int price;
};

void inputFile(std::vector<Item>& items);

int main()
{
	std::vector<Item> items;
	inputFile(items);

	std::sort(items.begin(), items.end(), [](Item& i1, Item& i2)
		->bool
		{
			return i1.price < i2.price;
		}
	);

	int j{};
	int pred_price = items[0].price;
	std::cout << items[0].name << "\t" << items[0].price << "\t" << 0 << std::endl;
	for (size_t i = 1; i < items.size(); i++)
	{
		if (items[i].price > pred_price)
			j++;

		std::cout << items[i].name << "\t" << items[i].price << "\t" << j << std::endl;

		pred_price = items[i].price;
	}

	return 1;
}

void inputFile(std::vector<Item>& items)
{
	std::ifstream fin;
	fin.open("data.dt");
	int length{};

	if (fin.is_open())
	{
		fin >> length;
		for (int i = 0; i < length; i++)
		{
			std::string name;
			int price;
			fin >> name;
			fin >> price;
			items.push_back({ name, price });
		}
	}
	fin.close();
}
