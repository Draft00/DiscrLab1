#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;

class Graph
{
public:

	int vertex_num, edge_num, arc_num; //число вершин, число ребер, число дуг
	bool norient; //norient = 1 – граф неориентирован, иначе ориентирован
	int num_new_ver; //номер новой вершины при ее создании
	int num_con_com; //количество компонент связности


	int** adjacency_matrix; //матрица смежности
	int** distance_matrix; //матрица расстояний
	int** inc_matrix; //матрица инцидентности
	int* eccentricity_mass; //эксцентриситеты вершин
	int* degrees_mass; //степени вершин
	int* degrees_in_mass; //степени вершин в
	int* degrees_out_mass; //степени вершин из
	int* connected_component; //массив, показывающий, в какой КС принадлежит вершина
	int girth; //обхват 

	vector<vector<int>> adjacency_list;  //Список смежности
	vector<int> leafs; //Висячие
	vector<int> isolated; //Изолированные
	vector<int> sources; //Истоки 
	vector<int> drains;  //Стоки
	vector<vector<int>> peref; //перефирийные
	vector<vector<int>> center; //центры
	vector<vector<int>> diametr;
	vector<vector<int>> radius;

	//выделение памяти 
	void malloc_matr(void);
	void malloc_inc(void);
	void delete_graph(void);

	//ввод матриц
	void get_adjacency(const char file_name[100]);  //Считывание из файла матрицы смежности
	void get_incidence(const char file_name[100]);  //Считывание из файла матрицы инцидентности
	void get_list(const char file_name[100]); //Считывание из файла списка смежности

	//преобразования в другой вид
	void adj_to_list(void);
	void adj_to_inc(void);
	void inc_to_adj(void);
	void list_to_adj(void);

	//вычисления
	void count_edges(void); //Подсчет количества ребер/дуг, когда считываем смежности
	void get_distance(void); //расстояние 
	void count_eccentricity(); //эксцентриситет
	void count_diametr_radius(); 
	void find_center(void); //поиск центров
	void count_degree(void); //определение степенной последовательности для неор
	void count_half_degree(void); //определение степенной последовательности для op
	void count_leaf_and_isolated(void); //нахожденние висячих и изолированных
	void count_sources_and_drains(void); //стоки и истоки
	void count_peref_vertex(void); //нахождение перефирийных вершин
	void count_girth(void); //обхват
	void count_con_com(void); //подсчет компонент связности

	Graph() //конструктор 
	{
		vertex_num = 0; edge_num = 0; arc_num = 0;
		norient = 1; num_new_ver = 0; girth = 0;
		num_con_com = 1;
		adjacency_matrix = nullptr;
		distance_matrix = nullptr;
		inc_matrix = nullptr;
		eccentricity_mass = nullptr;
		degrees_mass = nullptr;
		degrees_in_mass = nullptr;
		degrees_out_mass = nullptr;
		connected_component = nullptr;

	}

	~Graph() //деструктор
	{
		cout << "Сработал деструктор! " << endl;

		if (vertex_num)
		{
			//cout << "Удаляю граф!" << endl; 

			for (int i = 0; i < vertex_num + 1; i++)
			{
				delete[] distance_matrix[i];
			}
			delete[] distance_matrix;

			for (int i = 0; i < vertex_num + 1; i++)
			{
				delete[] adjacency_matrix[i];
			}
			delete[] adjacency_matrix;

			for (int i = 0; i < vertex_num; i++)
			{
				delete[] inc_matrix[i];
			}
			delete[] inc_matrix;

			delete[] degrees_mass;
			delete[] eccentricity_mass;
			delete[] degrees_in_mass;
			delete[] degrees_out_mass;
			delete[] connected_component;

			// Хотя стоит обратить внимание, что при вызове clear для основного вектора память выделенная внутренними векторами все-таки освободится.
			adjacency_list.clear();
			leafs.clear();
			isolated.clear();
			sources.clear();
			drains.clear();
			peref.clear();
			center.clear();
			diametr.clear();
			radius.clear();

			vertex_num = 0; edge_num = 0; arc_num = 0;
			norient = 1; num_new_ver = 0; girth = 0;
			num_con_com = 1;
			adjacency_matrix = nullptr;
			distance_matrix = nullptr;
			inc_matrix = nullptr;
			eccentricity_mass = nullptr;
			degrees_mass = nullptr;
			degrees_in_mass = nullptr;
			degrees_out_mass = nullptr;
			connected_component = nullptr;
		}
	}

	//вывод
	void print_adj_list(void); //список
	void print_adj_matrix(void); //матрица смежности
	void print_inc_matrix(void); //матрица инцидентности

	void print_adj_list_to_file(void); //РЕАЛИЗОВАТЬ ЮЛЯ

	void print_vertex_edg_arc(void); //вывод числа вершин, дуг или ребер
	void print_degrees(void); //вывод степенной последовательности, полустпеней захода-исхода
	void print_eccentricity(void);	//Вывод эксцентриситета вершины
	void print_diam_rad_centres(void);		//Вывод диаметра графа, радиуса и центра И ПЕРИФЕРИЙНОЙ ВЕРШИНЫ
	void print_leafs_isolated();  //Вывод висячих и изолированных вершин 
	void print_sources_drains();  //Вывод стоков и истоков 
	void print_distance_ver(int from, int to);
	void dfs(int v, int start_v, int* colors, int count, int* maxi, int predok);
	void print_girth(void);
	void print_dis_matr();
	//void dfs_for_conn(int v, int* num_con);

	//операции над матрицами
	void add_vertex(void); //добавление вершины
	void remove_vertex(int r_ver); //удаление вершины
	void add_edge(int from, int to); //д ребра
	void remove_edge(int from, int to); // у ребра
	void complement_graph(Graph* G); //дополнение графв
	void subdivision_edge(int from, int to); //подразибение ребра
	void graph_contraction(); //Стягивание графа
	void split_verticises(int v1, int v2); //Отождествление вершин
	void vertex_dublicate(int v); //Дублирование вершины 
	void multiplication_vertex(int v); //размножение вершины 
	void connect_or_union_graphs(Graph* G1, Graph* G2, int connect); //Соединение графов или объединение
	void graph_multiplication(Graph* G1, Graph* G2); //умножение графов 

	//перестройка
	void graph_rearrange_by_list(int old_vertex_num);
	void graph_rearrange_by_adj(void);
};


int count_G = 0, corr_num = 0;
Graph mass_graphs[10];

void Graph::malloc_inc(void)
{
	int N;
	if (norient) N = edge_num;
	else N = arc_num;

	inc_matrix = new int* [vertex_num];
	for (int i = 0; i < vertex_num; i++)
	{
		inc_matrix[i] = new int[N + 1];
	}
	for (int i = 0; i < vertex_num; i++)
		for (int j = 1; j < N + 1; j++)
			inc_matrix[i][j] = 0;
}

void Graph::delete_graph(void)
{

	for (int i = 0; i < vertex_num + 1; i++)
	{
		delete[] distance_matrix[i];
	}
	delete[] distance_matrix;

	for (int i = 0; i < vertex_num + 1; i++)
	{
		delete[] adjacency_matrix[i];
	}
	delete[] adjacency_matrix;

	for (int i = 0; i < vertex_num; i++)
	{
		delete[] inc_matrix[i];
	}
	delete[] inc_matrix;

	delete[] degrees_mass;
	delete[] eccentricity_mass;
	delete[] degrees_in_mass;
	delete[] degrees_out_mass;
	delete[] connected_component;

	// Хотя стоит обратить внимание, что при вызове clear для основного вектора память выделенная внутренними векторами все-таки освободится.
	adjacency_list.clear();
	leafs.clear();
	isolated.clear();
	sources.clear();
	drains.clear();
	peref.clear();
	center.clear();
	diametr.clear();
	radius.clear();

	vertex_num = 0; edge_num = 0; arc_num = 0;
	norient = 1; num_new_ver = 0; girth = 0;
	num_con_com = 1;
	adjacency_matrix = nullptr;
	distance_matrix = nullptr;
	inc_matrix = nullptr;
	eccentricity_mass = nullptr;
	degrees_mass = nullptr;
	degrees_in_mass = nullptr;
	degrees_out_mass = nullptr;
	connected_component = nullptr;

	cout << "Удаление графа - успешно!" << endl; 
}

void Graph::malloc_matr(void)
{
	//для матрицы смежности
	adjacency_matrix = new int* [vertex_num + 1];
	for (int i = 0; i < vertex_num + 1; i++)
	{
		adjacency_matrix[i] = new int[vertex_num + 1];
	}
	for (int i = 1; i < vertex_num + 1; i++)
	{
		for (int j = 1; j < vertex_num + 1; j++)
		{
			adjacency_matrix[i][j] = 0;
		}
	}

	//для матрица расстояний
	distance_matrix = new int* [vertex_num + 1];
	for (int i = 0; i < vertex_num + 1; i++)
	{
		distance_matrix[i] = new int[vertex_num + 1];
	}
	for (int i = 1; i < vertex_num + 1; i++)
	{
		for (int j = 1; j < vertex_num + 1; j++)
			distance_matrix[i][j] = 0;
	}

	//для эксцентриситета вершин
	eccentricity_mass = new int[vertex_num];
	memset(eccentricity_mass, 0, vertex_num * sizeof(int));

	degrees_mass = new int[vertex_num];
	memset(degrees_mass, 0, vertex_num * sizeof(int));

	degrees_in_mass = new int[vertex_num];
	memset(degrees_in_mass, 0, vertex_num * sizeof(int));

	degrees_out_mass = new int[vertex_num];
	memset(degrees_out_mass, 0, vertex_num * sizeof(int));

	connected_component = new int[vertex_num];
	memset(connected_component, 0, vertex_num * sizeof(int));
}

