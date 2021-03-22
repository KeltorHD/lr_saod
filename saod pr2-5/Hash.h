#pragma once

#include <iostream>
#include <array>
#include <string>
#include <algorithm>
#include <utility>

struct data
{
    std::string key;
    int count;
    int cost;
};

class Hash
{
public:
	void insert(std::string to_add, int count, int cost)
	{
        int key = this->calc_collision_insert(this->get_key(to_add));
        mas[key].key = to_add;
        mas[key].count = count;
        mas[key].cost = cost;
	}

    bool find(std::string to_find, int& count, int& cost)
    {
        int key = this->get_key(to_find);
        if (this->mas[key].key == "")
        {
            return false;
        }
        else
        {
            if (this->mas[key].key == to_find)
            {
                count = this->mas[key].count;
                cost = this->mas[key].cost;
                return true;
            }
            else
            {
                if (this->calc_collision_find(key))
                {
                    count = this->mas[key].count;
                    cost = this->mas[key].cost;
                    return true;
                }
                return false;
            }
        }
        
    }

private:
    std::array<data, 1000> mas;

    bool calc_collision_find(int& key)
    {
        int index{ key };
        int i{ 1 };

        while (true)
        {
            if (index < 999)
                index = 0;

            if (mas[index + i].key == "")
            {
                return false;
            }
            else
            {
                key = index + i;
                return true;
            }

            i += i * i;
            index += i;
        }
    }

    int calc_collision_insert(int key)
    {
        if (mas[key].key == "")
            return key;

        int index{ key };
        int i{ 1 };
        
        while (true)
        {
            if (index < 999)
                index = 0;

            if (mas[index + i].key == "")
                return index + i;
            else
            {
                i += i * i;
                index += i;
            }
        }
    }

	int get_key(std::string to_add)
    {
        int key =
            (unsigned char)to_add[0] << 24 |
            (unsigned char)to_add[1] << 16 |
            (unsigned char)to_add[2] << 8 |
            (unsigned char)to_add[3];

        size_t counter{ 4 };
        for (size_t i = 0; i < (to_add.size() - 4) / 4; i++)
        {
            if (to_add.size() - i * 4 >= 4)
            {
                key = key ^ (
                    (unsigned char)to_add[counter++] << 24 |
                    (unsigned char)to_add[counter++] << 16 |
                    (unsigned char)to_add[counter++] << 8 |
                    (unsigned char)to_add[counter++]);
            }
            else if (to_add.size() - i * 4 == 3)
            {
                key = key ^ (
                    (unsigned char)to_add[counter++] << 24 |
                    (unsigned char)to_add[counter++] << 16 |
                    (unsigned char)to_add[counter++] << 8);
            }
            else if (to_add.size() - i * 4 == 2)
            {
                key = key ^ (
                    (unsigned char)to_add[counter++] << 24 |
                    (unsigned char)to_add[counter++] << 16);
            }
            else if (to_add.size() - i * 4 == 1)
            {
                key = key ^ (
                    (unsigned char)to_add[counter++] << 24);
            }
        }
        return key % 1000;
    }

};