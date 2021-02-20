#include <iostream>
#include <algorithm>

int main()
{
	srand(time(NULL));
	const int length{ 100 };
	int mas[length];
	int arr[length];

	int compare1{ 0 };
	int swap1{ 0 };
	int compare2{ 0 };
	int swap2{ 0 };

	for (size_t i = 0; i < length; i++)
	{
		arr[i] = mas[i] = rand() % 100;
	}

	/*bubble*/
	for (size_t i = 0; i < length - 1; i++)
	{
		for (size_t j = 0; j < length - i - 1; j++)
		{
			if (mas[j] > mas[j + 1])
			{
				std::swap(mas[j], mas[j + 1]);
				swap1++;
			}
			compare1++;
		}
	}

	int left{ 1 };
	int right{ length - 1 };
	while (left <= right)
	{
		for (size_t i = right; i >= left; i--)
		{
			if (arr[i - 1] > arr[i])
			{
				std::swap(arr[i - 1], arr[i]);
				swap2++;
			}
			compare2++;
		}
		left++;
		for (size_t i = left; i <= right; i++)
		{
			if (arr[i - 1] > arr[i])
			{
				std::swap(arr[i - 1], arr[i]);
				swap2++;
			}
			compare2++;
		}
		right--;
	}
	

	/*for (auto& i : arr)
	{
		std::cout << i << std::endl;
	}*/

	std::cout << compare1 << " compares, " << swap1 << " swap of bubble" << std::endl;
	std::cout << compare2 << " compares, " << swap2 << " swap." << std::endl;

	return 0;
}