void Graph::adj_to_inc(void)
{
	int k = 1, N, j;
	if (norient) N = edge_num;
	else N = arc_num;

	malloc_inc();
	for (int i = 1; i < vertex_num + 1; i++)
		inc_matrix[i - 1][0] = adjacency_matrix[i][0];

	for (int i = 1; i < vertex_num + 1; i++)
	{
		for (norient ? j = i : j = 1; j < vertex_num + 1; j++)
		{
			for (int temp = 0; temp < adjacency_matrix[i][j]; temp++)
			{
				if (i == j)
				{
					inc_matrix[i - 1][k] = 2;
				}
				else
				{
					if (norient)
					{
						inc_matrix[i - 1][k] = 1;
						inc_matrix[j - 1][k] = 1;
					}
					else
					{
						inc_matrix[i - 1][k] = 1;
						inc_matrix[j - 1][k] = -1;
					}
				}
				k++;
				if (i == j)
					temp++;
			}
			if (k == N + 1)
				break;
		}
	}
}
void Graph::inc_to_adj(void)
{
	int N;

	if (norient) N = edge_num;
	else N = arc_num;

	int i = 0, temp;

	for (int i = 1; i < vertex_num + 1; i++)
	{
		adjacency_matrix[0][i] = inc_matrix[i - 1][0];
		adjacency_matrix[i][0] = inc_matrix[i - 1][0];
	}
	adjacency_matrix[0][0] = 0;

	for (int j = 1; j < N + 1; j++)
	{
		for (int i = 0; i < vertex_num; i++)
		{
			if (inc_matrix[i][j] == 1)
			{
				temp = i;
				for (i = i + 1; i < vertex_num; i++)
				{
					if (inc_matrix[i][j] == 1)
					{
						adjacency_matrix[temp + 1][i + 1] += 1;
						adjacency_matrix[i + 1][temp + 1] += 1;
					}
					else if (inc_matrix[i][j] == -1)
					{
						adjacency_matrix[temp + 1][i + 1] += 1;
					}
				}
			}
			else if (inc_matrix[i][j] == -1)
			{
				temp = i;
				for (i = i + 1; i < vertex_num; i++)
				{
					if (inc_matrix[i][j] == 1)
						adjacency_matrix[i + 1][temp + 1] += 1;
				}
			}
			else if (inc_matrix[i][j] == 2)
			{
				adjacency_matrix[i + 1][i + 1] += 2;
			}
		}
	}
}

void Graph::adj_to_list()
{
	for (int i = 1; i < vertex_num + 1; i++)
	{
		adjacency_list.push_back(vector<int>()); 
		adjacency_list[i - 1].push_back(adjacency_matrix[i][0]);
		for (int j = 1; j < vertex_num + 1; j++)
		{
			for (int k = 0; k < adjacency_matrix[i][j]; k++)
			{
				adjacency_list[i - 1].push_back(adjacency_matrix[j][0]);
				if (i == j)
					//break;
					k++;
			}
		}
	}
}

void Graph::list_to_adj(void)
{
	for (int i = 1; i < vertex_num + 1; i++)
	{
		adjacency_matrix[0][i] = adjacency_list[i - 1][0];
		adjacency_matrix[i][0] = adjacency_list[i - 1][0];
	}
	adjacency_matrix[0][0] = 0;
	for (int i = 0; i < vertex_num; i++)
	{
		for (int j = 1; j < adjacency_list[i].size(); j++)
		{
			if (adjacency_list[i][j] == adjacency_list[i][0])
				adjacency_matrix[i + 1][i + 1] += 2; 
			else
			{
				int num = 1;
				while (adjacency_matrix[0][num] != adjacency_list[i][j]) num++;
				adjacency_matrix[i + 1][num] += 1;
			}
		}
	}
}

void Graph::get_distance()
{
	int j, v, num;

	distance_matrix[0][0] = 0;
	for (int i = 1; i < vertex_num + 1; i++)
	{
		distance_matrix[i][0] = adjacency_matrix[i][0];
		distance_matrix[0][i] = adjacency_matrix[i][0];
	}

	for (int i = 1; i < vertex_num + 1; i++)
	{
		vector<int> flag;
		queue<int> q;

		flag.clear();
		for (j = 0; j < vertex_num; j++)
		{
			flag.push_back(0);
		}
		q.push(i - 1);
		flag[i - 1] = 1;
		distance_matrix[i][i] = 0;
		while (!q.empty())
		{
			v = q.front();
			q.pop();
			for (j = 1; j < adjacency_list[v].size(); j++)
			{
				num = 1; //в adj_m[0][0] стоит ноль
				while (num < vertex_num && adjacency_matrix[0][num] != adjacency_list[v][j]) num++;
				num--;

				if (!flag[num])
				{
					q.push(num);
					distance_matrix[i][num + 1] = distance_matrix[i][v  + 1] + 1;
					flag[num] = 1;
				}
			}
		}
	}
}

void Graph::get_adjacency(const char file_name[100])
{
	FILE* fin = fopen(file_name, "r");
	if (!fin)
	{
		cout << "Error open file!" << endl;
		count_G--;
		return;
	}
	int temp;
	fscanf(fin, "%d", &temp);
	if (temp == 0)
		norient = true;
	else norient = false;
	temp = fgetc(fin);

	char buf[100] = { 0 };
	fgets(buf, 100, fin);
	for (int i = 0; ; i++)
	{
		if (buf[i] == ' ')
			vertex_num++;
		else if (buf[i] == '\n')
			break;
	}
	vertex_num++;
	fseek(fin, 2, SEEK_SET);

	malloc_matr();

	for (int i = 1; i < vertex_num + 1; i++)
	{
		for (int j = 1; j < vertex_num + 1; j++)
		{
			fscanf(fin, "%d", &adjacency_matrix[i][j]);
		}
	}
	fclose(fin);
	adjacency_matrix[0][0] = 0;
	for (int i = 1; i < vertex_num + 1; i++)
	{
		adjacency_matrix[i][0] = i;
		adjacency_matrix[0][i] = i;
	}

	//num_new_ver = vertex_num + 1;
	num_new_ver = adjacency_matrix[0][vertex_num] + 1;

	//Обязательно! перед преобразованием в другой вид
	count_edges(); //количество петель и ребер для Inc
	
	//только после количества ребер/дуг!!!! после проверки ориентированности!
	adj_to_list();  //преобразование в список 
	adj_to_inc();
	
	get_distance(); //найти расстояние
	count_con_com();
	count_eccentricity(); //после расстояние - экс
	count_diametr_radius(); // после экс - диаметр и радиус
	find_center(); //зная радиус можно найти центр

	if (norient) count_degree(); //определение степенной последовательности
	else
	{
		count_half_degree(); //степ зах-исхода
		count_sources_and_drains();
	}
	
	count_leaf_and_isolated();
	count_peref_vertex();

	cout << "Граф №" << corr_num + 1 << " успешно прочитан!" << endl;
}
void Graph::get_incidence(const char file_name[100])
{
	char buf[100];
	int i = 0, N = 0;
	FILE* fin;
	fin = fopen(file_name, "r");
	if (!fin)
	{
		printf("File not exist\n");
		count_G--;
		return;
	}
	int temp;
	fscanf(fin, "%d", &temp);

	if (temp == 0)
		norient = true;
	else norient = false;

	temp = fgetc(fin);
	fgets(buf, 100, fin);
	while (buf[i] != '\n')
	{
		if (buf[i] != ' ' && buf[i] != '-')
			N++;
		i++;
	}
	/*if (ory) arc_num = N;
	else edge_num = N;*/
	vertex_num++;
	while (fgets(buf, 100, fin))
	{
		vertex_num++;
	}

	inc_matrix = new int* [vertex_num];
	for (int i = 0; i < vertex_num; i++)
	{
		inc_matrix[i] = new int[N + 1];
	}
	for (int i = 0; i < vertex_num; i++)
		for (int j = 1; j < N + 1; j++)
			inc_matrix[i][j] = 0;

	fseek(fin, 2, SEEK_SET);

	while (!feof(fin))
	{
		for (int i = 0; i < vertex_num; i++)
		{
			for (int j = 1; j < N + 1; j++)
			{
				fscanf(fin, "%d", &inc_matrix[i][j]);
			}
		}
	}
	fclose(fin);

	for (int i = 0; i < vertex_num; i++)
	{
		inc_matrix[i][0] = i + 1;
	}

	if (norient) edge_num = N;
	else arc_num = N;

	malloc_matr();

	inc_to_adj(); //получили смежности
	//num_new_ver = vertex_num + 1;
	num_new_ver = adjacency_matrix[0][vertex_num] + 1;
	adj_to_list(); //получили список
	if (norient) count_degree();  //степенная последовательность
	else
	{
		count_half_degree();
		count_sources_and_drains();
	}
	get_distance(); //найти расстояние
	count_con_com();
	count_eccentricity(); //после расстояние - экс
	count_diametr_radius(); // после экс - диаметр и радиус
	find_center(); //зная радиус можно найти центр
	count_leaf_and_isolated();
	count_peref_vertex();
}
void Graph::get_list(const char file_name[100])
{
	FILE* fin;
	int c = -1, line = 0;
	fin = fopen(file_name, "r");
	if (!fin)
	{
		printf("File not exist\n");
		count_G--;
		return;
	}

	int temp;

	fscanf(fin, "%d", &temp);
	if (temp == 0)
		norient = true;
	else norient = false;
	temp = fgetc(fin);

	while ((c = fgetc(fin)) != EOF)
	{
		if (c == '{')
		{
			adjacency_list.push_back(vector<int>());
			fscanf_s(fin, "%d", &c);
			adjacency_list[line].push_back(c);
			//(*(adjacency_list.end() - 1)).push_back(c);
			c = fgetc(fin);
			if (c != '}')
			{
				fseek(fin, -1, SEEK_CUR);
				while (c != '}')
				{
					fscanf_s(fin, "%d", &c);
					adjacency_list[line].push_back(c);
					c = fgetc(fin);
				}
			}
			line++;
		}
	}
	fclose(fin);

	vertex_num = adjacency_list.size();
	malloc_matr();


	list_to_adj();

	//num_new_ver = vertex_num + 1;
	num_new_ver = adjacency_matrix[0][vertex_num] + 1;
	count_edges(); //перед осзданием матрицы инцидентности

	adj_to_inc();

	if (norient) count_degree();  //степенная последовательность
	else {
		count_half_degree();
		count_sources_and_drains(); //истоки стоки
	}
	get_distance(); //найти расстояние
	count_con_com();
	count_eccentricity(); //после расстояние - экс
	count_diametr_radius(); // после экс - диаметр и радиус
	find_center(); //зная радиус можно найти центр
	count_leaf_and_isolated();
	count_peref_vertex();

}

