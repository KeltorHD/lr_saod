#pragma once

#include <fstream>
#include <string>
#include <iostream>

class Hash_table
{
public:
	Hash_table();
	~Hash_table();

	/*вставка значения в таблицу, to_insert - по какому ключу, data - что вставляем*/
	void insert(std::string to_insert, std::string data);

	/*поиск значения в таблице: 1 - если нашлось значение, to_insert - по какому ключу ищем, data - куда вставляем ответ*/
	bool find(std::string to_find, std::string& data);

private:
	/*переменные*/
	/*размер хэш-таблицы*/
	const size_t table_size{ 1000 };
	/*макс размер ключа*/
	const size_t id_size{ 50 };
	/*макс размер хранимых данных*/
	const size_t data_size{ 100 };

	/*файлик*/
	std::fstream file;


	/*внутренние функции*/
	/*получение ключа по строке, метод свертки (xor)*/
	size_t get_key(std::string& id);

	/*разрешение коллизии на вставку методом линейного зондирования*/
	size_t correct_collision_insert(size_t key);

	/*разрешение коллизии на поиск, 1 - если нужный ключ нашелся, key - куда вставляем ключ*/
	bool correct_collision_find(size_t& key, std::string to_find);
};