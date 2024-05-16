

#include <iostream>
#include <string>
#include <vector>
#include <queue>

// Структура для представления ребра графа
struct Vertex 
{
	int dest; // Конечная вершина ребра
	int weight; // Вес ребра
};

// Класс графа
template <size_t Rows_Colm>
class Graph // Класс Graph для представления графа
{
	int q_Vert; // Количество вершин в графе
	std::vector <std::vector<Vertex>> adjList; // Список смежности для хранения рёбер
	std::vector<std::pair<std::string, int>> adjEdge; // Вектор для хранения рёбер

	// Метод для добавления вершины и ребра в список смежности
	void addVertex(int src, int dest, int weight)
	{
		Vertex vert;//Создаем вершину 
		vert.dest = dest;//Номер вершины, куда ведет ребро
		vert.weight = weight;//Вес ребра
		adjList[src].push_back(vert);//Добавляем вершину в список смежности
	}

	// Метод для добавления ребра в список ребер
	void addEdge(std::string name, int weight) 
	{
		adjEdge.emplace_back(name, weight);// Добавляем новое ребро с именем name и весом weight в список ребер
	};

	// Метод для удаления дубликатов из вектора рёбер
	void removeDuplicates(std::vector<std::pair<std::string, int>>& arr) 
	{
		std::vector<std::pair<std::string, int>> temp;//Создание временного вектора пар значений типа string и int для хранения уникальных элементов

		for (int i = 0; i < arr.size(); ++i)//Цикл по всем элементам входного массива
		{
			bool duplicateFound = false;// Флаг для обнаружения дубликата
			for (int j = i + 1; j < arr.size(); ++j) //Цикл для сравнения текущего элемента с остальными элементами массива
			{
				if (arr[i].first.size() == arr[j].first.size() &&
					arr[i].first[0] == arr[j].first[1] &&
					arr[i].first[1] == arr[j].first[0]) //Условие для обнаружения дубликата 
				{

					duplicateFound = true;// Установка флага дубликата и выход из цикла
					break;
				}
			}
			if (!duplicateFound) //Если дубликат не найден, то добавляем элемент во временный вектор
			{
				if (arr[i].first[1] < arr[i].first[0]) 
				{
					arr[i].first = std::string(1, arr[i].first[1]) + arr[i].first[0];
				}
				temp.push_back(arr[i]);
			}
		}
		arr = temp;//Заменяем исходный массив уникальными элементами из временного вектора
	};

	// Метод для сортировки вектора рёбер по весу
	void sort(std::vector<std::pair<std::string, int>>& arr) 
	{
		for (int i = 0; i < arr.size() - 1; i++) 
		{
			for (int j = 0; j < arr.size() - 1; j++) 
			{
				if (arr[j].second > arr[j + 1].second) 
				{
					std::pair<std::string, int> bubble{ arr[j] };
					arr[j] = arr[j + 1];
					arr[j + 1] = bubble;
				}
			}
		}
	};

	// Метод для поиска минимального ребра из доступных
	std::pair<std::string, int> minEdge(std::vector<std::pair<std::string, int>> arr, std::vector<int>& visited)// Функция принимает вектор рёбер и вектор посещенных вершин 
	{
		std::pair<std::string, int> buble = arr[0];// Создаёт пару buble и инициализируем её первым элементом из переданного вектора
		for (int i = 0; i < arr.size() - 1; i++) // Проходимся по всем элементам вектора и если находит ребро с меньшим весом, заменяет buble на это ребро
		{
			if (buble.second > arr[i].second) //Если находим ребро с меньшим весом, заменяет buble на это ребро
				buble = arr[i];
		}
		// Помечаем обе вершины найденного ребра как посещенные
		visited[buble.first[0] - 'A'] = 1;
		visited[buble.first[1] - 'A'] = 1;
		return buble;// Возвращает найденное минимальное ребро
	};

