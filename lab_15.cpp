
#include <iostream>
#include <vector>
#include <set>

//Определение перечисления color
enum color 
{
	RED,
	GREEN,
	BLUE,
	WHITE,
	NONE
};

// Структура вершины графа
struct Vertex 
{
	int dest;// Номер вершины назначения
	color clr;//Цвет вершины 
	Vertex(int _dest) : dest(_dest), clr(color::NONE) {}//Конструктор Vertex
};


// Шаблон класса для реализации графа
template <size_t Rows_Colm>
class Graph 
{
	int q_Vert;// Количество вершин
	std::vector <std::vector<Vertex>> adjList;// Список смежности
	std::vector<bool> visited;// Вектор посещенных вершин

	void addVertex(int src, int dest) // Метод добавления вершины
	{
		adjList[src].emplace_back(Vertex(dest));//Добавляем вершину в список смежности
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
			int colmIndx = 0;//Индекс столбца, начинаем с 0
			for (auto val : row) //Перебор значений в строке
			{
				if (val != 0)//Если значение не равно нулю 
					graph.addVertex(rowIndx, colmIndx);//Добавляем ребро в граф
				++colmIndx;//Увеличение индекса столбца
			} 
			++rowIndx;//Увеличение индекса строки
		}
		return graph;//Возвращение графа
	}

	void decorateGraph() 
	{
		std::vector<color> colors(q_Vert, color::WHITE);//Создание вектора colors размером q_Vert, заполненного значениями color::WHITE

		for (int i = 0; i < q_Vert; ++i)//Цикл по всем вершинам графа
		{
			std::set<color> neighborColors;//Создание множества neighborColors для хранения цветов соседей текущей вершины

			for (auto v : adjList[i])//Цикл по всем соседям текущей вершины
			{
				if (colors[v.dest] != color::NONE) //Проверка, если цвет соседа не равен color::NONE
				{
					neighborColors.insert(colors[v.dest]);//добавление его цвета в neighborColors
				}
			}

			for (int c = 0; c <= 3; ++c) //Цикл по всем цветам (0, 1, 2, 3).
			{
				if (!neighborColors.count(static_cast<color>(c))) //Проверка, если соседи не содержат текущий цвет
				{
					colors[i] = static_cast<color>(c);//то присвоение текущей вершине этого цвета
					break;//выход из цикла.
				}
			}
		}

		for (int i = 0; i < q_Vert; ++i) //Цикл по всем вершинам графа.
		{
			for (auto& v : adjList[i]) //Цикл по всем соседям каждой вершины
			{
				v.clr = colors[v.dest];//присвоение им цвета из вектора colors
			}
		}
	}

	void printGraph() 
	{
		std::vector<std::string> colorNames = { "RED", "GREEN", "BLUE", "WHITE", "NONE" };//Инициализируем вектор colorNames именами цветов.

		for (int i = 0; i < q_Vert; ++i) //Итерируемся по каждой вершине графа
		{
			std::cout << char('A' + i) << ':' << std::endl;// Выводим название текущей вершины
			for (auto v : adjList[i])//Итерируемся по соседям текущей вершины и выводим их имена и цвета
				std::cout << char('A' + v.dest) << " - " << colorNames[static_cast<int>(v.clr)] << std::endl;
		}
	}
};

int main() 
{
	setlocale(LC_ALL, "ru");

	auto graph = Graph<6>::create({
		//   A  B  C  D  E  F
			{0, 1, 1, 1, 0, 0},//A
			{1, 0, 0, 1, 1, 0},//B
			{1, 0, 0, 1, 0, 1},//C
			{1, 1, 1, 0, 0, 0},//D
			{0, 1, 0, 0, 0, 1},//E
			{0, 0, 1, 0, 1, 0},//F
		});
	graph.decorateGraph();
	graph.printGraph();

	return 0;
}


