

#include <iostream>
#include <vector>
#include <queue>
#include <limits> 

// Структура вершины графа
struct Vertex 
{
	int dest; // Номер вершины назначения
	int weight; // Вес ребра
	bool visited; // Флаг посещения вершины
};

// Шаблон класса для реализации графа
template <size_t Rows_Colm>
class Graph 
{
	int q_Vert; // Количество вершин
	std::vector <std::vector<Vertex>> adjList; // Список смежности
	std::vector<bool> visited; // Вектор посещенных вершин

	// Метод добавления вершины
	void addVertex(int src, int dest, int weight) 
	{
		Vertex vert;//Создаем вершину 
		vert.visited = false;//Объявляем вершину как непосещенную 
		vert.dest = dest;//Номер вершины, куда ведет ребро
		vert.weight = weight;//Вес ребра
		adjList[src].push_back(vert);//Добавляем вершину в список смежности
	}
public:
	// Конструктор
	Graph() : q_Vert(Rows_Colm) //Инициализируем количество вершин графа
	{
		adjList.resize(q_Vert);//Инициализируем список смежности
		visited.resize(q_Vert);//Инициализируем список посещенных вершин 
	}

	// Метод создания графа из списка смежности
	static Graph<Rows_Colm> create(std::initializer_list<std::initializer_list<int>> data)
	{
		Graph <Rows_Colm> graph;//Создание пустого графа
		int rowIndx = 0;//Индекс строки, начинаем с 0
		for (auto row : data) //Перебор строк входных данных
		{
			int colmIndx = 0; //Индекс столбца, начинаем с 0
			for (auto val : row) //Перебор значений в строке
			{
				if (val != 0)//Если значение не равно нулю 
					graph.addVertex(rowIndx, colmIndx, val);//Добавляем ребро в граф
				++colmIndx;//Увеличение индекса столбца
			}
			++rowIndx;//Увеличение индекса строки
		}
		return graph;//Возвращение графа
	}

	// Метод для печати списка смежности
	void printGraph() 
	{
		for (int i = 0; i < q_Vert; i++) //Проход по всем вершинам графа
		{
			std::cout << "Список смежности вершины " << i + 1 << ": ";
			for (const auto& edge : adjList[i]) //Проход по рёбрам текущей вершины
			{
				std::cout << edge.dest + 1 << " "; //Вывод вершины, к которой ведёт ребро
			}
			std::cout << std::endl;
		}
	}
	// Метод для нахождения кратчайшего пути методом Дейкстры
	void shortestPath_Dijkstra(int start_Vertex) 
	{
		//Создается вектор distance_Vert длиной q_Vert, все элементы которого инициализируются INT_MAX
		std::vector<int> distance_Vert(q_Vert, std::numeric_limits<int>::max());
		//Создается приоритетная очередь, отсортированная по возрастанию, которая будет хранить пары (расстояние, вершина).
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

		distance_Vert[start_Vertex] = 0;//Устанавливается начальное расстояние до стартовой вершины start_Vertex равное нулю
		pq.push({ 0, start_Vertex });//Добавляется стартовая вершина с расстоянием 0 в приоритетную очередь

		while (!pq.empty())//Пока очередь не пуста
		{
			int currentVertex = pq.top().second; //Получаем вершину с наименьшим расстоянием из приоритетной очереди
			int currentDistance = pq.top().first; //Получаеем текущее минимальное расстояние до вершины
			pq.pop(); //Извлекается вершина с наименьшим расстоянием из приоритетной очереди

			//Если текущее расстояние больше, чем сохраненное в distance_Vert, то игнорируется текущая вершина
			if (currentDistance > distance_Vert[currentVertex])
				continue;

			//Перебор всех смежных вершин текущей вершины
			for (const auto& adjVertex : adjList[currentVertex])
			{
				int newDistance = currentDistance + adjVertex.weight; //Вычисляем новое расстояние до смежной вершины
				if (newDistance < distance_Vert[adjVertex.dest]) //Если новое расстояние меньше, чем текущее сохраненное, то  обновляем расстояние
				{
					distance_Vert[adjVertex.dest] = newDistance;//Обновляется расстояние до смежной вершины
					pq.push({ newDistance, adjVertex.dest });//Смежная вершина добавляется в приоритетную очередь с обновленным расстоянием
				}
			}
		}
		for (int i = 0; i < q_Vert; ++i) //Вывод полученных кратчайших расстояний для всех вершин
		{
			std::cout << "Кратчайшее расстояние до вершины " << i + 1 << ": " << distance_Vert[i] << std::endl;
		}
	}
};

int main() 
{
	setlocale(LC_ALL, "ru");

	auto graph = Graph<6>::create({
		{0, 1, 6, 0, 0, 0},
		{1, 0, 0, 3, 9, 0},
		{6, 0, 0, 2, 0, 0},
		{0, 3, 2, 0, 2, 0},
		{0, 9, 0, 2, 0, 3},
		{0, 0, 0, 0, 3, 0},
		});


	graph.printGraph();
	graph.shortestPath_Dijkstra(0);
	return 0;
}

