#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

struct Student
{
	std::string firstName;
	std::string secondName;
	int l1;
	int l2;
	int l3;
	int sum;
};

int main()
{
	system("chcp 65001 > nul");

	std::ifstream ifs;
	ifs.open("data.txt");

	int counter{};
	ifs >> counter;
	std::shared_ptr<Student[]> mas{ new Student[counter] };

	for (int i = 0; i < counter; i++)
	{
		ifs >> mas[i].firstName;
		ifs >> mas[i].secondName;
		ifs >> mas[i].l1;
		ifs >> mas[i].l2;
		ifs >> mas[i].l3;
		mas[i].sum = mas[i].l1 + mas[i].l2 + mas[i].l3;
	}

	std::sort(&mas[0], &mas[0] + counter, [](const Student& st1, const Student& st2) {return st1.sum > st2.sum; });

	std::cout << "Фамилия Имя:" << "\t\t" << "l1" << "\t" << "l2" << "\t" << "l3" << std::endl;
	for (int i = 0; i < counter; i++)
	{
		std::cout << mas[i].firstName << " " << mas[i].secondName << "\t" << mas[i].l1 << "\t" << mas[i].l2 << "\t" << mas[i].l3 << std::endl;
	}

	return 1;
}