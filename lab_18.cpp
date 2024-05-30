

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

// Функция сортировки массива с использованием сортировки Шелла(Сортируем по убыванию модулей)
void  sort(std::vector<int>& _arr) 
{
    // Инициализация переменной шага (step) равной половине размера массива _arr.
    // Продолжаем цикл, пока шаг больше 0, уменьшая шаг вдвое на каждой итерации.
    for (int step = _arr.size() / 2; step > 0; step /= 2) 
    {
        for (int i = step; i < _arr.size(); ++i) 
        {
            // Создание временной переменной temp для хранения текущего элемента.
            int temp = _arr[i];
            int j;// Инициализация переменной j.
            for (j = i; j >= step && abs(_arr[j - step]) < abs(temp); j -= step)// Начало вложенного цикла для сдвига элементов на правильные позиции.
            {
                _arr[j] = _arr[j - step];
            }
            _arr[j] = temp;
        }
    }
};

// Функция проверки существования подмножества с суммой равной нулю
bool subsetSumZero(std::vector<int>& numbers) 
{
    // Начало цикла по элементам массива numbers, исключая последний элемент.
    for (int i = 0; i < numbers.size() - 1; ++i)
    {
        int sum = numbers[i];// Инициализация переменной sum значением текущего элемента.
        for (int j = i + 1; j < numbers.size(); ++j)//Вложенный цикл для проверки всех возможных подмножеств, начиная с элемента, следующего за текущим.
        {
            // Если модуль суммы больше модуля суммы текущего элемента и следующего элемента, прибавляем следующий элемент к сумме.
            if (abs(sum) > abs(sum + numbers[j])) 
            {
                sum += numbers[j];
            }
        }
        if (sum == 0)// Если сумма равна нулю, возвращаем true.
            return true;
    }
    return false;// Возвращаем false, если не найдено подмножество с суммой нуль.
}

int main() 
{
    std::vector<int> numbers = { -7, -3, 10, 4 };

    sort(numbers);
    for (int i = 0; i < numbers.size(); i++)
    {
        std::cout << numbers[i] << std::endl;
    }

    if (subsetSumZero(numbers)) 
    {
        std::cout << std::endl;
        std::cout << "Yes,there sum exists" << std::endl;
    }
    else 
    {
        std::cout << std::endl;
        std::cout << "No, there doesn't exist" << std::endl;
    }

    return 0;
}
