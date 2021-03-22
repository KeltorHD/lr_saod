#include "hash_table.hpp"

Hash_table::Hash_table()
{
	this->file.open("utility.bin", std::ios::binary | std::ios::out | std::ios::in);

	/*инициализаци€, заполнение таблицы на table_size елементов*/
	std::string tmp_id{};
	std::string tmp_data{};
	tmp_id.resize(this->id_size);
	tmp_data.resize(this->data_size);
	for (size_t i = 0; i < this->table_size; i++)
	{
		this->file.write(tmp_id.c_str(), this->id_size);
		this->file.write(tmp_data.c_str(), this->data_size);
	}

    this->file.seekg(0, std::ios_base::beg);
}

Hash_table::~Hash_table()
{
	this->file.close();
}

void Hash_table::insert(std::string to_insert, std::string data)
{
    to_insert.resize(this->id_size);
    data.resize(this->data_size);
    size_t key{ this->correct_collision_insert(this->get_key(to_insert)) }; /*находим свободную €чейку*/

    this->file.seekp(key * (this->data_size + this->id_size), std::ios_base::beg); /*и записываем в нее ключ и значение*/
    this->file.write(to_insert.c_str(), this->id_size);
    this->file.write(data.c_str(), this->data_size);
}

bool Hash_table::find(std::string to_find, std::string& data)
{
    to_find.resize(this->id_size);
    size_t key = this->get_key(to_find); /*получаем ключ*/
    if (this->correct_collision_find(key, to_find)) /*если запись есть в таблице*/
    {
        data.resize(this->data_size);
        this->file.seekg(key * (this->data_size + this->id_size), std::ios_base::beg); /*и записываем в нее ключ и значение*/
        this->file.read(&to_find[0], this->id_size);
        this->file.read(&data[0], this->data_size);
        return true;
    }

    return false;
}

size_t Hash_table::get_key(std::string& id)
{
    /*получаем ключ путем перемешивани€ каждых 4-х байтов id операцией xor*/
    size_t key =
        (unsigned char)id[0] << 24 |
        (unsigned char)id[1] << 16 |
        (unsigned char)id[2] << 8 |
        (unsigned char)id[3];

    size_t counter{ 4 };
    for (size_t i = 0; i < (id.size() - 4) / 4; i++)
    {
        if (id.size() - i * 4 >= 4)
        {
            key = key ^ (
                (unsigned char)id[counter++] << 24 |
                (unsigned char)id[counter++] << 16 |
                (unsigned char)id[counter++] << 8 |
                (unsigned char)id[counter++]);
        }
        else if (id.size() - i * 4 == 3)
        {
            key = key ^ (
                (unsigned char)id[counter++] << 24 |
                (unsigned char)id[counter++] << 16 |
                (unsigned char)id[counter++] << 8);
        }
        else if (id.size() - i * 4 == 2)
        {
            key = key ^ (
                (unsigned char)id[counter++] << 24 |
                (unsigned char)id[counter++] << 16);
        }
        else if (id.size() - i * 4 == 1)
        {
            key = key ^ (
                (unsigned char)id[counter++] << 24);
        }
    }
    return key % this->table_size;
}

size_t Hash_table::correct_collision_insert(size_t key)
{
    /*получение значени€ по ключу*/
    std::string empty{}; empty.resize(this->id_size);
    std::string tmp{}; tmp.resize(this->id_size);
    this->file.seekg(key * (this->data_size + this->id_size), std::ios_base::beg);
    this->file.read(&tmp[0], this->id_size);

    if (tmp == empty) /*если €чейка не зан€та*/
        return key;

    size_t index{ key };

    while (true) /*иначе находим первую попавшуюс€ пустую €чейку*/
    {
        if (index >= this->table_size - 1) /*если дошли до конца таблицы, начинаем сначала*/
            index = 0;

        /*находим значение по новому ключу*/
        this->file.seekg((key + 1) * (this->data_size + this->id_size), std::ios_base::beg);
        this->file.read(&tmp[0], this->id_size);

        if (tmp == empty) /*если €чейка не зан€та*/
        {
            return index + 1;
        }
        else
        {
            index++;
        }
    }
}

bool Hash_table::correct_collision_find(size_t& key, std::string to_find)
{
    /*переменные дл€ поиска нужного ключа*/
    std::string empty{}; empty.resize(this->id_size);
    std::string tmp{}; tmp.resize(this->id_size);
    this->file.seekg(key * (this->data_size + this->id_size), std::ios_base::beg);
    this->file.read(&tmp[0], this->id_size);

    if (tmp != empty && tmp == to_find) /*если €чейка не пуста€*/
    {
        return true;
    }
    else if (tmp == empty) /*если €чейка пуста*/
    {
        return false;
    }/*иначе ищем либо пустую, либо совпадающую c to_find*/

    size_t index{ key };
    size_t i{ 1 };

    while (true)
    {
        if (index >= this->table_size - 1) /*если дошли до конца таблицы, начинаем сначала*/
            index = 0;

        /*находим значение по новому ключу*/
        this->file.seekg((key + 1) * (this->data_size + this->id_size), std::ios_base::beg);
        this->file.read(&tmp[0], this->id_size);

        if (tmp == empty) /*если €чейка не зан€та, значит искомой записи нет*/
        {
            return false;
        }
        else /*если €чейка не пуста€, то сравниваем id с искомым*/
        {
            if (tmp == to_find) /*если искома€ запись нашлась*/
            {
                key = index + 1;
                return true;
            } /*в противном случае продолжаем поиски*/
        }

        index++;
    }
}
