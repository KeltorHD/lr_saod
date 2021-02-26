#include <iostream>
#include <fstream>
#include <algorithm>

int main()
{
	/*подготовка*/
	const int length{ 10 };

	std::fstream file("sort.bin", std::ios::binary | std::ios::out | std::ios::in);
	std::fstream tmp_1("tmp1.bin", std::ios::binary | std::ios::out | std::ios::in);
	std::fstream tmp_2("tmp2.bin", std::ios::binary | std::ios::out | std::ios::in);

	for (size_t i = 0; i < length; i++)
	{
		int tmp = rand() % 10000;
		file.write((char*)&tmp, sizeof(int));
	}
	file.seekg(0);
	for (size_t i = 0; i < length; i++)
	{
		int var;
		file.read((char*)&var, sizeof(int));
		std::cout << var << std::endl;
	}

	unsigned long long ser{ 1 };

	while (ser <= length)
	{
		for (size_t i = 0; i < length / ser; i++)
		{
			if (i % 2 == 0)
			{
				for (size_t j = 0; j < ser; j++)
				{
					int var{}; 
					file.seekg((i + j * ser) * sizeof(int));
					file.read((char*)&var, sizeof(int));
					tmp_1.write((char*)&var, sizeof(int));
				}
			}
			else
			{
				for (size_t j = 0; j < ser; j++)
				{
					int var{};
					file.seekg((i + j * ser) * sizeof(int));
					file.read((char*)&var, sizeof(int));
					tmp_2.write((char*)&var, sizeof(int));
				}
			}
		}
		file.seekg(0);
		tmp_1.seekg(0);
		tmp_2.seekg(0);
		std::cout << "tmp1 ";
		for (size_t i = 0; i < length / 2; i++)
		{
			int var;
			tmp_1.read((char*)&var, sizeof(int));
			std::cout << var << " ";
		}
		std::cout << "\ntmp2 ";
		for (size_t i = 0; i < length / 2; i++)
		{
			int var;
			tmp_2.read((char*)&var, sizeof(int));
			std::cout << var << " ";
		}
		std::cout << "\n";
		tmp_1.seekg(0);
		tmp_2.seekg(0);

		int left{}, rigth{};
		int var_1{}, var_2{};
		int min_file = 0;
		int min{}, max{};
		int min{}, max{};
		tmp_1.read((char*)&var_1, sizeof(int));
		tmp_2.read((char*)&var_2, sizeof(int));
		min = var_1 < var_2 ? var_1 : var_2;
		max = var_1 < var_2 ? var_2 : var_1;
		min_file = var_1 < var_2 ? 1 : 2;
		for (size_t i = 0; left + rigth < 2 * ser; i++)
		{
			file.write((char*)&min, sizeof(int));

			if (min_file == 1)
			{
				left++;
				if (i
					tmp_1.read((char*)&var_1, sizeof(int));
			}
			else
			{
				rigth++;
				tmp_2.read((char*)&var_2, sizeof(int));
			}
		}

		/*int var_1{}, var_2{};
		int min_file = 0;
		int min{}, max{};
		tmp_1.read((char*)&var_1, sizeof(int));
		tmp_2.read((char*)&var_2, sizeof(int));
		min = var_1 < var_2 ? var_1 : var_2;
		max = var_1 < var_2 ? var_2 : var_1;
		min_file = var_1 < var_2 ? 1 : 2;
		for (size_t i = 1; i < ser * 2; i++)
		{
			file.write((char*)&min, sizeof(int));
			
			if (ser != 1)
			{
				if (min_file == 1 && )
				{
					tmp_1.read((char*)&var_1, sizeof(int));
				}
				else
				{
					tmp_2.read((char*)&var_2, sizeof(int));
				}
				min = var_1 < var_2 ? var_1 : var_2;
				max = var_1 < var_2 ? var_2 : var_1;
				min_file = var_1 < var_2 ? 1 : 2;
			}
		}
		file.write((char*)&max, sizeof(int));*/
		file.seekg(0);
		std::cout << "file ";
		for (size_t i = 0; i < length; i++)
		{
			int var;
			file.read((char*)&var, sizeof(int));
			std::cout << var << " ";
		}
		std::cout << "\n\n";
		file.seekg(0);

		ser *= 2;
	}

	file.seekg(0);
	for (size_t i = 0; i < length; i++)
	{
		int var;
		file.read((char*)&var, sizeof(int));
		std::cout << var << std::endl;
	}
	

	return 1;
}