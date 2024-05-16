

#include <iostream>
#include <vector>
#include <stack>

// Перечисление для направлений ребер
enum direction 
{
    direction_NONE = 0,// direction_NONE - отсутствие направления
    direction_AB = 1, //direction_AB - направление от вершины A к вершине B
    direction_BOTH = 2, //direction_BOTH - двунаправленное ребро
};

// Структура вершины
struct Vertex 
{
    int dest;// номер вершины, к которой ведет ребро
    int weight;// вес ребра
    direction Path;// направление ребра
};

// Шаблон класса
template <size_t Rows_Colm>
class Graph 
{
    int q_Vert; // количество вершин
    std::vector<std::vector<Vertex>> adjList; // список смежности

    // Метод для добавления вершины
    void addVertex(int src, int dest, int weight, direction _Path) 
    {
        Vertex vert; //Создаем вершину 
        vert.dest = dest; //Номер вершины, куда ведет ребро
        vert.weight = weight; //Вес ребра
        vert.Path = _Path; // направление ребра
        adjList[src].push_back(vert); //Добавляем вершину в список смежности
    }

    // Метод обхода в глубину
    void DFS(int v, std::vector<bool>& visited, std::stack<int>& SCC) 
    {
        visited[v] = true;// Помечаем вершину v как посещённую.

        for (const auto& edge : adjList[v])  // Перебираем все рёбра, исходящие из вершины v.
        {
            int u = edge.dest;// Получаем номер вершины-получателя u.
            // Если вершина u не посещена и ребро не равно direction_NONE,
            // то рекурсивно вызываем DFS для вершины u.
            if (!visited[u] && edge.Path != direction_NONE) 
            {
                DFS(u, visited, SCC);
            }
        }
        SCC.push(v);// Добавляем вершину v в стек SCC.
    }

    // Вспомогательный метод для обхода в глубину
    void DFSUtil(int v, std::vector<bool>& visited, std::vector<int>& scc_vec)
    {
        visited[v] = true;// Помечаем вершину v как посещённую.
        scc_vec.push_back(v);// Добавляем вершину v в вектор SCC.

        for (const auto& edge : adjList[v]) // Перебираем все рёбра, исходящие из вершины v.
        {
            int u = edge.dest;// Получаем номер вершины-получателя u.
            // Если вершина u не посещена и ребро не равно direction_NONE,
            // то рекурсивно вызываем DFS для вершины u.
            if (!visited[u] && edge.Path != direction_NONE) 
            {
                DFSUtil(u, visited, scc_vec);
            }
        }
    }

    // Метод для получения транспонированного графа
    Graph<Rows_Colm> getTranspose() 
    {
        Graph<Rows_Colm> transposedGraph;// Создаём новый граф transposedGraph.
        transposedGraph.q_Vert = q_Vert;// Устанавливаем число вершин в transposedGraph равным числу вершин в исходном графе.
        transposedGraph.adjList.resize(q_Vert);// Изменяем размер списка смежности transposedGraph до q_Vert.

        for (int v = 0; v < q_Vert; ++v) // Перебираем все вершины в исходном графе.
        {
            for (const auto& edge : adjList[v]) // Перебираем все рёбра, исходящие из вершины v.
            {
                transposedGraph.addVertex(edge.dest, v, edge.weight, edge.Path);// Создаём ребро в транспонированном графе с весом edge.weight
                                                                                // и направлением edge.Path.
            }
        }

        return transposedGraph; // Возвращаем транспонированный граф.
    }

public:
    // Конструктор класса
    Graph() : q_Vert(Rows_Colm) //Инициализируем количество вершин графа
    {
        adjList.resize(q_Vert);//Инициализируем список смежности
    }

    // Статический метод для создания графа из инициализаторов
    static Graph<Rows_Colm> create(std::initializer_list<std::initializer_list<std::pair<int, int>>> data) 
    {
        Graph<Rows_Colm> graph; //Создание пустого графа
        int rowIndx = 0; //Индекс строки, начинаем с 0
        for (auto row : data) //Перебор строк входных данных 
        {
            int colmIndx = 0; //Индекс столбца, начинаем с 0
            for (auto val : row) //Перебор значений в строке
            {
                if (val.first != 0) //Если значение не равно нулю, добавляем ребро в граф
                    graph.addVertex(rowIndx, colmIndx, val.first, static_cast<direction>(val.second)); //Добавляем ребро в граф
                ++colmIndx; //Увеличение индекса столбца
            }
            ++rowIndx; //Увеличение индекса строки
        }
        return graph; //Возвращение графа
    }

    // Метод для вывода графа
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

    // Метод для нахождения сильно связанных компонент
    void findSCC() 
    {
        std::vector<bool> visited(q_Vert, false);// Вектор посещённых вершин, инициализируется false.
        std::stack<int> SCC;// Стек для хранения вершин сильно связанной компоненты.

        // Выполнение DFS для каждой непосещённой вершины.
        for (int v = 0; v < q_Vert; ++v) 
        {
            if (!visited[v]) 
            {
                DFS(v, visited, SCC);
            }
        }

        Graph<Rows_Colm> transposedGraph = getTranspose();// Получение транспонированного графа.
        visited.assign(q_Vert, false);// Обновление вектора посещённых вершин.

        std::vector<std::vector<int>> SCCs;// Вектор для хранения сильно связанных компонент.

        while (!SCC.empty())  // Пока стек SCC не пуст.
        {
            int v = SCC.top();// Получение вершины из стека SCC.
            SCC.pop();
            if (!visited[v])  // Если вершина v не посещена.
            {
                std::vector<int> scc_vec;// Вектор для хранения вершин сильно связной компоненты.
                transposedGraph.DFSUtil(v, visited, scc_vec);// Выполнение DFS в транспонированном графе для вершины v.
                SCCs.push_back(scc_vec);// Добавление вершин сильно связной компоненты в вектор SCCs.
            }
        }

        // Вывод сильно связанных компонент.
        for (const auto& SCC : SCCs)
        {
            std::cout << "Сильно связанная компонента: ";
            for (int v : SCC) 
            {
                std::cout << v + 1 << " ";
            }
            std::cout << std::endl;
        }
    }
};


int main() 
{
    setlocale(LC_ALL, "ru");

    // Создание графа и вывод информации
    auto graph = Graph<9>::create({
         { {0, 0}, {1, 1}, {1, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} },
         { {1, 0}, {0, 0}, {0, 0}, {1, 1}, {1, 2}, {0, 0}, {0, 0}, {0, 0}, {0, 0} },
         { {1, 0}, {0, 0}, {0, 0}, {1, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} },
         { {0, 0}, {1, 0}, {1, 2}, {0, 0}, {1, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0} },
         { {0, 0}, {1, 2}, {0, 0}, {1, 2}, {0, 1}, {1, 1}, {0, 0}, {0, 0}, {0, 0} },
         { {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} },
         { {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} },
         { {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 2} },
         { {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 2}, {0, 1} }
        });

    graph.printGraph();
    std::cout << "Сильно связанные компоненты: " << std::endl;
    graph.findSCC();

    return 0;
}

