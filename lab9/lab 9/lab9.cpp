
//Найти объем куба.

#include <iostream>
//Класс содержащий информацию о кубе
class Cube
{
private:
    unsigned int m_sides; //СторнЫ
public:
    //Принимает значения высоты и сторон 
    Cube(unsigned int sides)
    {
        m_sides = sides;
    }
    //Возвращает значение объема 
    unsigned int CubeArea()
    {
        return (m_sides*m_sides*m_sides);
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Введите стороны куба" << std::endl;
    int K;//Принимает значение сторон куба
    std::cin >> K;
    if (K > 0)
    {
        std::cout << std::endl;
        Cube Cube(K);
        std::cout << "Объем куба:" << " ";
        std::cout << Cube.CubeArea() << std::endl;
    }
}