void Graph::count_edges()
{
	int i, j;

	for (i = 1; i < vertex_num + 1; i++)
	{
		for (norient ? j = i + 1 : j = 1; j < vertex_num + 1; j++)
		{
			if (adjacency_matrix[i][j] && i != j)
			{
				if (norient) edge_num += adjacency_matrix[i][j];
				else arc_num += adjacency_matrix[i][j];
			}
		}
	}
	for (int i = 1; i < vertex_num + 1; i++)
	{
		if (adjacency_matrix[i][i])
		{
			if (norient) edge_num += adjacency_matrix[i][i] / 2;
			else arc_num += adjacency_matrix[i][i] / 2;
		}
	}
}
void Graph::find_center(void)
{
	for (int i = 0; i < num_con_com; i++)
	{
		center.push_back(vector<int>());
	}
	for (int i = 0; i < vertex_num; i++)
	{
		if (eccentricity_mass[i] == radius[connected_component[i] - 1][0])
			center[connected_component[i] - 1].push_back(i + 1);
	}
}
void Graph::count_eccentricity()
{
	for (int i = 1; i < vertex_num + 1; i++)
	{
		int max = 0;
		for (int j = 1; j < vertex_num + 1; j++)
		{
			if (distance_matrix[i][j] > max && i != j)
				max = distance_matrix[i][j];
		}
		eccentricity_mass[i - 1] = max;
	}
}
void Graph::count_diametr_radius()
{
	for (int i = 0; i < num_con_com; i++)
	{
		diametr.push_back(vector<int>());
		radius.push_back(vector<int>());
	}
	int* max; int* min;
	min = new int[num_con_com]; 
	for (int i = 0; i < num_con_com; i++)
		min[i] = INT_MAX;
	max = new int[num_con_com]; memset(max, 0, num_con_com * sizeof(int));

	for (int i = 0; i < vertex_num; i++)
	{
		if (eccentricity_mass[i] > max[connected_component[i] - 1])
			max[connected_component[i] - 1] = eccentricity_mass[i];
		if (eccentricity_mass[i] < min[connected_component[i] - 1])
			min[connected_component[i] - 1] = eccentricity_mass[i];
	}
	
	for (int i = 0; i < num_con_com; i++)
	{
		diametr[i].push_back(max[i]);
		radius[i].push_back(min[i]);
	}
}
void Graph::count_degree()
{
	for (int i = 0; i < vertex_num; i++)
	{
		for (int j = 1; j < edge_num + 1; j++)
		{
			degrees_mass[i] += inc_matrix[i][j];
		}
	}
}
void Graph::count_half_degree()
{
	for (int i = 0; i < vertex_num; i++)
	{
		for (int j = 1; j < arc_num + 1; j++)
		{
			if (inc_matrix[i][j] > 0)
				degrees_out_mass[i] += inc_matrix[i][j];
			else if (inc_matrix[i][j] < 0)
				degrees_in_mass[i] += abs(inc_matrix[i][j]);
		}
	}
}
void Graph::count_leaf_and_isolated()
{
	if (norient)
	{
		for (int i = 0; i < vertex_num; i++)
		{
			if (degrees_mass[i] == 1) leafs.push_back(i + 1);
			if (degrees_mass[i] == 0) isolated.push_back(i + 1);
		}
	}
	else
	{
		for (int i = 0; i < vertex_num; i++)
		{
			if ((degrees_in_mass[i] + degrees_out_mass[i]) == 1) leafs.push_back(i + 1);
			if ((degrees_in_mass[i] + degrees_out_mass[i]) == 0) isolated.push_back(i + 1);
		}
	}
}
void Graph::count_sources_and_drains()
{
	for (int i = 0; i < vertex_num; i++)
	{
		if (degrees_in_mass[i] && !degrees_out_mass[i])
			drains.push_back(i + 1);
		if (!degrees_in_mass[i] && degrees_out_mass[i])
			sources.push_back(i + 1);
	}
}
void Graph::count_peref_vertex(void)
{
	for (int i = 0; i < num_con_com; i++)
	{
		peref.push_back(vector<int>());
	}
	for (int i = 0; i < vertex_num; i++)
	{
		if (eccentricity_mass[i] == diametr[connected_component[i] - 1][0])
			peref[connected_component[i] - 1].push_back(i + 1);
	}
	/*for (int i = 0; i < vertex_num; i++)
	{
		if (eccentricity_mass[i] == diametr)
			peref.push_back(i + 1);
	}*/
}
void Graph::count_girth(void)
{
	for (int i = 1; i < vertex_num + 1; i++)
	{
		if (adjacency_matrix[i][i])
		{
			girth = 1;
			return;
		}
	}
	int* colors;
	int mini = INT_MAX;
	colors = new int[vertex_num];

	int count = 1;
	for (int i = 1; i < vertex_num + 1; i++)
	{
		memset(colors, 0, vertex_num*sizeof(int));

		dfs(i, i, colors, count, &mini, -1);
	}
	girth = mini - 1; 
}
void Graph::dfs(int v, int start_v, int* colors, int count, int* mini, int predok)
{
	if (colors[v - 1])
	{
		if (v == start_v)
		{
			if (norient && adjacency_matrix[predok][v] == 1 && count == 3)
				return;
			if (count < *mini)
				* mini = count;
		}
		return; 
	}

	colors[v - 1] = 1;
	predok = v;
	for (int i = 1; i < vertex_num + 1; i++)
	{
		if (adjacency_matrix[v][i])
		{
			//ВОТ ТУТ ТОЖЕ КОПИЯ
			dfs(i, start_v, colors, count + 1, mini, predok);
		}
	}
	colors[v - 1] = 0;
}

void Graph::count_con_com(void)
{
	connected_component = new int[vertex_num];
	memset(connected_component, 0, vertex_num * sizeof(int));
	
	int num_com = 1; 

		for (int i = 1; i < vertex_num + 1; i++)
		{
			if (!connected_component[i - 1])
			{
				connected_component[i - 1] = num_com;
				num_com++;

				for (int j = 1; j < vertex_num + 1; j++)
				{
					if (!connected_component[j - 1])
					{
						if (distance_matrix[i][j])
						{
							if (norient) connected_component[j - 1] = connected_component[i - 1];
							else
							{
								if (distance_matrix[j][i])
									connected_component[j - 1] = connected_component[i - 1];
							}
						}
					}
				}
			}
		}

	num_con_com = num_com - 1;
}

