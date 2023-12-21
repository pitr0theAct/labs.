

#include <iostream>
#include <fstream>
#include <vector>
#include <list>

//Хеш-функция для получения индекса в хеш-таблице
int hashFunction(const std::string& word, int tableSize) 
{
    int hash = 0;
    for (char c : word) 
    {
        hash += c;
    }
    return hash % tableSize;
}

int main() 
{
    std::string inputFile = "input.txt";//Путь к входному файлу
    std::string outputFile = "output.txt";//Путь к результирующему файлу
    const int tableSize = 100;//Размер хеш-таблицы

    std::vector<std::list<std::string>> hashTable(tableSize);//Хеш-таблица с списками

    std::ifstream input(inputFile);//Открываем входной файл для чтения
    if (!input.is_open()) 
    {
        std::cout << "Failed to open input file!" << std::endl;
        return 1;
    }

    //Читаем текст из входного файла
    std::string word;
    while (input >> word) 
    {
        int index = hashFunction(word, tableSize);//Получаем индекс в хеш-таблице
        hashTable[index].push_back(word);//Добавляем слово в соответствующий список
    }

    input.close();//Закрываем входной файл

    std::ofstream output(outputFile);//Открываем результирующий файл для записи
    if (!output.is_open()) 
    {
        std::cout << "Failed to open output file!" << std::endl;
        return 1;
    }

    //Записываем хеш-таблицу в результирующий файл
    for (int i = 0; i < tableSize; ++i) 
    {
        output << "Список " << i << ": ";
        for (const std::string& word : hashTable[i]) 
        {
            output << word << " ";
        }
        output << std::endl;
    }

    output.close();//Закрываем результирующий файл

    std::cout << "Hash table created and written to output file successfully!" << std::endl;

    return 0;
}

