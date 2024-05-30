

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

// Функция для нахождения минимального количества коробок с использованием динамического программирования
// Функция minBoxesDP принимает вектор items - предметов и переменную boxCapacity - вместимость коробки.
int minBoxesDP(std::vector<int>& items, int boxCapacity) 
{
    int n = items.size();// Получаем количество предметов 
    if (n == 0)// Если количество предметов равно 0, возвращаем 0, так как коробка не нужна.
        return 0;

    // Сортируем предметы по возрастанию.
    std::sort(items.begin(), items.end());

    // Создаем вектор dp размером (boxCapacity + 1) и заполняем его значениями INT_MAX, чтобы в дальнейшем узнать минимальное количество коробок.
    std::vector<int> dp(boxCapacity + 1, INT_MAX);
    dp[0] = 0;// Устанавливаем значение 0 в dp[0], так как 0 предметов помещаются в коробку с вместимостью 0.

    // Начинаем перебор от 1 до boxCapacity.
    for (int i = 1; i <= boxCapacity; ++i) 
    {
        for (int j = 0; j < n; ++j) // Для каждого i проходим по всем предметам.
        {
            // Если текущий предмет помещается в коробку и при этом не приводит к переполнению коробки
            //вычисляем минимальное количество коробок, нужных для упаковки предметов.
            if (items[j] <= i && dp[i - items[j]] != INT_MAX) 
            {
                dp[i] = std::min(dp[i], dp[i - items[j]] + 1);// Обновляем dp[i] в соответствии с полученным результатом
            }
        }
    }

    int minNumBoxes = INT_MAX;// Находим минимальное количество коробок minNumBoxes, необходимых для упаковки всех предметов.
    for (int i = 0; i < n; ++i) 
    {
        if (items[i] > boxCapacity)
            return n; // Если какой - то предмет не помещается в коробку, возвращаем общее количество предметов в качестве ответа.
        // Вычисляем минимальное количество коробок, необходимых для упаковки оставшихся предметов.
        minNumBoxes = std::min(minNumBoxes, dp[boxCapacity - items[i]]);
    }

    return minNumBoxes;// Возвращаем найденное минимальное количество коробок.
}

int main() 
{
    std::vector<int> items = { 1, 1, 2, 2, 2, 2, 7 };
    int boxCapacity = 10;

    int minNumBoxes = minBoxesDP(items, boxCapacity);
    std::cout << "Minimum number of boxes required: " << minNumBoxes << std::endl;

    return 0;
}