void Graph::print_adj_matrix(void)
{
	cout << "Матрица смежности имеет вид: " << endl;
	for (int i = 0; i < vertex_num + 1; i++)
	{
		for (int j = 0; j < vertex_num + 1; j++)
		{
			cout << adjacency_matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void Graph::print_vertex_edg_arc(void)
{
	cout << "Число вершин графа: " << vertex_num << endl;
	if (norient) cout << "Число ребер графа: " << edge_num << endl;
	else cout << "Число дуг графа: " << arc_num << endl;
}
void Graph::print_adj_list(void)
{
	for (int i = 0; i < adjacency_list.size(); i++)
	{
		cout << "{" << adjacency_list[i][0];
		for (int j = 1; j < adjacency_list[i].size(); j++)
			cout << " " << adjacency_list[i][j];
		cout << "}" << endl;
	}
	cout << endl;
}
void Graph::print_inc_matrix(void)
{
	int N;
	if (norient) N = edge_num;
	else N = arc_num;

	cout << "Матрица инцидентности имеет вид: " << endl;
	for (int i = 0; i < vertex_num; i++)
	{
		for (int j = 0; j < N + 1; j++)
		{
			cout << inc_matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void Graph::print_dis_matr()
{
	for (int i = 0; i < vertex_num + 1; i++)
	{
		for (int j = 0; j < vertex_num + 1; j++)
		{
			if ((i != j) && !distance_matrix[i][j])
				cout << "-" << " ";
			else cout << distance_matrix[i][j] << " ";
		}
		cout << endl;
	}
}
void Graph::print_eccentricity(void)
{
	for (int i = 0; i < vertex_num; i++)
		cout << i + 1 << " - " << eccentricity_mass[i] << endl;
}
void Graph::print_diam_rad_centres(void)
{
	cout << "Вершина - принадлежности к КС" << endl; 

	for (int i = 0; i < vertex_num; i++)
	{
		cout << adjacency_matrix[0][i + 1] << " - " << connected_component[i] << endl; 
	}
	for (int i = 0; i < num_con_com; i++)
	{
		cout << "Характеристики для компоненты связности № " << i + 1 << endl;
		cout << "Диаметр: " << diametr[i][0] << endl;
		cout << "Радиус: " << radius[i][0] << endl;
		cout << "Центр(ы): ";
		for (int k = 0; k < center[i].size(); k++)
		{
			cout << center[i][k] << " ";
		}
		cout << endl; 
		cout << "Периферийные вершины: ";
		for (int k = 0; k < peref[i].size(); k++)
		{
			cout << peref[i][k] << " ";
		}
		cout << endl;
	}
	/*cout << "Диаметр графа: " << diametr << endl;
	cout << "Радиус графа: " << radius << endl;
	cout << "Центр(ы) графа: ";
	if (center.size())
	{
		for (int i = 0; i < center.size(); i++)
		{
			cout << center[i] << " ";
		}
		cout << endl;
	}
	else cout << "Центр(ы) отсутствуют." << endl;
	if (peref.size())
	{
		cout << "Перефирийные вершины: ";
		for (int i = 0; i < peref.size(); i++)
			cout << peref[i] << " ";
		cout << endl;
	}
	else cout << "Перефирийный вершины отсутствуют." << endl;*/
}
void Graph::print_degrees(void)
{
	if (norient)
	{
		cout << "Степенная последовательность графа: ";
		for (int i = 0; i < vertex_num; i++)
			cout << degrees_mass[i] << " ";
		cout << endl;
	}
	else
	{
		cout << "Полустепени захода: ";
		for (int i = 0; i < vertex_num; i++)
			cout << degrees_in_mass[i] << " ";
		cout << endl;

		cout << "Полустепени исхода: ";
		for (int i = 0; i < vertex_num; i++)
			cout << degrees_out_mass[i] << " ";
		cout << endl;
	}
}
void Graph::print_leafs_isolated()
{
	if (isolated.size())
	{
		cout << "Изолированные вершины: ";
		for (int i = 0; i < isolated.size(); i++)
			cout << isolated[i] << " ";
		cout << endl;
	}
	else cout << "Нет изолированных вершин." << endl;

	if (leafs.size())
	{
		cout << "Висячие вершины: ";
		for (int i = 0; i < leafs.size(); i++)
			cout << leafs[i] << " ";
		cout << endl;
	}
	else cout << "Нет висячих вершин." << endl;
}
void Graph::print_sources_drains()
{
	if (norient)
	{
		cout << "Этот граф неориентирован." << endl;
		return;
	}
	if (sources.size())
	{
		cout << "Истоки: ";
		for (int i = 0; i < sources.size(); i++)
			cout << sources[i] << " ";
		cout << endl;
	}
	else cout << "Истоков нет." << endl;

	if (drains.size())
	{
		cout << "Стоки: ";
		for (int i = 0; i < drains.size(); i++)
			cout << drains[i] << " ";
		cout << endl;
	}
	else cout << "Стоков нет. " << endl;
}
void Graph::print_distance_ver(int from, int to)
{
	int from_index = -1, to_index = -1; 
	for (int j = 1; j < vertex_num + 1; j++)
	{
		if (adjacency_matrix[0][j] == from)
			from_index = j;
		if (adjacency_matrix[0][j] == to)
			to_index = j;
	}
	if (from_index == -1)
	{ cout << "Первой вершины не существует." << endl; return; }
	if (to_index == -1)
	{ cout << "Второй вершины не существует." << endl; return; }
	cout << "Расстояние от вершины " << from << " до вершины " << to << " = ";
	if (distance_matrix[from_index][to_index])
	{
		cout << distance_matrix[from_index][to_index] << endl;
	}
	else
	{
		if (from == to)
			cout << 0 << endl;
		else cout << "inf." << endl; 
	}
}

void Graph::print_girth(void)
{
	if (girth)
	{
		cout << "Обхват графа составляет: " << girth << endl;
	}
	else cout << "Граф ацикличен." << endl;
}
void Graph::print_adj_list_to_file(void)
{
	ofstream fout;
	fout.open("output.txt");
	
	for (int i = 0; i < adjacency_list.size(); i++)
	{
		fout << "{";
		fout << adjacency_list[i][0];
		for (int j = 1; j < adjacency_list[i].size(); j++)
		{
			fout << " " << adjacency_list[i][j];
		}
		fout << "}" << endl; 
	}
	fout.close();
}
void Graph::graph_rearrange_by_list(int old_vertex_num)
{
	for (int i = 0; i < old_vertex_num + 1; i++)
	{
		delete[] distance_matrix[i];
	}
	delete[] distance_matrix;

	for (int i = 0; i < old_vertex_num + 1; i++)
	{
		delete[] adjacency_matrix[i];
	}
	delete[] adjacency_matrix;

	for (int i = 0; i < old_vertex_num; i++)
	{
		delete[] inc_matrix[i];
	}
	delete[] inc_matrix;

	adjacency_matrix = nullptr;
	inc_matrix = nullptr;
	distance_matrix = nullptr;

	delete[] degrees_mass;
	delete[] eccentricity_mass;
	delete[] degrees_in_mass;
	delete[] degrees_out_mass;
	delete[] connected_component;

	leafs.clear();
	isolated.clear();
	sources.clear();
	drains.clear();
	peref.clear();
	center.clear();
	diametr.clear();
	radius.clear();

	edge_num = 0;
	arc_num = 0;

	malloc_matr();
	list_to_adj();

	count_edges(); //перед осзданием матрицы инцидентности

	adj_to_inc();

	if (norient) count_degree();  //степенная последовательность
	else {
		count_half_degree();
		count_sources_and_drains(); //истоки стоки
	}

	get_distance(); //найти расстояние
	count_con_com();
	count_eccentricity(); //после расстояние - экс
	count_diametr_radius(); // после экс - диаметр и радиус
	find_center(); //зная радиус можно найти центр
	count_leaf_and_isolated();
	count_peref_vertex();
}
void Graph::graph_rearrange_by_adj(void)
{
	for (int i = 0; i < vertex_num + 1; i++)
	{
		delete[] distance_matrix[i];
	}
	delete[] distance_matrix;

	for (int i = 0; i < vertex_num; i++)
	{
		delete[] inc_matrix[i];
	}
	delete[] inc_matrix;

	inc_matrix = nullptr;
	distance_matrix = nullptr;

	delete[] degrees_mass;
	delete[] eccentricity_mass;
	delete[] degrees_in_mass;
	delete[] degrees_out_mass;
	delete[] connected_component;

	adjacency_list.clear();
	leafs.clear();
	isolated.clear();
	sources.clear();
	drains.clear();
	peref.clear();
	center.clear();
	diametr.clear();
	radius.clear();

	distance_matrix = new int* [vertex_num + 1];
	for (int i = 0; i < vertex_num + 1; i++)
	{
		distance_matrix[i] = new int[vertex_num + 1];
	}
	for (int i = 1; i < vertex_num + 1; i++)
	{
		for (int j = 1; j < vertex_num + 1; j++)
			distance_matrix[i][j] = 0;
	}
	//malloc для Inc в adj_to_inc
	//для эксцентриситета вершин
	eccentricity_mass = new int[vertex_num];
	memset(eccentricity_mass, 0, vertex_num * sizeof(int));

	degrees_mass = new int[vertex_num];
	memset(degrees_mass, 0, vertex_num * sizeof(int));

	degrees_in_mass = new int[vertex_num];
	memset(degrees_in_mass, 0, vertex_num * sizeof(int));

	degrees_out_mass = new int[vertex_num];
	memset(degrees_out_mass, 0, vertex_num * sizeof(int));

	connected_component = new int[vertex_num];
	memset(connected_component, 0, vertex_num * sizeof(int));

	adj_to_inc();
	adj_to_list();

	if (norient) count_degree();  //степенная последовательность
	else {
		count_half_degree();
		count_sources_and_drains(); //истоки стоки
	}

	get_distance(); //найти расстояние
	count_con_com();
	count_eccentricity(); //после расстояние - экс
	count_diametr_radius(); // после экс - диаметр и радиус
	find_center(); //зная радиус можно найти центр
	count_leaf_and_isolated();
	count_peref_vertex();
}

void Graph::add_vertex()
{
	adjacency_list.push_back(vector<int>());
	adjacency_list[vertex_num].push_back(num_new_ver); 

	int new_v, index_new_v = -1;

	if (norient)
	{
		cout << "Добавление вершины № " << num_new_ver << ". Введите смежные ей вершины !через ENTER. Конец ввода - 0" << endl;
		new_v = 1;
		cout << ">>>";
		cin >> new_v;
		while (new_v != 0)
		{
			for (int i = 0; i < adjacency_list.size(); i++)
			{
				if (new_v == adjacency_list[i][0])
					index_new_v = i;
			}
			if (index_new_v == -1) cout << "Такой вершины не существует" << endl;
			else
			{
				if (index_new_v != vertex_num)
				{
					adjacency_list[index_new_v].push_back(num_new_ver);
				}
				int temp;
				for (temp = 1; temp < adjacency_list[vertex_num].size(); temp++) //чтобы по порядку было. не 7 5 4, а 7 4 5
				{
					if (adjacency_list[vertex_num][temp] >= new_v) //изменила на >= 
						break; 
				}
				adjacency_list[vertex_num].emplace(adjacency_list[vertex_num].begin() + temp, adjacency_list[index_new_v][0]);
			}
			cout << ">>>";
			cin >> new_v;
		}
	}
	else
	{
		cout << "Добавление вершины № " << num_new_ver << ". Введите смежные ей вершины !через ENTER. Конец ввода - 0" << endl;
		cout << "Граф - ОРИЕНТИРОВАННЫЙ. Введите смежную вершину со знаком минус, если дуга, инцидентная новой вершине и вводимой, входит в вводимую, иначе - без знака." << endl;
		cout << "Знак минус = из новая вершина в вводимая, но не обратный" << endl;
		new_v = 1;
		cout << ">>>";
		cin >> new_v;
		while (new_v != 0)
		{
			for (int i = 0; i < adjacency_list.size(); i++)
			{
				if (abs(new_v) == adjacency_list[i][0])
					index_new_v = i;
			}
			if (index_new_v == -1) cout << "Такой вершины не существует" << endl;
			else
			{
				if (new_v > 0)
					adjacency_list[index_new_v].push_back(num_new_ver);
				else
				{
					int temp;
					for (temp = 1; temp < adjacency_list[vertex_num].size(); temp++) //чтобы по порядку было. не 7 5 4, а 7 4 5
					{
						if (adjacency_list[vertex_num][temp] > new_v)
							break;
					}
					adjacency_list[vertex_num].emplace(adjacency_list[vertex_num].begin() + temp, adjacency_list[index_new_v][0]);
				}
			}
			cout << ">>>";
			cin >> new_v;
		}
	}
	num_new_ver++; vertex_num++;
	cout << "Добавление вершины - успешно!" << endl;
	graph_rearrange_by_list(vertex_num - 1);
}
void Graph::remove_vertex(int r_ver)
{
	int index_r_ver = -1;
	for (int i = 0; i < adjacency_list.size(); i++)
	{
		if (adjacency_list[i][0] == r_ver)
			index_r_ver = i;
	}
	if (index_r_ver == -1)
	{ cout << "Такой вершины не существует" << endl; return; }
	else
	{
		for (int i = 0; i < adjacency_list.size(); i++)
		{
			for (int j = 1; j < adjacency_list[i].size(); j++)
			{
				if (adjacency_list[i][j] == r_ver)
				{
					adjacency_list[i].erase(adjacency_list[i].begin() + j);
					j--;
				}
			}
		}
		adjacency_list[index_r_ver].clear();
		adjacency_list.erase(adjacency_list.begin() + index_r_ver);
	}
	vertex_num--;

	cout << "Удаление вершины - успешно!" << endl; 
	graph_rearrange_by_list(vertex_num + 1);
}
void Graph::add_edge(int from, int to)
{
	int index_to = -1, index_from = -1;
	for (int i = 1; i < vertex_num + 1; i++)
	{
		if (from == adjacency_matrix[i][0])
			index_from = i;
		if (to == adjacency_matrix[i][0])
			index_to = i;
	}
	if (index_from == -1)
	{ cout << "Первой вершины не существует." << endl; return; }
	if (index_to == -1)
	{ cout << "Второй вершины не существует." << endl; return; }

	adjacency_matrix[index_from][index_to]++;
	if (norient) adjacency_matrix[index_to][index_from]++;

	if (norient) edge_num++;
	else arc_num++;

	cout << "Добавление ребра/дуги - успешно!" << endl;
	graph_rearrange_by_adj();
}
void Graph::remove_edge(int from, int to)
{
	int index_to = -1, index_from = -1;
	for (int j = 1; j < vertex_num + 1; j++)
	{
		if (adjacency_matrix[0][j] == from)
			index_from = j;
		if (adjacency_matrix[0][j] == to)
			index_to = j;
	}
	if (index_from == -1)
	{ cout << "Первой вершины не существует." << endl; return; }
	if (index_to == -1)
	{ cout << "Второй вершины не существует." << endl; return; }
	if (adjacency_matrix[index_from][index_to] == 0)
	{ cout << "Между данными вершинами не существует ребра/дуги. Попробуйте снова. " << endl; return; }
	adjacency_matrix[index_from][index_to]--;
	if (norient) adjacency_matrix[index_to][index_from]--;
	if (norient) edge_num--;
	else arc_num--;
	cout << "Удаление ребра/дуги - успешно!" << endl;
	graph_rearrange_by_adj();
}
void Graph::complement_graph(Graph* G)
{
	norient = (*G).norient;
	vertex_num = (*G).vertex_num;
	num_new_ver = vertex_num + 1;

	malloc_matr();
	for (int i = 1; i < vertex_num + 1; i++)
	{
		adjacency_matrix[i][0] = (*G).adjacency_matrix[i][0];
		adjacency_matrix[0][i] = (*G).adjacency_matrix[0][i];
	}
	adjacency_matrix[0][0] = 0;

	for (int i = 1; i < vertex_num + 1; i++)
	{
		for (int j = 1; j < vertex_num + 1; j++)
		{
			if (i == j)
				adjacency_matrix[i][j] = 0;
			else
			{
				if ((*G).adjacency_matrix[i][j])
					adjacency_matrix[i][j] = 0;
				else adjacency_matrix[i][j] = 1;
			}
		}
	}

	count_edges(); //количество петель и ребер для Inc

//только после количества ребер/дуг!!!! после проверки ориентированности!
	adj_to_list();  //преобразование в список 
	adj_to_inc();

	get_distance(); //найти расстояние
	count_con_com();
	count_eccentricity(); //после расстояние - экс
	count_diametr_radius(); // после экс - диаметр и радиус
	find_center(); //зная радиус можно найти центр

	if (norient) count_degree(); //определение степенной последовательности
	else
	{
		count_half_degree(); //степ зах-исхода
		count_sources_and_drains();
	}

	count_leaf_and_isolated();
	count_peref_vertex();
}
void Graph::subdivision_edge(int from, int to)
{
	/*if (from == to)
	{
		cout << "Это не ребро." << endl; return; 
	}*/
	if (norient)
	{
		int index_to = -1, index_from = -1;
		for (int j = 1; j < vertex_num + 1; j++)
		{
			if (adjacency_matrix[0][j] == from)
				index_from = j;
			if (adjacency_matrix[0][j] == to)
				index_to = j;
		}
		if (index_from == -1)
		{ cout << "Первой вершины не существует." << endl; return; }
		if (index_to == -1)
		{ cout << "Второй вершины не существует." << endl; return; }
		if (adjacency_matrix[index_from][index_to] == 0)
		{ cout << "Между данными вершинами не существует ребра. Попробуйте снова. " << endl; return; }

		remove_edge(from, to);

		adjacency_list[index_from - 1].push_back(num_new_ver);
		adjacency_list[index_to - 1].push_back(num_new_ver);

		adjacency_list.push_back(vector<int>());
		adjacency_list[vertex_num].push_back(num_new_ver);
		if (from > to)
		{
			adjacency_list[vertex_num].push_back(to);
			adjacency_list[vertex_num].push_back(from);
		}
		else
		{
			adjacency_list[vertex_num].push_back(from);
			adjacency_list[vertex_num].push_back(to);
		}
		vertex_num++; num_new_ver++;
		graph_rearrange_by_list(vertex_num - 1);

		cout << "Добавление новых ребер в подразбиении - успешно!" << endl;
		cout << "Подразбиение ребра - успешно!" << endl;
	}
	else
	{
		cout << "Невозможно, граф - ориентированный." << endl; return;
	}
}

void Graph::split_verticises(int v1, int v2)
{
	int index_v1 = -1, index_v2 = -1;
	vector <int> ver_for_connection; 
	ver_for_connection.clear();
	ver_for_connection.push_back(num_new_ver);

	for (int i = 0; i < adjacency_list.size(); i++)
	{
		if (v1 == adjacency_list[i][0])
			index_v1 = i;
		if (v2 == adjacency_list[i][0])
			index_v2 = i;
	}
	if (index_v1 == -1)
	{
		cout << "Первой вершины не существует." << endl; return;
	}
	if (index_v2 == -1)
	{
		cout << "Второй вершины не существует." << endl; return;
	}

	for (int j = 1; j < adjacency_list[index_v1].size(); j++)
	{
		if (adjacency_list[index_v1][j] != adjacency_list[index_v1][0] && adjacency_list[index_v1][j] != v2) //петли не нужны
			if (find(ver_for_connection.begin(), ver_for_connection.end(), adjacency_list[index_v1][j]) == ver_for_connection.end())
			{
				ver_for_connection.push_back(adjacency_list[index_v1][j]);
			}

	}
	for (int j = 1; j < adjacency_list[index_v2].size(); j++)
	{
		if (adjacency_list[index_v2][j] != adjacency_list[index_v2][0] && adjacency_list[index_v2][j] != v1)
		{
			if (find(ver_for_connection.begin(), ver_for_connection.end(), adjacency_list[index_v2][j]) == ver_for_connection.end()) //index_v2 ИЗМЕНИЛА!!!
			{
				int temp2;
				for (temp2 = 1; temp2 < ver_for_connection.size(); temp2++) //чтобы по порядку было. не 7 5 4, а 7 4 5
				{
					if (ver_for_connection[temp2] > adjacency_list[index_v2][j])
						break;
				}
				ver_for_connection.emplace(ver_for_connection.begin() + temp2, adjacency_list[index_v2][j]);
				//ver_for_connection.push_back(adjacency_list[index_v2][j]);
			}
		}
	}
	for (int i = 0; i < adjacency_list.size(); i++)
	{
		int flag = 0;
		for (int j = 1; j < adjacency_list[i].size(); j++)
		{
			if (adjacency_list[i][0] != v1 && adjacency_list[i][0] != v2)
			{
				if (adjacency_list[i][j] == v1 || adjacency_list[i][j] == v2)
				{
					adjacency_list[i].erase(adjacency_list[i].begin() + j);
					if (!flag)
					{
						adjacency_list[i].push_back(num_new_ver);
						flag = 1;
					}
					j--;
				}
			}
		}
	}

	adjacency_list[index_v1].clear();
	adjacency_list.erase(adjacency_list.begin() + index_v1);
	for (int i = 0; i < adjacency_list.size(); i++)
	{
		if (adjacency_list[i][0] == v2)
			index_v2 = i;
	}
	adjacency_list[index_v2].clear();
	adjacency_list.erase(adjacency_list.begin() + index_v2);
	
	vertex_num -= 2;

	adjacency_list.push_back(vector<int>());
	adjacency_list[vertex_num] = ver_for_connection;

	//
	ver_for_connection.clear();
	//

	vertex_num++; num_new_ver++;
	graph_rearrange_by_list(vertex_num - 1);
}

void Graph::vertex_dublicate(int v)
{
	int index_v = -1;
	for (int i = 0; i < adjacency_list.size(); i++)
	{
		if (v == adjacency_list[i][0])
			index_v = i;
	}
	if (index_v == -1)
	{
		cout << "Вершины не существует." << endl; return;
	}

	adjacency_list.push_back(vector<int>());
	adjacency_list[vertex_num].push_back(num_new_ver);

	for (int j = 1; j < adjacency_list[index_v].size(); j++)
	{
		if (adjacency_list[index_v][j] != v) //петли от дублируемой вершины не нужны
		{
			if (find(adjacency_list[vertex_num].begin(), adjacency_list[vertex_num].end(), adjacency_list[index_v][j]) == adjacency_list[vertex_num].end()) //кратные ребра тоже
				adjacency_list[vertex_num].push_back(adjacency_list[index_v][j]);
		}
	}
	for (int i = 0; i < adjacency_list.size() - 1; i++) //для орграфа тоже работает
	{
		for (int j = 1; j < adjacency_list[i].size(); j++)
		{
			if (adjacency_list[i][j] == v && adjacency_list[i][0] != v)
			{
				if (find(adjacency_list[i].begin(), adjacency_list[i].end(), num_new_ver) == adjacency_list[i].end())
					adjacency_list[i].push_back(num_new_ver);
			}
		}
	}
	vertex_num++; num_new_ver++;
	graph_rearrange_by_list(vertex_num - 1);
	cout << "Дублирование вершин - успешно!" << endl;
}
void Graph::multiplication_vertex(int v)
{
	vertex_dublicate(v);
	add_edge(v, num_new_ver - 1);
	cout << "Разможение вершин - успешно!" << endl;
}
void Graph::graph_contraction()
{
	int old_num_ver = vertex_num;

	vector <int> index_ver_for_remove, ver_for_remove, ver_for_connection;
	ver_for_connection.push_back(num_new_ver);
	cout << "Ведите вершины для стягивания через ENTER. Конец ввода - 0 " << endl; 
	int v, index_v = -1; 
	cin >> v;
	while (v != 0)
	{
		for (int i = 0; i < adjacency_list.size(); i++)
		{
			if (v == adjacency_list[i][0])
				index_v = i;
		}
		if (index_v == -1)
		{
			cout << "Bершины не существует." << endl; return;
		}
		index_ver_for_remove.push_back(index_v);
		ver_for_remove.push_back(v);
		cout << "Ведите вершины для стягивания через ENTER. Конец ввода - 0 " << endl;
		cin >> v;
	}

	if (ver_for_remove.size() < 2)
	{
		cout << "Нужно минимум две вершины для стягивания!" << endl; return; 
	}

	for (int i = 0; i < index_ver_for_remove.size(); i++)
	{
		for (int j = 1; j < adjacency_list[index_ver_for_remove[i]].size(); j++)
		{
			if (adjacency_list[index_ver_for_remove[i]][j] != adjacency_list[index_ver_for_remove[i]][0]) //не связана сама с собой
			{
				if (find(ver_for_remove.begin(), ver_for_remove.end(), adjacency_list[index_ver_for_remove[i]][j]) == ver_for_remove.end()
					&& find(ver_for_connection.begin(), ver_for_connection.end(), adjacency_list[index_ver_for_remove[i]][j]) == ver_for_connection.end()) //не нашел
				{
					int temp2;
					for (temp2 = 1; temp2 < ver_for_connection.size(); temp2++) //чтобы по порядку было. не 7 5 4, а 7 4 5
					{
						if (ver_for_connection[temp2] > adjacency_list[index_ver_for_remove[i]][j])
							break;
					}
					ver_for_connection.emplace(ver_for_connection.begin() + temp2, adjacency_list[index_ver_for_remove[i]][j]);
					//ver_for_connection.push_back(adjacency_list[index_ver_for_remove[i]][j]);
				}	
			}
		}
	}

	for (int i = 0; i < adjacency_list.size(); i++)
	{
		if (find(ver_for_remove.begin(), ver_for_remove.end(), adjacency_list[i][0]) == ver_for_remove.end()) //не в списке удаляемых, иначе и трогать смысла нет
		{
			int flag = 0;
			for (int j = 1; j < adjacency_list[i].size(); j++)
			{
				if (find(ver_for_remove.begin(), ver_for_remove.end(), adjacency_list[i][j]) != ver_for_remove.end()) //нашли в списке удаляемых вершин
				{
					adjacency_list[i].erase(adjacency_list[i].begin() + j); //ну так удалим ее
					if (!flag)
					{
						adjacency_list[i].push_back(num_new_ver);
						flag = 1;
					}
					j--;
				}
			}
		}
	}
	
	for (int i = 0; i < adjacency_list.size(); i++)
	{
		if (find(ver_for_remove.begin(), ver_for_remove.end(), adjacency_list[i][0]) != ver_for_remove.end())
		{
			adjacency_list[i].clear();
			adjacency_list.erase(adjacency_list.begin() + i);
			i--;
			vertex_num--;
		}
	}

	adjacency_list.push_back(vector<int>());
	adjacency_list[vertex_num] = ver_for_connection;
	vertex_num++; num_new_ver++;
	ver_for_connection.clear(); ver_for_remove.clear(); index_ver_for_remove.clear();

	graph_rearrange_by_list(old_num_ver);

}
void Graph::connect_or_union_graphs(Graph* G1, Graph* G2, int connect) //соединение, +, conn = 1 между вершинами двух графов, объединение conn = 0
{
	if ((*G1).norient) norient = 1;
	else norient = 0;

	vertex_num = (*G1).vertex_num + (*G2).vertex_num;
	num_new_ver = vertex_num + 1;
	malloc_matr();

	adjacency_matrix[0][0] = 0;
	for (int i = 1; i < vertex_num + 1; i++)
	{
		adjacency_matrix[0][i] = i;
		adjacency_matrix[i][0] = i;
	}
	int i, j;
	for (i = 1; i < (*G1).vertex_num + 1; i++)
	{
		for (j = 1; j < (*G1).vertex_num + 1; j++)
		{
			adjacency_matrix[i][j] = (*G1).adjacency_matrix[i][j];
		}
	}
	for (i = (*G1).vertex_num + 1; i < vertex_num + 1; i++)
	{
		for (j = (*G1).vertex_num + 1; j < vertex_num + 1; j++)
		{
			adjacency_matrix[i][j] = (*G2).adjacency_matrix[i - (*G1).vertex_num][j - (*G1).vertex_num];
		}
	}
	for (int i = 1; i < (*G1).vertex_num + 1; i++)
	{
		for (int j = (*G1).vertex_num + 1; j < vertex_num + 1; j++)
		{
			adjacency_matrix[i][j] = connect;
			adjacency_matrix[j][i] = connect;
		}
	}
	
	count_edges(); //количество петель и ребер для Inc

	//только после количества ребер/дуг!!!! после проверки ориентированности!
	adj_to_list();  //преобразование в список 
	adj_to_inc();

	get_distance(); //найти расстояние
	count_con_com();
	count_eccentricity(); //после расстояние - экс
	count_diametr_radius(); // после экс - диаметр и радиус
	find_center(); //зная радиус можно найти центр

	if (norient) count_degree(); //определение степенной последовательности
	else
	{
		count_half_degree(); //степ зах-исхода
		count_sources_and_drains();
	}

	count_leaf_and_isolated();
	count_peref_vertex();
}
void Graph::graph_multiplication(Graph* G1, Graph* G2)
{
	if ((*G1).norient) norient = 1;
	else norient = 0;

	vertex_num = (*G1).vertex_num * (*G2).vertex_num;
	num_new_ver = vertex_num + 1;
	malloc_matr();
	/*adjacency_matrix = new int* [vertex_num + 1];
	for (int i = 0; i < vertex_num + 1; i++)
	{
		adjacency_matrix[i] = new int[vertex_num + 1];
	}*/

	adjacency_matrix[0][0] = 0;
	for (int i = 1; i < vertex_num + 1; i++)
	{
		adjacency_matrix[i][0] = i;
		adjacency_matrix[0][i] = i;
	}
	for (int i = 1; i < vertex_num + 1; i++)
	{
		for (int j = 1; j < vertex_num + 1; j++)
		{
			adjacency_matrix[i][j] = 0;
		}
	}

	int** adj_matr_copy;
	adj_matr_copy = new int* [(*G1).vertex_num + 1];
	for (int i = 0; i < (*G1).vertex_num + 1; i++)
	{
		adj_matr_copy[i] = new int[(*G1).vertex_num + 1];
	}
	for (int i = 1; i < (*G1).vertex_num + 1; i++)
	{
		for (int j = 1; j < (*G1).vertex_num + 1; j++)
		{
			if (i == j && (*G1).adjacency_matrix[i][j])
				adj_matr_copy[i][j] = 2;
			else if ((*G1).adjacency_matrix[i][j])
			{
				adj_matr_copy[i][j] = 1;
			}
			else adj_matr_copy[i][j] = 0; //i = j и там 0 должно быть тут
		}
	}

	for (int k = 0; k < vertex_num; k += (*G1).vertex_num)
	{
		for (int i = 1; i < (*G1).vertex_num + 1; i++)
		{
			for (int j = 1; j < (*G1).vertex_num + 1; j++)
			{
				adjacency_matrix[i + k][j + k] = adj_matr_copy[i][j];
			}
		}
	}

	/*for (int i = 0; i < vertex_num + 1; i++)
	{
		for (int j = 0; j < vertex_num + 1; j++)
		{
			cout << adjacency_matrix[i][j] << " ";
		}
		cout << endl; 
	}*/
	for (int i = 1; i < (*G2).vertex_num + 1; i++)
	{
		int str = i;
		for (int j = 1; j < (*G2).vertex_num + 1; j++)
		{
			if (i == j)
			{
				if ((*G2).adjacency_matrix[i][j])
				{
					for (int i2 = (i - 1) * (*G1).vertex_num + 1; i2 < i * (*G1).vertex_num + 1; i2++)
					{
						adjacency_matrix[i2][i2] += 2;
					}
				}
			}
			else
			{
				if ((*G2).adjacency_matrix[i][j])
				{
					for (int i2 = (i - 1) * (*G1).vertex_num + 1 + (j - 1) * (*G1).vertex_num; i2 < i * (*G1).vertex_num + 1 + (j - 1) * (*G1).vertex_num; i2++)
					{
						int index_i, index_j;
						index_i = i2 - (j - 1) * (*G1).vertex_num; index_j = i2 - (i - 1) * (*G1).vertex_num;
						adjacency_matrix[index_i][index_j] = 1;
						/*for (int ty = 0; ty < vertex_num + 1; ty++)
						{
							for (int tz = 0; tz < vertex_num + 1; tz++)
							{
								cout << adjacency_matrix[ty][tz] << " ";
							}
							cout << endl;
						}*/
					}
				}
			}
		}
	}

	for (int i = 0; i < (*G1).vertex_num; i++)
	{
		delete[] adj_matr_copy[i];
	}
	delete[] adj_matr_copy;


	count_edges(); //количество петель и ребер для Inc

	//только после количества ребер/дуг!!!! после проверки ориентированности!
	adj_to_list();  //преобразование в список 
	adj_to_inc();

	get_distance(); //найти расстояние
	count_con_com();
	count_eccentricity(); //после расстояние - экс
	count_diametr_radius(); // после экс - диаметр и радиус
	find_center(); //зная радиус можно найти центр

	if (norient) count_degree(); //определение степенной последовательности
	else
	{
		count_half_degree(); //степ зах-исхода
		count_sources_and_drains();
	}

	count_leaf_and_isolated();
	count_peref_vertex();
}

void menu(void)
{
	cout << "Считать граф в виде матрицы смежности - 1" << endl;
	cout << "Считать граф в виде матрицы инцидентности - 2" << endl;
	cout << "Считать граф в виде списка смежности - 3" << endl;
	cout << endl;
	cout << "Список смежности - 4" << endl;
	cout << "Матрица смежности - 5" << endl;
	cout << "Матрица инцидентности - 6" << endl;
	cout << endl;
	cout << "Степенная последовательность (полустепени захода и исхода) - 7" << endl;
	cout << "Эксцентриситеты вершин - 8" << endl;
	cout << "Диаметр, радиус, центр и перефирийные вершины - 9" << endl;
	cout << "Висячие и изолированные вершины - 10" << endl;
	cout << "Стоки и истоки - 11" << endl;
	cout << "Обхват графа - 12" << endl;
	cout << "Количество вершин и ребер/дуг - 13" << endl;
	cout << "Расстояние между двумя вершинами - 14" << endl;
	cout << endl;
	cout << "Добавить вершину - 15" << endl;
	cout << "Удалить вершину - 16" << endl;
	cout << "Добавить ребро - 17" << endl;
	cout << "Удалить ребро - 18" << endl;
	cout << "Получить дополнение графа - 19" << endl;
	cout << "Подразбиение ребра - 20" << endl;
	cout << "Отождествление вершин - 21" << endl;
	cout << "Дублирование вершины - 22" << endl;
	cout << "Размнoжение вершин - 23" << endl;
	cout << endl;
	cout << "Стягивание графа - 24" << endl; 
	cout << "Соединение графов - 25" << endl;
	cout << "Объединение графов - 26" << endl; 
	cout << "Умножение графов - 27" << endl;
	cout << "Удалить выбранный граф - 30" << endl; 
	cout << "Вывод существующих номеров графов - 31" << endl; 
	cout << endl; 
	cout << "Вывод графа в виде списка смежности в файл - 28" << endl;
	cout << "Выбрать граф - 50" << endl; 
	cout << "Выход - 0" << endl;
}

int message_for_user(void)
{
	cout << "Выберете граф, нумерация ведется с 1: ";
	int num_g = 0;
	cin >> num_g;
	if (!mass_graphs[num_g - 1].vertex_num)
	//if (num_g > count_G)
	{
		for (int i = 0; i < 10; i++)
		{
			if (mass_graphs[i].vertex_num)
			{
				num_g = i + 1;
				break;
			}
		}
		cout << "Неверный номер графа. Графа не существует. Пока что будет выбран граф №" << num_g << ". " << "Попытайтесь снова" << endl; 
	}
	cout << "Выбран граф №" << num_g << endl;
	return num_g;
}

void num_graphs(void)
{
	cout << "Всего графов: " << count_G << endl; 
	cout << "Загруженные графы имеют номера: " << endl;
	for (int i = 0; i < 10; i++)
	{
		if (mass_graphs[i].vertex_num)
		{
			cout << i + 1 << " ";
		}
	}
	cout << endl; 
}

void find_correct_num_for_add(void)
{
	corr_num = count_G;
	for (int i = 0; i < count_G; i++)
	{
		if (mass_graphs[i].vertex_num == 0)
		{
			corr_num = i;
			break;
		}
	}
}

void functions(void)
{
	int num, num_g = 1;
	cout << "Выберете операцию: ";
	cin >> num;

	while (num != 0)
	{
		switch (num)
		{
		case 1:
		{
			char filename[100] = { '\0' };
			cout << "Введите название файла: ";
			//scanf("%s", &filename);
			cin >> filename;
			//add
			find_correct_num_for_add();
			//mass_graphs[count_G].get_adjacency(filename);
			mass_graphs[corr_num].get_adjacency(filename);
			count_G++;
			break;
		}
		case 2:
		{
			char filename[100] = { '\0' };
			cout << "Введите название файла: ";
			cin >> filename;
			find_correct_num_for_add();
			mass_graphs[corr_num].get_incidence(filename);
			//mass_graphs[count_G].get_incidence(filename);
			count_G++;
			break;
		}
		case 3:
		{
			char filename[100] = { '\0' };
			cout << "Введите название файла: ";
			cin >> filename;
			find_correct_num_for_add();
			mass_graphs[corr_num].get_list(filename);
			//mass_graphs[count_G].get_list(filename);
			count_G++;
			break;
		}
		case 4:
		{
			mass_graphs[num_g - 1].print_adj_list();
			break;
		}
		case 5:
		{
			mass_graphs[num_g - 1].print_adj_matrix();
			break;
		}
		
		case 6:
		{
			mass_graphs[num_g - 1].print_inc_matrix();
			break;
		}
		case 7:
		{
			mass_graphs[num_g - 1].print_degrees();
			break;

		}
		case 8:
		{
			mass_graphs[num_g - 1].print_eccentricity();
			break;
		}
		case 9:
		{
			mass_graphs[num_g - 1].print_diam_rad_centres();
			break;
		}
		case 10:
		{
			mass_graphs[num_g - 1].print_leafs_isolated();
			break;
		}
		case 11:
		{
			mass_graphs[num_g - 1].print_sources_drains();
			break;
		}

		case 12:
		{
			mass_graphs[num_g - 1].count_girth();
			mass_graphs[num_g - 1].print_girth();
			break;
		}
		case 13:
		{
			mass_graphs[num_g - 1].print_vertex_edg_arc();
			break;
		}
		case 14:
		{
			int from, to;
			cout << endl;
			cout << "Введите через ENTER вершину ИЗ и вершину В" << endl;
			cin >> from; cin >> to;
			mass_graphs[num_g - 1].print_distance_ver(from, to);
			break;
		}
		case 15:
		{
			mass_graphs[num_g - 1].add_vertex();
			break;
		}
		case 16:
		{
			int r_ver;
			cout << "Выберете вершину для удаления: ";
			cin >> r_ver;
			mass_graphs[num_g - 1].remove_vertex(r_ver);
			break;
		}
		case 17:
		{
			int from, to;
			cout << "Введите через ENTER две вершины. Учитывайте порядок для ориентированного графа." << endl;
			cin >> from >> to;
			mass_graphs[num_g - 1].add_edge(from, to);
			break;
		}
		case 18:
		{
			int from, to;
			cout << "Введите через ENTER две вершины. Учитывайте порядок для ориентированного графа." << endl;
			cin >> from >> to;
			mass_graphs[num_g - 1].remove_edge(from, to);
			break;
		}
		case 19:
		{
			//
			find_correct_num_for_add();
			//cout << "Результат этой бинарной операции будет сохранен. Это будет граф № " << count_G + 1 << endl;
			//mass_graphs[count_G].complement_graph(&mass_graphs[num_g - 1]);
			cout << "Результат этой бинарной операции будет сохранен. Это будет граф № " << corr_num + 1 << endl;
			mass_graphs[corr_num].complement_graph(&mass_graphs[num_g - 1]);
			count_G++;
			//mass_graphs[num_g - 1].complement_graph();
			break;
		}
		case 20:
		{
			int from, to;
			cout << "Введите через ENTER две вершины." << endl;
			cin >> from >> to;
			mass_graphs[num_g - 1].subdivision_edge(from, to);
			break;
		}
		case 21:
		{
			int v1, v2;
			cout << "Введите через ENTER две вершины." << endl;
			cin >> v1 >> v2;
			mass_graphs[num_g - 1].split_verticises(v1, v2);
			break;
		}

		case 22:
		{
			int v;
			cout << "Введите вершину." << endl;
			cin >> v;
			mass_graphs[num_g - 1].vertex_dublicate(v);
			break;
		}
		case 23:
		{
			int v;
			cout << "Введите вершину." << endl;
			cin >> v;
			mass_graphs[num_g - 1].multiplication_vertex(v);
			break;
		}
		case 24:
		{
			mass_graphs[num_g - 1].graph_contraction();
			break;
		}
		case 25:
		{
			int numg_1, numg_2;
			//
			find_correct_num_for_add();
			//cout << "Результат этой бинарной операции будет сохранен. Это будет граф № " << count_G + 1<< endl; 
			cout << "Результат этой бинарной операции будет сохранен. Это будет граф № " << corr_num + 1 << endl;
			cout << "Введите номера двух графов через ENTER" << endl;
			cin >> numg_1 >> numg_2;
			//if (numg_1 > count_G || numg_2 > count_G)
			if (mass_graphs[numg_1 - 1].vertex_num == 0 || mass_graphs[numg_2 - 1].vertex_num == 0)
			{
				cout << "Некорректный ввод номеров графов!" << endl;
				break;
			}
			//Graph G1 = ; 
			//Graph G2 = mass_graphs[numg_2 - 1];
			//mass_graphs[count_G].connect_or_union_graphs(&mass_graphs[numg_1 - 1], &mass_graphs[numg_2 - 1], 1);
			mass_graphs[corr_num].connect_or_union_graphs(&mass_graphs[numg_1 - 1], &mass_graphs[numg_2 - 1], 1);
			count_G++;
			break;
		}
		case 26:
		{
			int numg_1, numg_2;
			find_correct_num_for_add();
			//cout << "Результат этой бинарной операции будет сохранен. Это будет граф № " << count_G + 1 << endl;
			cout << "Результат этой бинарной операции будет сохранен. Это будет граф № " << corr_num + 1 << endl;
			cout << "Введите номера двух графов через ENTER" << endl;
			cin >> numg_1 >> numg_2;
			//if (numg_1 > count_G || numg_2 > count_G)
			if (mass_graphs[numg_1 - 1].vertex_num == 0 || mass_graphs[numg_2 - 1].vertex_num == 0)
			{
				cout << "Некорректный ввод номеров графов!" << endl;
				break;
			}
			//mass_graphs[count_G].connect_or_union_graphs(&mass_graphs[numg_1 - 1], &mass_graphs[numg_2 - 1], 0);
			mass_graphs[corr_num].connect_or_union_graphs(&mass_graphs[numg_1 - 1], &mass_graphs[numg_2 - 1], 0);
			count_G++;
			break;
		}
		case 27:
		{
			int numg_1, numg_2;
			find_correct_num_for_add();
			cout << "Результат этой бинарной операции будет сохранен. Это будет граф № " << corr_num + 1 << endl;
			//cout << "Результат этой бинарной операции будет сохранен. Это будет граф № " << count_G + 1 << endl;
			cout << "Введите номера двух графов через ENTER" << endl;
			cin >> numg_1 >> numg_2;
			if (mass_graphs[numg_1-1].vertex_num == 0 || mass_graphs[numg_2 - 1].vertex_num == 0)
			{
				cout << "Некорректный ввод номеров графов!" << endl;
				break;
			}
			//mass_graphs[count_G].graph_multiplication(&mass_graphs[numg_1 - 1], &mass_graphs[numg_2 - 1]);
			mass_graphs[corr_num].graph_multiplication(&mass_graphs[numg_1 - 1], &mass_graphs[numg_2 - 1]);
			count_G++;
			break;
		}
		case 28:
		{
			mass_graphs[num_g - 1].print_adj_list_to_file();
		}
		case 29:
		{
			menu();
			break;
		}
		case 30:
		{
			cout << "Удаляю граф №" << num_g << endl; 
			mass_graphs[num_g - 1].delete_graph();
			count_G--;
			cout << "Количество графов после удаления: " << count_G << endl;
			for (int i = 0; i < 10; i++)
			{
				if (mass_graphs[i].vertex_num)
				{
					num_g = i + 1;
					cout << "Выбран граф №" << i + 1 << endl; 
					break;
				}
			}
			break;
		}
		case 31:
		{
			num_graphs();
			break;
		}
		case 50:
		{
			num_g = message_for_user();
			break;
		}
		default:
			break;
		}
		
		cout << "Выберете операцию (Показать меню - 29): ";
		cin >> num;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	menu();
	functions();
	return 0;
}