	// Метод применения алгоритма для построения минимального остовного дерева
	std::pair<std::string, int> algorithm(std::vector<int>& visited)// Функция algorithm принимает вектор посещенных вершин
	{
		std::vector<std::pair<std::string, int>> arr; // Создаем вектор arr для хранения доступных ребер

		// Проходим по всем ребрам и добавляем их в arr, если одна из вершин посещена, а другая нет
		for (const auto& edge : adjEdge) 
		{
			if ((visited[edge.first[0] - 'A'] && !visited[edge.first[1] - 'A']) ||
				(visited[edge.first[1] - 'A'] && !visited[edge.first[0] - 'A'])) 
			{
				arr.push_back(edge);
			}
		}

		// Если вектор arr не пустой, применяем алгоритм нахождения минимального ребра
		if (!arr.empty()) 
		{
			visited[adjEdge[0].first[0] - 'A'] = 1;
			return minEdge(arr, visited);
		}
		else 
		{
			std::pair<std::string, int> a("", NULL);
			return a; // Иначе возвращаем пустое значение
		}

	};

	// Метод применения алгоритма Прима для построения минимального остовного дерева
	std::vector<std::pair<std::string, int>> algorithmPrim() 
	{
		std::vector<std::pair<std::string, int>> result; // Создаем вектор результатов
		std::vector<int> visited(q_Vert, 0);// Инициализируем вектор посещенных вершин

		// Сортировка вектора рёбер и удаление дубликатов
		sort(adjEdge);
		removeDuplicates(adjEdge);

		// Добавляем первое ребро в результат и помечаем его вершины как посещенные
		result.push_back(adjEdge[0]);
		visited[adjEdge[0].first[0] - 'A'] = 1;
		visited[adjEdge[0].first[1] - 'A'] = 1;

		// Применяем алгоритм для остальных вершин
		for (int i = 0; i < visited.size() - 1; i++) 
		{
			std::pair<std::string, int> buble = algorithm(visited);
			if (buble.first != "")
				result.push_back(buble);
		}

		return result;// Возвращаем построенное минимальное остовное дерево
	};


public:
	// Конструктор класса
	Graph() : q_Vert(Rows_Colm) // Инициализируем переменную q_Vert значением Rows_Colm
	{
		adjList.resize(q_Vert);// Изменяем размер adjList на q_Vert
	}

	// Метод для создания графа из двумерного инициализационного списка
	static Graph<Rows_Colm> create(std::initializer_list<std::initializer_list<int>> data) 
	{
		Graph <Rows_Colm> graph;//Создание пустого графа

		int rowIndx = 0;//Индекс строки, начинаем с 0
		for (auto row : data) //Перебор строк входных данных
		{
			int colmIndx = 0;//Индекс столбца, начинаем с 0
			for (auto val : row) //Перебор значений в строке
			{
				if (val != 0) // Если значение не равно нулю, добавляем ребро в граф
				{
					graph.addVertex(rowIndx, colmIndx, val);//Добавляем ребро в граф
					std::string vert_A(1, 'A' + rowIndx);
					std::string vert_B(1, 'A' + colmIndx);
					graph.addEdge(vert_A + vert_B, val);// Добавляем новое ребро с именем name и весом weight в список ребер
				}
				++colmIndx;//Увеличение индекса столбца
			}
			++rowIndx;//Увеличение индекса строки
		}
		return graph;//Возвращение графа
	}

	// Метод для построения минимального остовного дерева
	void buildTree() 
	{
		auto result = algorithmPrim();//Вызываем метод algorithmPrim для поиска минимального остовного дерева

		for (const auto& edge : result) // Выводим найденные ребра
		{
			std::cout << edge.first << ' ' << edge.second << std::endl;
		}
	};

};


int main() 
{
	setlocale(LC_ALL, "ru");

	auto graph = Graph<9>::create({
		 {0, 5, 3, 0, 0, 0, 9, 0, 0},
		 {5, 0, 0, 4, 6, 0, 0, 0, 0},
		 {3, 0, 0, 7, 0, 0, 0, 0, 0},
		 {0, 4, 7, 0, 0, 0, 0, 0, 0},
		 {0, 6, 0, 0, 0, 1, 0, 0, 0},
		 {0, 0, 0, 0, 1, 0, 4, 0, 0},
		 {9, 0, 0, 0, 0, 4, 0, 2, 0},
		 {0, 0, 0, 0, 0, 0, 2, 0 ,1},
		 {0, 0, 0, 0, 0, 0, 0, 1, 0}
		});

	graph.buildTree();

	return 0;
}


