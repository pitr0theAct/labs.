

#include <iostream>
#include <vector>
#include <queue>
#include <limits> 

// Структура представления ребра графа
struct Vertex 
{
	int dest; // вершина, к которой ведёт ребро
	int weight; // вес ребра
};

// Класс представления для графа
template <size_t Rows_Colm>
class Graph 
{
	int q_Vert; // количество вершин
	std::vector <std::vector<Vertex>> adjList; // список смежности для хранения рёбер

	// Добавление вершины в список смежности
	void addVertex(int src, int dest, int weight) 
	{
		Vertex vert;
		vert.dest = dest; //инициализация номера вершины, к которой ведёт ребро
		vert.weight = weight; //инициализация веса ребра
		adjList[src].push_back(vert); //добавление вершины в список смежности графа
	}
public:
	//Конструктор
	Graph() : q_Vert(Rows_Colm) 
	{
		adjList.resize(q_Vert);// Инициализируем список смежности
	}

	// Метод создания графа на основе переданных данных
	static Graph<Rows_Colm> create(std::initializer_list<std::initializer_list<int>> data) 
	{
		Graph <Rows_Colm> graph;// создание экземпляра класса Graph
		int rowIndx = 0;
		for (auto row : data) // проход по строкам матрицы смежности
		{
			int colmIndx = 0;
			for (auto val : row) // проход по элементам строки
			{
				if (val != 0)  // если вес ребра не равен 0
					graph.addVertex(rowIndx, colmIndx, val); // добавляем ребро в список смежности
				++colmIndx;
			}
			++rowIndx;
		}
		return graph;// возвращаем созданный граф
	}

	// Метод для вывода сеписка смежности графа
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

	// Обход графа "в ширину"
	void BFS(int start_Vertex, std::vector<bool>& visited) //принимает начальную вершину и вектор посещенных вершин
	{
		std::queue<int> q; // создание очереди для обхода в ширину
		q.push(start_Vertex); // добавление начальной вершины в очередь
		visited[start_Vertex] = true; // пометка начальной вершины как посещённой

		while (!q.empty()) // пока очередь не пуста
		{
			//Извлечение вершины из очереди
			int v = q.front();
			q.pop();
			std::cout << v + 1 << " "; // вывод вершины

			for (const auto& adjVertex : adjList[v]) // проход по рёбрам текущей вершины
			{
				if (!visited[adjVertex.dest])// если вершина не посещена
				{
					q.push(adjVertex.dest); // добавляем вершину в очередь
					visited[adjVertex.dest] = true; // помечаем вершину как посещённую
				}
			}
		}
		std::cout << std::endl;
	}

	// Поиск компонента связности в графе
	void findConnectedComponents() 
	{
		std::vector<bool> visited(q_Vert, false);// создание вектора посещенных вершин, изначально все вершины не посещены

		std::cout << std::endl;
		std::cout << "Компоненты связности:\n";// вывод на экран заголовка
		for (int v = 0; v < q_Vert; ++v) //проходимся по всем вершинам графа
		{
			if (!visited[v]) // если вершина не посещена
			{
				BFS(v, visited);// вызов функции обхода в ширину начиная с данной вершины
			}
		}
	}
};


int main() 
{
	setlocale(LC_ALL, "ru");

	// Создание и заполнение графа
	auto graph = Graph<9>::create({
		{0, 1, 6, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 3, 9, 0, 0, 0, 0},
		{6, 0, 0, 2, 0, 0, 0, 0, 0},
		{0, 3, 2, 0, 2, 0, 0, 0, 0},
		{0, 9, 0, 2, 0, 3, 0, 0, 0},
		{0, 0, 0, 0, 3, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0 ,5},
		{0, 0, 0, 0, 0, 0, 0, 5, 0}
		});

	// Вывод списка смежности и поиск компонента связности
	graph.printGraph();
	graph.findConnectedComponents();
	return 0;
}


