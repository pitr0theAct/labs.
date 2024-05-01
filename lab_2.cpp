#include <iostream>
#include <vector>
#include <queue>

//Структура Vertex содержит информацию о вершине графа
struct Vertex 
{
    int dest; //Номер вершины, куда ведет ребро
    int weight; //Вес ребра
};

template <size_t Rows_Colm>
class Graph 
{
    int q_Vert; //Количество вершин
    std::vector<std::vector<Vertex>> adjList; //Список смежности

    //Метод addVertex добавляет новую вершину в список смежности 
    void addVertex(int src, int dest, int weight) 
    {
        Vertex vert; //Создаем вершину 
        vert.dest = dest; //Номер вершины, куда ведет ребро
        vert.weight = weight; //Вес ребра
        adjList[src].push_back(vert); //Добавляем вершину в список смежности
    }

public:
    //Конструктор Graph инициализирует список смежности и количество вершин графа
    Graph() : q_Vert(Rows_Colm) 
    {
        adjList.resize(q_Vert); //Инициализируем список смежности
    }

    //Статический метод для создания графа из списка инициализации
    static Graph<Rows_Colm> create(std::initializer_list<std::initializer_list<int>> data) 
    {
        Graph <Rows_Colm> graph; //Создание пустого графа
        int rowIndx = 0; //Индекс строки, начинаем с 0
        for (auto row : data)  //Перебор строк входных данных
        {
            int colmIndx = 0; //Индекс столбца, начинаем с 0
            for (auto val : row) //Перебор значений в строке
            {
                if (val != 0) //Если значение не равно нулю, добавляем ребро в граф
                    graph.addVertex(rowIndx, colmIndx, val); //Добавляем ребро в граф
                ++colmIndx; //Увеличение индекса столбца
            }
            ++rowIndx; //Увеличение индекса строки
        }
        return graph; //Возвращение графа
    }

    //Метод для вывода графа в консоль
    void printGraph() 
    {
        for (int i = 0; i < q_Vert; i++) 
        {
            std::cout << "Список смежности вершины " << i + 1 << ": ";
            for (const auto& edge : adjList[i]) 
            {
                std::cout << edge.dest + 1 << " ";
            }
            std::cout << std::endl;
        }
    }

    //Метод findShortestPath ищет кратчайший путь из заданной вершины, используя поиск в ширину (BFS)
    std::vector<int> findShortestPath(int _numberVert) 
    {
        std::vector<bool> visited(q_Vert, false); //Вектор посещённых вершин, инициализируется false
        std::vector<int> path(q_Vert, INT_MAX); //Вектор кратчайших путей от начальной вершины, инициализируется INT_MAX
        std::queue<int> q; //Очередь для обхода графа

        //Добавление начальной вершины в очередь и инициализация её пути как 0
        q.push(_numberVert);
        path[_numberVert] = 0;
        visited[_numberVert] = true;

        //Пока очередь не пуста
        while (!q.empty()) 
        {
            //Извлечение вершины из очереди
            int v = q.front();
            q.pop();

            //Перебор всех смежных вершин текущей вершины
            for (const auto& adjVertex : adjList[v]) 
            {
                //Если смежная вершина не посещена
                if (!visited[adjVertex.dest]) 
                {
                    q.push(adjVertex.dest); //Добавление смежной вершины в очередь
                    visited[adjVertex.dest] = true; //Отметка смежной вершины как посещённой
                    path[adjVertex.dest] = path[v] + 1; //Обновление кратчайшего пути до смежной вершины
                }
            }
        }
        return path; //Возвращение вектора кратчайших путей
    }
};

int main() 
{
    setlocale(LC_ALL, "ru");

    //Создание графа из списка инициализации
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
    //Поиск кратчайшего пути из вершины nv
    std::vector<int> path = graph.findShortestPath(nv);

    for (int i = 0; i < path.size(); i++) 
    {
        //Вывод кратчайших путей
        if (path[i] != nv && path[i] != INT_MAX)
        {
            std::cout << "Кратчайший путь из " << 1 << " в " << (i + 1) << " составляет " << path[i] << std::endl;
        }
        //Вывод несуществующих путей
        if (path[i] == INT_MAX)
        {
            std::cout << "Пути из " << 1 << " в " << (i + 1) << " не существует " << std::endl;
        }
    }
    return 0;
}