#pragma once

#include <iostream>
#include <array>
#include <string>
#include <algorithm>
#include <utility>

namespace ha 
{

    struct data
    {
        std::string key;
        int count;
        int cost;
    };

    class Ha
    {
    public:
        static const int length{ 1000 };

        void insert(std::string to_add)
        {
            int key = this->get_key(to_add);
            mas[key].count++;
        }

    private:
        std::array<data, length> mas;

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
}