#include <iostream>
#include <fstream>

#include <chrono> // дл€ функций из std::chrono

class Timer
{
private:
	// ѕсевдонимы типов используютс€ дл€ удобного доступа к вложенным типам
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
	const int length{ 1000 };

	int mas[length];
	std::fstream file("sort.bin", std::ios::binary | std::ios::out | std::ios::in);

	for (size_t i = 0; i < length; i++)
	{
		int tmp = mas[i] = rand() % 10000;
		file.write((char*)&tmp, sizeof(int));
	}
	file.seekg(0);

	Timer t;
	std::cout << "bubble in ddr4: " << std::endl;
	/*bubble*/
	for (size_t i = 0; i < length - 1; i++)
	{
		for (size_t j = 0; j < length - i - 1; j++)
		{
			if (mas[j] > mas[j + 1])
			{
				std::swap(mas[j], mas[j + 1]);
			}
		}
	}
	std::cout << "complete for " << t.elapsed() << " seconds" << std::endl;

	t.reset();
	std::cout << "bubble in ssd: " << std::endl;
	/*bubble*/
	for (size_t i = 0; i < length - 1; i++)
	{
		for (size_t j = 0; j < length - i - 1; j++)
		{
			int vf{}, vs{};
			file.seekg(j * sizeof(int));
			file.read((char*)&vf, sizeof(int));
			file.seekg((j + 1) * sizeof(int));
			file.read((char*)&vs, sizeof(int));
	
			if (vf > vs)
			{
				file.seekg(j * sizeof(int));
				file.write((char*)&vs, sizeof(int));

				file.seekg((j  + 1) * sizeof(int));
				file.write((char*)&vf, sizeof(int));
			}
		}
	}
	std::cout << "complete for " << t.elapsed() << " seconds" << std::endl;

	/*file.seekg(0);
	for (size_t i = 0; i < length; i++)
	{
		int var;
		file.read((char*)&var, sizeof(int));
		std::cout << var << std::endl;
	}*/
}