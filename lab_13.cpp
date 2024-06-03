

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

// Функция для создания таблицы смещений
std::map<char, int> displaced(const std::string& pattern) 
{
//Начинам c n-1 
//Берем значение которое наиболее близко к концу образа 

    // Множество уникальных символов
    std::set<char> uniqueChars;
    // Карта смещений
    std::map<char, int> displaceMap;
    // Размер шаблона
    int p_size = pattern.size() - 1;
    // Проход по шаблону для заполнения карты смещений
    for (int i = p_size - 1; i >= 0; i--) 
    {
        // Если символ уникален
        if (uniqueChars.find(pattern[i]) == uniqueChars.end()) 
        {
            uniqueChars.insert(pattern[i]);// Добавляем символ в множество уникальных символов
            displaceMap.insert(std::make_pair(pattern[i], p_size - i));// Рассчитываем смещение для данного символа
        }
    }

    // Обработка последнего символа шаблона
    if (uniqueChars.find(pattern[p_size]) == uniqueChars.end())
    {
        // Если последний символ уникален
        displaceMap.insert(std::make_pair(pattern[p_size], p_size + 1));// Добавляем символ в множество уникальных символов
    }

    // Добавление смещения для символа-заполнителя ('*')
    displaceMap.insert(std::make_pair('*', p_size + 1));
    return displaceMap;//Возвращаем карту смещений 
}

// Основной алгоритм BMH
void algorithmBMH(const std::string& text, const std::string& pattern) 
{
    int n = text.size();// Длина строки
    int m = pattern.size();// Длина шаблона
    std::map<char, int> p = displaced(pattern);// Получение таблицы смещений для шаблона

    int i = m - 1, check = 0;// Инициализация индекса
    
    // Пока индекс не выйдет за границы строки
    while (i < n) 
    {
        int k = 0;// Счетчик совпадений
        int j = m - 1;// Индекс в шаблоне
        
        // Сравниваем символы справа налево
        while (j >= 0 && pattern[j] == text[i - k])
        {
            j--;
            k++;
        }

        // Если все символы совпали
        if (j == -1) 
        {
            check = 1;// Помечаем, что вхождение найдено
            std::cout << "Pattern found at index " << i - m + 1 << std::endl;// Выводим позицию начала вхождения
        }
        
        // Рассчитываем смещение с учетом текущего символа текста
        if (p.find(text[i]) == p.end()) 
        {
            // Если символ не найден в таблице смещений
            // Сдвигаемся на размер шаблона
            i += p['*'];
        }
        else 
        {
            // Если символ найден в таблице смещений
            // Сдвигаемся на значение смещения
            i += p[text[i]];
        }
    }
    
    // Если вхождение не найдено
    if (!check)
    {
        std::cout << "There is no pattern in the text " << std::endl;
    }
}

int main() 
{
    std::string text = " abcabca abacbab abcabcabc";
    std::string pattern = "abcabc";
    algorithmBMH(text, pattern);
    return 0;
}

