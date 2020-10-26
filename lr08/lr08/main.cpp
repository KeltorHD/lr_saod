#include <iostream>
#include <algorithm>
#include <vector>
#include "list.h"

struct PartPolynom
{
	double c;
	double e;

	bool operator==(const PartPolynom& p)
	{
		if (c == p.c && e == p.e)
			return true;
		return false;
	}
};

/*нахождение суммы*/
List<PartPolynom> sum(const List<PartPolynom>& a, const List<PartPolynom>& b);

/*нахождение произведения*/
List<PartPolynom> multip(const List<PartPolynom>& a, const List<PartPolynom>& b);

std::ostream& operator<<(std::ostream& os, const List<PartPolynom>& a);

int main()
{
	system("chcp 65001>nul");

	List<PartPolynom> polA = { {5,0}, {2,1}, {4,2}, {-7,3}, {8,5},{9,9} };
	List<PartPolynom> polB = { {-2,0}, {-3,1}, {5,2}, {-8,3} };

	std::cout << "Полином A: " << std::endl;
	std::cout << polA << std::endl;
	std::cout << "Полином B: " << std::endl;
	std::cout << polB << std::endl << std::endl;

	std::cout << "Результат сложения: " << std::endl;
	std::cout << sum(polA, polB) << std::endl << std::endl;

	std::cout << "Результат перемножения: " << std::endl;
	std::cout<<multip(polA,polB) << std::endl << std::endl;

	return bool(std::cout);
}

List<PartPolynom> sum(const List<PartPolynom>& a, const List<PartPolynom>& b)
{
	List<PartPolynom> result{};

	std::vector<size_t> a_v, b_v; /*использованные индексы частей полинома*/


	for (size_t i = 0; i < a.length(); i++) /*сложение коэф. при одинаковых степенях*/
	{
		for (size_t j = 0; j < b.length(); j++)
		{
			if (a[i].e == b[j].e)
			{
				PartPolynom tmp{ a[i].c + b[j].c, a[i].e };
				if (!result.find(tmp))
				{
					result.pushBack(tmp);
					a_v.push_back(i);
					b_v.push_back(j);
				}
			}
		}
	}

	for (size_t i = 0; i < a.length(); i++) /*если пары для сложения не нашлось*/
	{
		if (std::find(a_v.begin(), a_v.end(), i) == a_v.end())
			result.pushBack(a[i]);
	}
	for (size_t i = 0; i < b.length(); i++)
	{
		if (std::find(b_v.begin(), b_v.end(), i) == b_v.end())
			result.pushBack(b[i]);
	}

	return result;
}

List<PartPolynom> multip(const List<PartPolynom>& a, const List<PartPolynom>& b)
{
	List<PartPolynom> result{};
	List<PartPolynom> tmp{};

	std::vector<double> tmp_v{}; /*вектор степеней, хранящихся в tmp*/

	/*простое перемножение*/
	for (size_t i = 0; i < a.length(); i++) /*сложение коэф. при одинаковых степенях*/
	{
		for (size_t j = 0; j < b.length(); j++)
		{
			PartPolynom p{ a[i].c * b[j].c, a[i].e + b[j].e };
			tmp.pushBack(p);
			tmp_v.push_back(p.e);
		}
	}

	std::sort(tmp_v.begin(), tmp_v.end());
	tmp_v.erase(std::unique(tmp_v.begin(), tmp_v.end()), tmp_v.end()); /*нахождение уникальных степеней в tmp*/

	for (auto& element : tmp_v) /*склеивание частей с одинаковыми степенями*/
	{
		PartPolynom p{0., element};
		for (size_t i = 0; i < tmp.length(); i++)
		{
			if (tmp[i].e == element)
			{
				p.c += tmp[i].c;
			}
		}
		result.pushBack(p);
	}

	return result;
}

std::ostream& operator<<(std::ostream& os, const List<PartPolynom>& a)
{
	for (size_t i = 0; i < a.length(); i++)
	{
		if (a[i].c < 0)
		{
			os << "- ";
		}
		else
		{
			os << "+ ";
		}
		os << abs(a[i].c) << "*x^(" << a[i].e << ") ";
	}
	return os;
}
