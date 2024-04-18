

#include <iostream>

int main()
{
    setlocale(LC_ALL, "ru");

    std::string word = "КОМБИНАТОРИКА";
    int first = word.length();
    int second = word.length() - 1;
    int third = word.length() - 2;
    int fourth = word.length() - 3;
    int fifth = word.length() - 4;

    int result = first * second * third * fourth * fifth;
    std::cout << std::endl;
    std::cout << "Количество слов из 5-и букв: " << result << std::endl;






    
    double a_100 = 1.0 / 7 * pow(-5, 100) + 6.0 / 7 * pow(2, 100);

    std::cout << std::endl << std::endl << std::endl;
    std::cout << "Значение a_100: " << a_100 << std::endl;

    return 0;
    

    
}


