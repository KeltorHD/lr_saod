#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

int main()
{
	system("chcp 65001>nul");

	std::ifstream file("gr.txt");
	if (!file.is_open())
		throw std::exception("not open file");

	size_t count_vertex{};
	file >> count_vertex;
	std::vector<std::vector<int>> graph(count_vertex, std::vector<int>(count_vertex, false));

	/*заполняем граф, матрица смежности*/
	for (size_t i = 0; i < count_vertex; i++)
	{
		for (size_t j = 0; j < count_vertex; j++)
		{
			bool tmp{};
			file >> tmp;
			graph[i][j] = tmp;
		}
	}

	/*определение степени вершины*/
	std::vector<int> deg(count_vertex);
	for (int i = 0; i < count_vertex; ++i)
		for (int j = 0; j < count_vertex; ++j)
			deg[i] += graph[i][j];

	/*находим первую вершину для старта*/
	int first = 0;
	while (!deg[first])
	{
		++first;
	}

	int v1 = -1, v2 = -1;
	bool bad = false;

	/*если есть 2 верш. с нечетными степенями, то эйлеров путь есть*/
	for (int i = 0; i < count_vertex; ++i)
	{
		if (deg[i] & 1)
			if (v1 == -1)
				v1 = i;
			else if (v2 == -1)
				v2 = i;
			else
				bad = true;
	}

	if (v1 != -1) /*добавляем ребро между v1, v2*/
		++graph[v1][v2], ++graph[v2][v1];

	std::stack<int> st;
	st.push(first);   /*кладем стартовую вершину*/
	std::vector<int> res; 
	while (!st.empty())
	{
		int v = st.top();
		std::cout << "Вершина: " << v << std::endl;
		int i;
		for (i = 0; i < count_vertex; ++i) /*находим первое попавшееся ребро*/
			if (graph[v][i])
				break;

		std::cout << "I: " << i << std::endl;
		if (i == count_vertex) /*если степень вершины = 0, ребер с этой вершиной нет*/
		{
			std::cout << "Добавляем в результат" << std::endl;
			res.push_back(v); /*добавляем в результат*/
			st.pop(); /*удаляем из стека*/
		}
		else
		{
			--graph[v][i]; /*удаляем ребро, выходящее из v*/
			--graph[i][v];
			st.push(i); /*второй конец ребра кладем в st*/
			std::cout << "Удаляем ребро " << v << ":" << i << std::endl;
		}
		std::cout << "-------------------" << std::endl;
	}


	if (v1 != -1) /*если добавили ребро v1-v2*/
		for (size_t i = 0; i + 1 < res.size(); ++i)
			/*если встретили добавленное ребро v1-v2*/
			if (res[i] == v1 && res[i + 1] == v2 || res[i] == v2 && res[i + 1] == v1)
			{
				std::vector<int> res2;
				for (size_t j = i + 1; j < res.size(); ++j)
					res2.push_back(res[j]);
				for (size_t j = 1; j <= i; ++j) /*удаляем первый элемент*/
					res2.push_back(res[j]);
				res = res2;
				break;
			}

	/*если остались несвязанные вершины*/
	for (int i = 0; i < count_vertex; ++i)
		for (int j = 0; j < count_vertex; ++j)
			if (graph[i][j])
				bad = true;

	if (bad)
	{
		std::cout << "Эйлерового пути нет" << std::endl;
	}
	else
	{
		std::cout << "Эйлеров путь: ";
		for (size_t i = 0; i < res.size(); ++i)
			std::cout << res[i] << " ";
		std::cout << std::endl;
	}

	return 0;
}