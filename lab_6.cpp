

#include <iostream>
#include <string>
#include <vector>
#include <queue>

// Структура для представления ребра графа
struct Vertex 
{
	int dest;// Конечная вершина ребра
	int weight;// Вес ребра
};

template <size_t Rows_Colm>
class Graph // Класс Graph для представления графа
{
	int q_Vert;// Количество вершин в графе
	std::vector <std::vector<Vertex>> adjList; // Список смежности для хранения рёбер
	std::vector<std::pair<std::string, int>> adjEdge; // Вектор для хранения рёбер

	// Метод для добавления вершины в список смежности
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
		adjEdge.emplace_back(name, weight);// Добавляет новое ребро с именем name и весом weight в список ребер
	};

	// Метод для удаления дубликатов в списке ребер
	void removeDuplicates(std::vector<std::pair<std::string, int>>& arr) 
	{
		std::vector<std::pair<std::string, int>> temp;//Создание временного вектора пар значений типа string и int для хранения уникальных элементов.

		for (int i = 0; i < arr.size(); ++i) //Цикл по всем элементам входного массива.
		{
			bool duplicateFound = false;// Флаг для обнаружения дубликата.
			for (int j = i + 1; j < arr.size(); ++j) //Цикл для сравнения текущего элемента с остальными элементами массива.
			{
				if (arr[i].first.size() == arr[j].first.size() &&
					arr[i].first[0] == arr[j].first[1] &&
					arr[i].first[1] == arr[j].first[0]) //Условие для обнаружения дубликата 
				{

					duplicateFound = true;// Установка флага дубликата и выход из цикла.
					break;
				}
			}
			if (!duplicateFound) //Если дубликат не найден, то добавляем элемент во временный вектор.
			{
				temp.push_back(arr[i]);
			}
		}
		arr = temp;//Заменяем исходный массив уникальными элементами из временного вектора.
	};

	// Метод для сортировки списка ребер по возростанию веса
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

	// Метод для нахождения корня дерева
	int findRoot(std::vector<int>& parent, int i) 
	{
		// Ищет корень элемента i в дереве, пока не найдет корень.
		while (parent[i] != i) 
		{
			i = parent[i];
		}
		return i;
	};

	// Метод для построения минимального остовного дерева (алгоритм Крускала)
	std::vector<std::pair<std::string, int>> kruskal() 
	{
		std::vector<std::pair<std::string, int>> result; //Создание вектора пар значений для хранения результата.
		std::vector<int> parent(q_Vert);

		sort(adjEdge);// Сортировка списка ребер по возрастанию веса.

		for (int i = 0; i < q_Vert; ++i) 
		{
			parent[i] = i;//Инициализация каждого элемента родителем самого себя.
		}

		for (const auto& edge : adjEdge) 
		{
			// Находим корень для каждого узла ребра.
			int root1 = findRoot(parent, edge.first[0] - 'A');
			int root2 = findRoot(parent, edge.first[1] - 'A');

			if (root1 != root2)// Проверка на то, что оба узла принадлежат различным компонентам связности.
			{
				// Добавление ребра в результат и объединение компонент связности.
				result.push_back(edge);
				parent[root1] = root2;
			}
		}

		return result;// Возвращаем результат
	}

public:
	// Конструктор класса
	Graph() : q_Vert(Rows_Colm) // Инициализируем переменную q_Vert значением Rows_Colm
	{
		adjList.resize(q_Vert);// Изменяем размер adjList на q_Vert
	}

	// Статический метод для создания графа на основе инициализирующего списка
	static Graph<Rows_Colm> create(std::initializer_list<std::initializer_list<int>> data)
	{
		Graph <Rows_Colm> graph;//Создание пустого графа

		int rowIndx = 0;//Индекс строки, начинаем с 0
		for (auto row : data) //Перебор строк входных данных
		{
			int colmIndx = 0;//Индекс столбца, начинаем с 0
			for (auto val : row)  //Перебор значений в строке
			{
				if (val != 0) // Если значение не равно нулю, добавляем ребро в граф
				{
					graph.addVertex(rowIndx, colmIndx, val);//Добавляем ребро в граф
					std::string vert_A(1, 'A' + rowIndx);
					std::string vert_B(1, 'A' + colmIndx);
					graph.addEdge(vert_A + vert_B, val);// Добавляем новое ребро с именем name и весом weight в список ребер
				}
				++colmIndx; //Увеличение индекса столбца
			}
			++rowIndx;//Увеличение индекса строки
		}
		return graph;//Возвращение графа
	}

	// Метод для построения минимального остовного дерева и вывода ребер
	void buildTree() 
	{
		auto result = kruskal();//Вызываем метод kruskal для поиска минимального остовного дерева

		for (const auto& edge : result)// Выводим найденные ребра
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
		 {0, 4, 7, 0, 9, 0, 0, 0, 0},
		 {0, 6, 0, 9, 0, 1, 0, 0, 0},
		 {0, 0, 0, 0, 1, 0, 4, 0, 0},
		 {9, 0, 0, 0, 0, 4, 0, 2, 0},
		 {0, 0, 0, 0, 0, 0, 2, 0 ,1},
		 {0, 0, 0, 0, 0, 0, 0, 1, 0}
		});

	graph.buildTree();

	return 0;
}


