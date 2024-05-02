

#include <iostream>
#include <vector>
#include <queue>

// Объявление структуры вершины графа
struct Vertex 
{
	int dest; // номер вершины, в которую идет ребро
	int weight; // вес ребра
};

// Шаблон класса графа с матрицей смежности
template <size_t Rows_Colm>
class Graph 
{
	int q_Vert; // количество вершин
	std::vector <std::vector<Vertex>> adjList; // список смежности

	// Метод для добавления ребер в список смежности
	void addVertex(int src, int dest, int weight) 
	{
		Vertex vert;
		vert.dest = dest;//инициализация номера вершины, к которой ведёт ребро
		vert.weight = weight;//инициализация веса ребра
		adjList[src].push_back(vert);//добавление вершины в список смежности графа
	}
public:
	// Конструктор класса
	Graph() : q_Vert(Rows_Colm) 
	{
		adjList.resize(q_Vert);// Инициализируем список смежности
	}

	// Статический метод создания графа из инициализирующего списка
	static Graph<Rows_Colm> create(std::initializer_list<std::initializer_list<int>> data)
	{
		Graph <Rows_Colm> graph;// создание экземпляра класса Graph
		int rowIndx = 0;
		for (auto row : data) // проход по строкам матрицы смежности
		{
			int colmIndx = 0;
			for (auto val : row) // проход по элементам строки
			{
				if (val != 0)// если вес ребра не равен 0
					graph.addVertex(rowIndx, colmIndx, val);// добавляем ребро в список смежности
				++colmIndx;
			}
			++rowIndx;
		}
		return graph;// возвращаем созданный граф
	}

	// Метод для вывода списка смежности графа в консоль
	void printGraph() 
	{
		for (int i = 0; i < q_Vert; i++) //проход по всем вершинам графа
		{
			std::cout << "Список смежности вершины " << i + 1 << ": ";
			for (const auto& edge : adjList[i]) //проход по рёбрам текущей вершины
			{
				std::cout << edge.dest + 1 << " "; //вывод номера вершины, к которой ведёт ребро
			}
			std::cout << std::endl;
		}
	}

	// Метод обхода графа в глубину
	void DFS(int v, std::vector<bool>& visited) 
	{
		visited[v] = true; // Помечаем текущую вершину как посещенную
		std::cout << (v + 1) << ' '; // Выводим номер текущей вершины

		for (const auto& edge : adjList[v]) // Перебираем все вершины, смежные с текущей
		{
			int u = edge.dest; // Получаем номер вершины
			if (!visited[u])  // Если вершина не посещена
			{
				DFS(u, visited); // Вызываем рекурсивно обход для этой вершины
			}
		}
	}

	// Метод для поиска связных компонент графа
	void findConnectedComponents() 
	{
		std::vector<bool> visited(q_Vert, false); // Создаем вектор для хранения информации о посещенных вершинах

		for (int v = 0; v < q_Vert; ++v) // Перебираем все вершины графа
		{
			if (!visited[v]) // Если вершина не посещена
			{
				DFS(v, visited); // Вызываем метод обхода в глубину для данной вершины
				std::cout << std::endl; // Переходим на новую строку после обхода всех вершин компоненты
			}
		}
	}
};



int main() 
{
	setlocale(LC_ALL, "ru");

	// Создание графа и инициализация его данными
	auto graph = Graph<9>::create({
		{0, 1, 1, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 1, 1, 0, 0, 0, 0},
		{1, 0, 0, 1, 0, 0, 0, 0, 0},
		{0, 1, 1, 0, 1, 0, 0, 0, 0},
		{0, 1, 0, 1, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0 ,1},
		{0, 0, 0, 0, 0, 0, 0, 1, 0}
		});

	int nv = 0;

	// Вывод информации о связных компонентах графа
	std::cout << "Компоненты связности при обходе DFS : " << std::endl;
	graph.findConnectedComponents();
	return 0;
}


