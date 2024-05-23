
#include <stack>
#include <iostream>
#include <string>
#include <vector>

class Graph 
{
    int q_Vert; // Количество вершин
    std::vector<std::vector<int>> adjList; // Список смежности

    // Метод добавления вершины
    void addVertex(int src, int dest) 
    {
        adjList[src].push_back(dest);//Добавляем вершину в список смежности
    }

public:
    // Конструктор
    Graph(int rows_cols) : q_Vert(rows_cols) //Инициализируем количество вершин графа
    {
        adjList.resize(q_Vert);//Инициализируем список смежности
    }

    // Метод создания графа на основе инициализационного списка
    static Graph create(std::initializer_list<std::initializer_list<int>> data) 
    {
        //Создание пустого графа
        int rows_cols = data.size();
        Graph graph(rows_cols);

        int rowIndx = 0;//Индекс столбца, начинаем с 0
        for (auto row : data) //Перебор значений в строке
        {
            int colmIndx = 0;//Индекс столбца, начинаем с 0
            for (auto val : row)// Если значение не равно нулю, добавляем ребро в граф
            {
                if (val != 0) //Если значение не равно нулю, добавляем ребро в граф
                {
                    graph.addVertex(rowIndx, colmIndx);//Добавляем ребро в граф
                }
                ++colmIndx;//Увеличение индекса столбца
            }
            ++rowIndx;//Увеличение индекса строки
        }
        return graph;//Возвращение графа
    }

    
    
    
    // Метод поиска пути Эйлера в графе
    std::vector<int> algorithEuler(int startVertex) 
    {
        std::vector<int> eulerVert;//Объявляет пустой вектор eulerVert для хранения пути Эйлера.

        std::vector<int> vertDegree(q_Vert, 0);//Объявляет вектор vertDegree, содержащий степени вершин графа. Степень вершины - 
                                               //это количество ребер, инцидентных этой вершине. Вектор инициализируется нулями.

        //Заполняет вектор vertDegree степенями вершин, подсчитывая количество ребер в каждом списке смежности adjList[u].
        for (int u = 0; u < q_Vert; ++u) 
        {
            vertDegree[u] = adjList[u].size();
        }

        //Объявляет стек path для хранения вершин, посещенных во время поиска пути Эйлера.
        std::stack<int> path;
        path.push(startVertex);//Добавляет начальную вершину в стек path.

        while (!path.empty()) //Входит в цикл, который продолжается, пока стек path не станет пустым
        {
            int u = path.top();//Извлекает верхнюю вершину из стека path.

            if (vertDegree[u] == 0) //Проверяет, равна ли степень извлеченной вершины u нулю.
            {
                eulerVert.push_back(u);//Если степень вершины u равна нулю, добавляет ее в вектор eulerVert как часть пути Эйлера.
                path.pop();//Удаляет вершину u из стека path.
            }
            
            //Если степень вершины u не равна нулю, переходит к следующему блоку.
            else 
            {
                bool found = false;//Объявляет булеву переменную found и инициализирует ее значением false. 
                                   //Она будет использоваться для отслеживания того, был ли найден сосед с неотмеченным ребром.

                
                for (size_t i = 0; i < adjList[u].size(); ++i)//Входит в цикл, который перебирает соседей вершины u.
                {
                    int v = adjList[u][i];//Извлекает соседа v вершины u.

                    if (v != -1) //Проверяет, не равен ли сосед v специальному значению -1. Это значение используется для обозначения удаленных ребер.
                    {
                        path.push(v);//Если сосед v допустим, добавляет его в стек path.
                        adjList[u].erase(adjList[u].begin() + i);//Удаляет ребро между вершинами u и v из списка смежности adjList[u].
                        for (size_t j = 0; j < adjList[v].size(); ++j) //Входит в цикл, который перебирает соседей вершины v.
                        {
                            if (adjList[v][j] == u) //Проверяет, не является ли сосед u вершины v.
                            {
                                adjList[v].erase(adjList[v].begin() + j);//Если сосед u найден, удаляет ребро между вершинами v и u из 
                                                                         //списка смежности adjList[v].
                                break;
                            }
                        }
                        vertDegree[u]--;//Уменьшает степени вершин u и v на 1, так как ребро между ними было удалено.
                        vertDegree[v]--;
                        found = true;//Устанавливает found в true, указывая, что сосед с неотмеченным ребром был найден.
                        break;//Выходит из цикла поиска соседей.
                    }
                }

                if (!found) //Если сосед с неотмеченным ребром не был найден, переходит к следующему блоку.
                {
                    path.pop();//Удаляет вершину u из стека path.
                }
            }
        }

        return eulerVert;//После завершения цикла возвращает вектор eulerVert, содержащий путь Эйлера.
    }
};

int main() 
{
    setlocale(LC_ALL, "ru");

    auto graph = Graph::create({
         {0, 1, 1, 0, 0},
         {1, 0, 1, 0, 0},
         {1, 1, 0, 1, 1},
         {0, 0, 1, 0, 1},
         {0, 0, 1, 1, 0}
        });

    std::vector<int> vert = graph.algorithEuler(0);

    for (int c : vert) 
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    return 0;
}


