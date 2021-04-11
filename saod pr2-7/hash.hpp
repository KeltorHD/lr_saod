#pragma once

#include <mutex>
#include <iostream>
#include <array>
#include <string>
#include <algorithm>
#include <utility>

struct data
{
    std::string key;
    int count;
};

class Hash
{
public:
    static const int length{ 1000 };
    static const int threads{ 10 };

    void plus(std::string to_add)
    {
        int key = this->get_key(to_add);

        int c_t = key / (length / threads);
        int k_t = key - c_t * (length / threads);

        this->mutexs[c_t].lock();
        this->mas[c_t][k_t].count++;
        this->mutexs[c_t].unlock();
    }

    const std::array<std::array<data, length>, threads>& get_array() const { return this->mas; }

private:
    std::array<std::array<data, length>, threads> mas{};
    std::array<std::mutex, threads> mutexs{};

    /*int calc_collision_plus(int key)
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
    }*/

    int get_key(std::string to_add)
    {
        size_t x{};
        for (auto& i : to_add)
        {
            x += size_t(i);
        }
        double a = 0.618 * x;
        int b = (a - int(a)) * 50;

        return b % this->length;
    }
};