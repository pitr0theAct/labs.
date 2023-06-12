
#include <iostream>
#include <string>
#include <vector>

//Класс перечисления
enum class Color
{
    PINK,
    WHITE,
    GREEN
};


//Базовый класс 
class Figure
{
private:
    //Координаты по x и y
    int m_x;
    int m_y;
    Color m_color;//Цвет

public:
    //Конструктор 
    Figure(int x, int y, Color color) : m_x(x), m_y(y), m_color(color) {}

};


//Класс потомок(треугольник)
class Triangle: public Figure 
{
private:
    //Три стороны треугольника
    int m_a;
    int m_b;
    int m_c;
public:
    //Конструктор 
    Triangle(int x, int y, Color color, int a, int b, int c) : Figure(x, y, color), m_a(a), m_b(b), m_c(c) {}
    
    //Метод который отвечает за нахождение площади
    void Square() 
    {
        //p - Полупериметр
        double p = (m_a + m_b + m_c) / 2;
        //По формуле Герона: sqrt(p * (p - m_a) * (p - m_b) * (p - m_c))
        std::cout << "Square of Triangle : " << sqrt(p * (p - m_a) * (p - m_b) * (p - m_c)) << std::endl;
    }
};


//Класс потомок(прямоугольник)
class Rectangle: public Figure 
{
private:
    int m_a;//Длина прямоугольника
    int m_b;//Ширина прямоугольника 
public:
    //Конструктор 
    Rectangle(int x, int y, Color color, int a, int b) : Figure(x, y, color), m_a(a), m_b(b) {}

    //Метод который отвечает за нахождение площади
    void Square() 
    {
        std::cout << "Square of Rectangle : " << m_a * m_b << std::endl;
    }
};


//Класс потомок(круг)
class Circle: public Figure 
{
private:
    int m_r;//Радиус круга 
    double PI = 3.14;

public:
    //Конструктор
    Circle(int x, int y, Color color, int r) : Figure(x, y, color), m_r(r) {}

    //Метод который отвечает за нахождение площади
    void Square() 
    {
        std::cout << "Square of Circle : " << PI * (m_r * m_r) << std::endl;
    }
};



int main()
{
    Triangle triangle(0, 0, Color::PINK,3, 4, 5);
    triangle.Square();
    std::cout << std::endl;


    Rectangle rectangle(0, 0, Color::WHITE, 6, 10);
    rectangle.Square();
    std::cout << std::endl;


    Circle circle(0, 0, Color::GREEN, 10);
    circle.Square();
    std::cout << std::endl;

}