

#include <iostream>
#include <vector>
#include <string>

// Функция для вычисления таблицы переходов
std::vector<int> computeTransitionTable(const std::string& pattern) 
{
    int m = pattern.size();// Получаем длину шаблона
    std::vector<int> transition(m + 1, 0);// Создаем вектор для таблицы переходов, и заполняем его нулями
    transition[0] = -1;// Инициализируем первый элемент таблицы переходов значением -1
    int k = -1;// Инициализируем переменную k значением -1
    
    // Цикл по длине шаблона
    for (int q = 1; q <= m; ++q) 
    {
        while (k >= 0 && pattern[k] != pattern[q - 1]) // Пока k >= 0 и символы не совпадают
        {
            k = transition[k];// Уменьшаем k до значения из таблицы переходов
        }
        k++;// Увеличиваем k
        transition[q] = k;// Записываем значение k в таблицу переходов
    }
    return transition; // Возвращаем таблицу переходов
}

// Функция для поиска подстроки в тексте
void searchPattern(const std::string& text, const std::string& pattern)
{
    int n = text.size();// Получаем длину текста
    int m = pattern.size();// Получаем длину шаблона
    std::vector<int> transition = computeTransitionTable(pattern);// Получаем таблицу переходов для указанного шаблона
    
    int q = 0; // Инициализируем переменную q значением 0
    
    // Цикл по всем символам текста
    for (int i = 0; i < n; ++i) 
    {
        while (q >= 0 && pattern[q] != text[i]) // Пока q >= 0 и символы не совпадают
        {
            q = transition[q]; // Уменьшаем q до значения из таблицы переходов
        }
        
        // Обновление значения
        q++;// Увеличиваем q
        if (q == m) // Если найден шаблон
        {
            std::cout << "Pattern found at index " << i - m + 1 << std::endl;// Выводим индекс найденного шаблона
            q = transition[q];// Возврат к начальному значению
        }
    }
}

int main() 
{
    std::string text = "ababcababcabcabc";
    std::string pattern = "abcabc";

    searchPattern(text, pattern);
    return 0;
}

