#include <iostream>
#include <random>
#include <climits>
#include <fstream>
#include <thread>

#include "hash.hpp"
#include "ha.hpp"

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
	Hash hash;
	std::random_device rd;
	std::mt19937 generator(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 

	auto func = [](Hash& hash, std::mt19937& generator)
	{
		const size_t length{ 1'000'000 / 10 };
		const size_t len_str{ 15 };
		std::string testing("", len_str);

		/*заполение*/
		for (size_t i = 0; i < length; i++)
		{
			for (size_t j = 0; j < len_str; j++)
			{
				int tmp{ generator() % SCHAR_MAX };
				//std::cout << tmp << std::endl;
				testing[j] = tmp;
			}
			//std::cout << testing << std::endl;
			hash.plus(testing);
		}
	};
	std::array<std::shared_ptr<std::thread>, 10> threads{};
	Timer t;
	for (size_t i = 0; i < 10; i++)
	{
		threads[i] = std::make_shared<std::thread>(func, std::ref(hash), std::ref(generator));
	}

	for (size_t i = 0; i < 10; i++)
	{
		threads[i]->join();
	}
	std::cout << t.elapsed() << std::endl;
	t.reset();


	const size_t length{ 1'000'000 };
	const size_t len_str{ 15 };
	std::string testing("", len_str);
	ha::Ha ha;

	/*заполение*/
	for (size_t i = 0; i < length; i++)
	{
		for (size_t j = 0; j < len_str; j++)
		{
			int tmp{ generator() % SCHAR_MAX };
			//std::cout << tmp << std::endl;
			testing[j] = tmp;
		}
		//std::cout << testing << std::endl;
		ha.insert(testing);
	}
	std::cout << t.elapsed() << std::endl;

	///*достаем и записываем в файлик*/
	//std::ofstream file("data.csv");
	//if (!file.is_open())
	//	throw "not open file";

	//const auto& mas = hash.get_array();
	//for (size_t i = 0; i < mas.size(); i++)
	//{
	//	file << i << "," << mas[i].count << std::endl;
	//}

	return 0;
}