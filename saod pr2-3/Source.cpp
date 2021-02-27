#include <iostream>
#include <fstream>
#include <algorithm>

#include "file_array.h"

#include <chrono> // для функций из std::chrono

class Timer
{
private:
	// Псевдонимы типов используются для удобного доступа к вложенным типам
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

int main()
{
	/*подготовка*/
	File_array<int> file("sort.bin");
	File_array<int> tmp_1("tmp1.bin");
	File_array<int> tmp_2("tmp2.bin");
	const int length{ 10000 };
	bool enable_steps{ false };
	bool enable_mas{ false };

	file.resize(length);
	tmp_1.clear();
	tmp_2.clear();

	for (size_t i = 0; i < file.length(); i++)
	{
		file[i] = rand() % length;
	}
	if (enable_steps)
	{
		for (size_t i = 0; i < file.length(); i++)
		{
			std::cout << file[i] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "Sort start." << std::endl;
	Timer t;

	unsigned long long ser{ 1 };


	/*сортировка*/
	while (ser < length) /*пока серия не сравнится с длиной*/
	{
		size_t i;
		for (i = 0; i < length / ser; i++) /*разделяем файлик на серии*/
		{
			if (i % 2 == 0)
			{
				for (size_t j = 0; j < ser && (i * ser + j < file.length()); j++)
				{
					tmp_1.push_back(file[i * ser + j]);
				}
			}
			else
			{
				for (size_t j = 0; j < ser && (i * ser + j < file.length()); j++)
				{
					tmp_2.push_back(file[i * ser + j]);
				}
			}
		}
		for (size_t j = i * ser; j < length; j++)
		{
			if (tmp_1.length() < tmp_2.length())
			{
				tmp_1.push_back(file[j]);
			}
			else
			{
				tmp_2.push_back(file[j]);
			}
		}
		if (enable_steps)
		{
			std::cout << "ser: " << ser << std::endl;
			std::cout << "tmp1: ";
			for (size_t i = 0; i < tmp_1.length(); i++)
			{
				std::cout << (i % ser == 0 ? " | " : " ") << tmp_1[i];
			}
			std::cout << std::endl;
			std::cout << "tmp2: ";
			for (size_t i = 0; i < tmp_2.length(); i++)
			{
				std::cout << (i % ser == 0 ? " | " : " ") << tmp_2[i];
			}
			std::cout << std::endl;
		}

		/*магия с объединением в результирующий файл*/
		file.clear();
		size_t count_ser_file{ std::max(tmp_1.length() / ser + (tmp_1.length() % ser != 0 ? 1 : 0), tmp_2.length() / ser + (tmp_2.length() % ser != 0 ? 1 : 0)) };
		for (size_t i = 0; i < count_ser_file; i++)
		{
			size_t l1{ tmp_1.length() }, l2{ tmp_2.length() };
			size_t left_length{ i * ser + ser - 1 >= tmp_1.length() ? tmp_1.length() - i * ser : ser },
				  right_length{ i * ser + ser - 1 >= tmp_2.length() ? tmp_2.length() - i * ser : ser };
			size_t left_index{ i * ser }, right_index{ i * ser };
			/*Сливаем массивы, пока один не закончится*/
			while (left_length && right_length) 
			{
				if (tmp_1[left_index] < tmp_2[right_index]) 
				{
					file.push_back(tmp_1[left_index]);
					if (enable_steps)
						std::cout << tmp_1[left_index] << " ";
					left_index++;
					--left_length;
				}
				else 
				{
					file.push_back(tmp_2[right_index]);
					if (enable_steps)
						std::cout << tmp_2[right_index] << " ";
					right_index++;
					right_length--;
				}
			}
			/*Если закончился первый массив*/
			if (left_length == 0) 
			{
				for (int i = 0; i < right_length; ++i)
				{
					file.push_back(tmp_2[right_index]);
					if (enable_steps)
						std::cout << tmp_2[right_index] << " ";
					right_index++;
				}
			}
			else /*Если закончился второй массив*/
			{
				for (int i = 0; i < left_length; ++i) 
				{
					file.push_back(tmp_1[left_index]);
					if (enable_steps)
						std::cout << tmp_1[left_index] << " ";
					left_index++;
				}
			}
		}
		if (enable_steps)
		{
			std::cout << std::endl;

			std::cout << "file: ";
			for (size_t i = 0; i < file.length(); i++)
			{
				std::cout << file[i] << " ";
			}
			std::cout << std::endl;
		}

		/*увеличиваем серию, обнуляем временные файлики*/
		ser *= 2;
		tmp_1.clear();
		tmp_2.clear();
	}

	std::cout << "File sorting finished, " << t.elapsed()<<"seconds: " << std::endl;
	if (enable_mas)
	{
		for (size_t i = 0; i < file.length(); i++)
		{
			std::cout << file[i] << " ";
		}
		std::cout << std::endl;
	}

	return 1;
}