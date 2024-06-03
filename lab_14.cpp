

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// Функция для вычисления хеша строки
unsigned long long calculateHash(const std::string& str, int start, int end, int prime) 
{
    unsigned long long hashValue = 0; // Инициализация переменной для хранения хеш-значения.
    for (int i = start; i <= end; ++i) // Цикл перебора символов строки в заданном диапазоне.
    {
        hashValue = (hashValue * prime + (int)str[i]) % prime;// Вычисление хеш-значения для текущего символа.
    }
    return hashValue;// Возврат вычисленного хеш-значения.
}

// Функция поиска подстроки с использованием алгоритма Рабина-Карпа
void searchRabinKarp(const std::string& text, const std::string& pattern, int prime) 
{
    int n = text.length();// Длина текста.
    int m = pattern.length();// Длина образца.
    int p = prime;// Простое число для вычисления хеша.

    // Вычисление хешей для образца и текста
    unsigned long long patternHash = calculateHash(pattern, 0, m - 1, p);// Вычисление хеша для образца.
    unsigned long long textHash = calculateHash(text, 0, m, p);// Вычисление хеша для начальной подстроки текста.

    // Проход по тексту и сравнение хешей
    for (int i = 0; i <= n - m; ++i) // Цикл по тексту для сравнения хешей образца и подстроки текста.
    {
        if (patternHash == textHash) // Если хеши совпали.
        {
            bool check = true;// Переменная для проверки совпадения символов.
            for (int j = 0; j < m; ++j) // Цикл для проверки совпадения символов образца и текста.
            {
                if (text[i + j] != pattern[j]) // Если символы не совпадают.
                {
                    check = false;// Установка флага неполного совпадения.
                }
            }
            if (check) // Если все символы совпадают.
            {
                std::cout << "Pattern found at index " << i << std::endl;// Вывод индекса найденного образца.
            }
        }
        
        // Обновление хеша для следующей итерации
        if (i < n - m) // Если не достигнут конец текста.
        {
            textHash = (textHash - (int)text[i] + p) % p; // Обновление хеш-значения для следующей подстроки текста.
            textHash = (textHash * prime + (int)text[i + m]) % p;// Пересчет хеша для следующей итерации.
        }
    }
}

int main() 
{
    std::string text = " abcabca abacbab abcabcabc";
    std::string pattern = "abcabc";
    int prime = 111;

    searchRabinKarp(text, pattern, prime);

    return 0;
}


