#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

std::vector<std::string> delim(std::string str, std::string delim)
{
	std::vector<std::string> arr;
	size_t prev = 0;
	size_t next;
	size_t delta = delim.length();

	while ((next = str.find(delim, prev)) != std::string::npos)
	{
		arr.push_back(str.substr(prev, next - prev));
		prev = next + delta;
	}

	arr.push_back(str.substr(prev));

	return arr;
}

struct node_data_t
{
	double I{ -1. };
	double R{};
};

struct graph_t
{
	std::vector<std::vector<int>> graph; /*матрица смежности*/
	std::vector<node_data_t> node_data;  /*сила тока и сопротивление провода*/
};

void fill_graph(graph_t& graph, const std::string& filename)
{
	graph.graph.clear();

	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cout << "NOT OPEN GRAPH.TXT" << std::endl;
		exit(1);
	}

	std::vector<std::string> file_vec;

	double I1{};
	size_t length{};
	file >> length;

	file >> I1;
	//std::cout << "count nodes: " << length << std::endl;
	//std::cout << "I1: " << I1 << std::endl;

	graph.node_data.push_back({ I1,0 });

	for (size_t i = 0; i < length - 2; i++)
	{
		double tmp{};
		file >> tmp;

		//std::cout << "R(" << i + 2 << "): " << tmp << std::endl;

		graph.node_data.push_back({ -1., tmp });
	}
	graph.node_data.push_back({ I1,0 });

	{
		std::string tmp;
		std::getline(file, tmp);

		while (std::getline(file, tmp))
		{
			file_vec.push_back(tmp);
		}
	}

	for (size_t i = 0; i < file_vec.size(); i++)
	{
		file_vec[i].erase(std::remove(file_vec[i].begin(), file_vec[i].end(), ' '), file_vec[i].end());
		//std::cout << file_vec[i] << std::endl;
	}

	graph.graph.resize(file_vec.size());
	for (size_t i = 0; i < file_vec.size(); i++)
	{
		graph.graph[i].resize(file_vec.size());
	}

	for (size_t i = 0; i < file_vec.size(); i++)
	{
		int first = std::atoi(delim(file_vec[i], ":")[0].c_str());
		/*int first = std::atoi(delim(delim(file_vec[i], ":")[1], " ")[0].c_str());*/

		if (file_vec.size() >= 1)
		{
			if (delim(file_vec[i], ":").size() < 2)
				continue;

			std::vector<std::string> seconds{ delim(delim(file_vec[i], ":")[1], ",") };

			if (seconds[0] != "")
			{
				for (size_t j = 0; j < seconds.size(); j++)
				{
					int second = std::atoi(seconds[j].c_str());

					//std::cout << "connect " << first << "-" << second << std::endl;

					graph.graph[first][second] = 1;
					//graph.graph[s_second][f_first] = 1;
				}
			}
		}
	}
}

void print(const graph_t& g)
{
	std::cout << "Graph:" << std::endl;
	std::cout << "\t";
	for (size_t i = 0; i < g.graph.size(); i++)
	{
		std::cout << i + 1 << "\t";
	}
	std::cout << std::endl;
	for (size_t i = 0; i < g.graph.size(); i++)
	{
		std::cout << i + 1 << "\t";
		for (size_t j = 0; j < g.graph[i].size(); j++)
		{
			std::cout << g.graph[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

void print_force(const graph_t& g)
{
	std::cout << "Information about the vertices:" << std::endl;
	for (size_t i = 0; i < g.node_data.size(); i++)
	{
		std::cout << "vertex: " << i + 1 << ", force: " << g.node_data[i].I << ", resistance: " << g.node_data[i].R << std::endl;
	}
}

int main()
{
	graph_t g;
	fill_graph(g, "graph.txt");
	print(g);

	std::cout << std::endl;
	print_force(g);

	std::cout << std::endl << "BFS start" << std::endl;
	size_t v{ 0u };
	std::queue<size_t> plan; // план посещения в виде очереди
	plan.push(v);   // мы нумеруем с 0, а не с 1
	g.graph[v][v] = 1; // отмечаем, что эта вершина уже заносилась в план 
	while (!plan.empty()) 
	{
		v = plan.front(); // посещаем следующую по плану вершину 
		std::cout << "visited: " << v + 1 << std::endl;

		/*начало расчёта токов*/
		if (g.node_data[v].I < 0)
		{
			size_t count_father{ 0u };
			std::vector<int> fathers{};
			for (size_t i = 0u; i < g.graph.size(); i++)
			{
				if (i != v && g.graph[i][v])
				{
					count_father++;
					fathers.push_back(i);
					if (g.node_data[i].I < 0)
						continue;
				}
			}
			if (count_father == 1) /*один предок*/
			{
				size_t count_neighborhood{ 0u };
				std::vector<int> neighborhoods{};
				for (size_t i = 0; i < g.graph.size(); i++)
				{
					if (fathers[0] != i && v != i && g.graph[fathers[0]][i])
					{
						count_neighborhood++;
						neighborhoods.push_back(i);
					}
				}

				if (count_neighborhood == 0) /*последовательное соединение*/
				{
					g.node_data[v].I = g.node_data[fathers[0]].I;
				}
				else /*v подключен параллельно с соседями*/
				{
					/*
					Формула вычисления силы тока при параллельном соединении
					                    I(father)
					I(v) =  ---------------------------------
						       R(v)             R(v)
						      ------  + ... +  ------  +  1
						       R(n1)            R(nm) 
					*/
					double denum{ 1. };
					for (size_t i = 0; i < count_neighborhood; i++)
					{
						denum += g.node_data[v].R / g.node_data[neighborhoods[i]].R;
					}

					g.node_data[v].I = g.node_data[fathers[0]].I / denum;
				}
			}
			else /*несколько проводов сходятся*/
			{
				size_t count_neighborhood{ 0u };
				std::vector<int> neighborhoods{};
				for (size_t i = 0; i < g.graph.size(); i++)
				{
					if (fathers[0] != i && v != i && g.graph[fathers[0]][i])
					{
						count_neighborhood++;
						neighborhoods.push_back(i);
					}
				}

				/*Сила тока дошедшая до текущей вершины равна сумма сил токов предков*/
				double I{};
				for (size_t i = 0; i < count_father; i++)
				{
					I += g.node_data[fathers[0]].I;
				}

				if (count_neighborhood == 0) /*сходятся в один*/
				{
					g.node_data[v].I = I;
				}
				else /*v подключен параллельно с соседями*/
				{
					/*
					Формула вычисления силы тока при параллельном соединении
										   I
					I(v) =  ---------------------------------
							   R(v)             R(v)
							  ------  + ... +  ------  +  1
							   R(n1)            R(nm)
					*/
					double denum{ 1. };
					for (size_t i = 0; i < count_neighborhood; i++)
					{
						denum += g.node_data[v].R / g.node_data[neighborhoods[i]].R;
					}

					g.node_data[v].I = I / denum;
				}
			}
		}
		/*конец рассчета токов*/


		plan.pop();       // удаляем ее из плана посещения
		for (size_t u = 0u; u < g.graph.size(); u++) // перебираем соседние с ней
		{ 
			if (g.graph[v][u] && !g.graph[u][u]) // если не посетили, то
			{ 
				plan.push(u);     // добавляем ее в план
				g.graph[u][u] = 1; // отмечаем, что уже не новая
			}
		}
	}
	std::cout << "BFS end" << std::endl << std::endl;

	print_force(g);
}