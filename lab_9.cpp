

#include <iostream>
#include <string>
#include <vector>
#include <queue>

// Перечисление для определения направления пути
enum direction 
{
	direction_NONE = 0,// direction_NONE - отсутствие направления
	direction_AB = 1,//direction_AB - направление от вершины A к вершине B
	direction_BOTH = 2,//direction_BOTH - двунаправленное ребро
};

// Структура для хранения вершины графа
struct Vertex 
{
	int dest;// номер вершины, к которой ведет ребро
	int weight;// вес ребра
	direction Path;// направление ребра
};

// Класс для работы с графом
template <size_t Rows_Colm>
class Graph 
{
	int q_Vert; // Количество вершин
	std::vector<std::vector<Vertex>> adjList; // Список смежности

	// Функция для добавления вершины
	void addVertex(int src, int dest, int weight, direction _Path) 
	{
		Vertex vert;//Создаем вершину 
		vert.dest = dest;//Номер вершины, куда ведет ребро
		vert.weight = weight;//Вес ребра
		vert.Path = _Path;// направление ребра
		adjList[src].push_back(vert);//Добавляем вершину в список смежности
	}


public:
	// Конструктор класса
	Graph() : q_Vert(Rows_Colm) //Инициализируем количество вершин графа
	{
		adjList.resize(q_Vert);//Инициализируем список смежности
	}

	// Функция для создания графа из двумерного списка
	static Graph<Rows_Colm> create(std::initializer_list<std::initializer_list<std::pair<int, int>>> data) 
	{
		Graph<Rows_Colm> graph; //Создание пустого графа
		int rowIndx = 0;//Индекс строки, начинаем с 0
		for (auto row : data) //Перебор строк входных данных 
		{
			int colmIndx = 0;//Индекс столбца, начинаем с 0
			for (auto val : row) //Перебор значений в строке
			{
				if (val.second != 0)//Если значение не равно нулю, добавляем ребро в граф
					graph.addVertex(rowIndx, colmIndx, val.first, static_cast<direction>(val.second));//Добавляем ребро в граф
				++colmIndx;//Увеличение индекса столбца
			}
			++rowIndx;//Увеличение индекса строки
		}
		return graph;//Возвращение графа
	}

	// Алгоритм Беллмана-Форда для поиска кратчайших путей
	void alghoritmBellmanFord(int src)
	{
		std::vector<int> VertDistance(q_Vert, INT_MAX);// Создание вектора расстояний до вершин, исходно расстояние до всех вершин - бесконечность
		VertDistance[src] = 0;// Устанавливаем расстояние до исходной вершины как 0

		/// Повторяем следующий блок кода q_Vert - 1 раз (где q_Vert - количество вершин в графе)
		for (int i = 0; i < q_Vert - 1; ++i) 
		{
			for (int j = 0; j < q_Vert; ++j) // Перебираем все вершины графа
			{
				for (const auto& edge : adjList[j]) // Перебираем все ребра, исходящие из текущей вершины j
				{
					int v = edge.dest;// Получаем конечную вершину ребра
					int weight = edge.weight;// Получаем вес ребра
					
					// Если существует путь из j в v и новый путь короче текущего
					if (VertDistance[j] != INT_MAX && VertDistance[j] + weight < VertDistance[v])
					{
						VertDistance[v] = VertDistance[j] + weight;// Обновляем расстояние до вершины v
					}
				}
			}
		}

		for (int u = 0; u < q_Vert; ++u) // Проверяем наличие отрицательных циклов
		{
			for (const auto& edge : adjList[u]) // Перебираем все ребра, исходящие из вершины u
			{
				int v = edge.dest;
				int weight = edge.weight;
				
				// Если после n итераций до сих пор удается улучшать путь, значит граф содержит отрицательный цикл
				if (VertDistance[u] != INT_MAX && VertDistance[u] + weight < VertDistance[v]) 
				{
					std::cout << "Граф содержит отрицательный цикл\n";
					return;
				}
			}
		}

		// Выводим информацию о кратчайших расстояниях
		std::cout << "Кратчайшее растояние из вершины: " << src + 1 << ":\n";
		for (int i = 0; i < q_Vert; ++i) // Перебираем все вершины
		{
			std::cout << "До вершины: " << i + 1 << ": " << VertDistance[i] << std::endl;// Выводим расстояние до вершины i
		}
	}
};

int main() 
{
	setlocale(LC_ALL, "ru");

	// Создание графа и вывод информации
	auto graph = Graph<7>::create({
				{{0, 0}, {1, 0}, {1, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
				{{1, 0}, {0, 0}, {2, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
				{{1, 0}, {2, 1}, {0, 0}, {4, 2}, {5,1}, {0, 0}, {0, 0}},
				{{0, 0}, {0, 0}, {4, 2}, {0, 0}, {0, 0}, {7, 1}, {14,1}},
				{{0, 0}, {0, 0}, {5, 0}, {0, 0}, {0, 0}, {-4,1}, {-5,1}},
				{{0, 0}, {0, 0}, {0, 0}, {7, 0}, {-4,0}, {0, 0}, {10,1}},
				{{0, 0}, {0, 0}, {0, 0}, {14,0}, {-5,0}, {10,0}, {0, 0}}
		});

	graph.alghoritmBellmanFord(0);

	return 0;
}
