#include <iostream>
#include <vector>

using namespace std;

// Функция для нахождения количества путей без ограничений
long long countPaths(int rows, int cols) {
    // Создаем двумерный вектор для хранения количества путей до каждой клетки
    vector<vector<long long>> paths(rows + 1, vector<long long>(cols + 1, 0));

    // Инициализируем количество путей до левого нижнего угла как 1
    paths[0][0] = 1;

    // Заполняем остальные клетки
    for (int i = 0; i <= rows; ++i) {
        for (int j = 0; j <= cols; ++j) {
            // Путей до текущей клетки равно сумме путей до клеток сверху и слева от нее
            if (i > 0) paths[i][j] += paths[i - 1][j];
            if (j > 0) paths[i][j] += paths[i][j - 1];
        }
    }

    // Возвращаем количество путей до правого верхнего угла
    return paths[rows][cols];
}

// Функция для нахождения количества путей с условием, что два вертикальных участка не могут идти подряд
long long countPathsWithoutConsecutiveVertical(int rows, int cols) {
    // Создаем двумерный вектор для хранения количества путей до каждой клетки
    vector<vector<long long>> paths(rows + 1, vector<long long>(cols + 1, 0));

    // Инициализируем количество путей до левого нижнего угла как 1
    paths[0][0] = 1;

    // Заполняем остальные клетки
    for (int i = 0; i <= rows; ++i) {
        for (int j = 0; j <= cols; ++j) {
            // Путей до текущей клетки равно сумме путей до клеток сверху и слева от нее,
            // за исключением случаев, когда предыдущая клетка находится выше текущей
            if (i > 0 && !(i > 1 && j > 0 && paths[i - 1][j] > 0)) paths[i][j] += paths[i - 1][j];
            if (j > 0) paths[i][j] += paths[i][j - 1];
        }
    }

    // Возвращаем количество путей до правого верхнего угла
    return paths[rows][cols];
}

int main() 
{
    setlocale(LC_ALL, "Russian");
    
    int rows = 15;
    int cols = 15;

    cout << "Количество различных кратчайших путей без ограничений: " << countPaths(rows, cols) << endl;
    cout << "Количество различных кратчайших путей без двух вертикальных участков, идущих подряд: " << countPathsWithoutConsecutiveVertical(rows, cols) << endl;

    return 0;
}
