#include <iostream>
#include <Windows.h>
#include <cstdint>
#include "queue.hpp"

template<typename Struct>
uint64_t max_size_struct(const Struct&);

int main()
{
	system("chcp 65001>nul");

	std::cout << "Максимальное количество элементов для Queue<double>:\t " << max_size_struct(Queue<double>()) << std::endl;
	std::cout << "Максимальное количество элементов для Queue<float>:\t " << max_size_struct(Queue<float>()) << std::endl;
	std::cout << "Максимальное количество элементов для Queue<int>:\t " << max_size_struct(Queue<int>()) << std::endl;
	std::cout << "Максимальное количество элементов для Queue<char>:\t " << max_size_struct(Queue<char>()) << std::endl;

	return static_cast<bool>(std::cout);
}

template<typename Struct>
uint64_t max_size_struct(const Struct&)
{
	/*сколько байт занимает пустой объект: память на top, end и т.д.*/
	static const uint32_t st_size = sizeof(Struct{});

	/*подсчет памяти средствами windows*/
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);

	uint64_t memory_free{ statex.ullAvailPhys + statex.ullAvailVirtual }; /*в байтах физической и виртуальной*/

	memory_free -= st_size; /*вычитаем количество байт на структуру без данных*/

	return (memory_free / Struct::bite_per_element()); /*делим доступное кол-во байт на кол-во байт на один элемент*/
}
