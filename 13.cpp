#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

//Хеш-функция
size_t hashFunc(const std::string& key)
{
    size_t hash = 0;
    for (char c : key)
    {
        hash = hash * 31 + c;
    }
    return hash;
}

int main()
{

    setlocale(LC_ALL, "Russian");

    std::ifstream input("input.txt");//Путь к входному файлу
    std::ofstream output("output.txt");//Путь к результирующему файлу


    if (!input.is_open() || !output.is_open())
    {
        std::cout << "Ошибка открытия файла" << std::endl;
        return 1;
    }


    std::unordered_map<size_t, std::string> hashTable;//Хеш-таблица
    //std::string line;

    //Читаем текст из входного файла
    std::string word;
    while (input >> word)
    {
        int index = hashFunc(word);//Получаем индекс в хеш-таблице
        hashTable[index] = word;//Добавляем слово
    }

    //Записываем хеш-таблицу в результирующий файл
    for (const auto& pair : hashTable)
    {
        output << pair.first << " " << pair.second << std::endl;
    }





    //Закрываем файлы
    input.close();
    output.close();


    std::cout << "Hash table created and written to output file successfully!" << std::endl;

    return 0;
}
