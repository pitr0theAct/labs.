

#include <iostream>

class Complex 
{
private:
    double m_a;
    double m_b;
public:
    
    Complex()
    {
        m_a = 0;
        m_b = 0;
    }
    
    //Базовый конструктор
    Complex(double a, double b)
    {
        m_a = a;
        m_b = b;
    }

    //Конструктор копирования
    Complex(const Complex& z) = default;
    
    //Оператор присваивания
    Complex& operator=(Complex z)
    {
        std::swap(m_a, z.m_a);
        std::swap(m_b, z.m_b);
        return *this;
    }

    //Деструктор
    ~Complex() = default;

    //Оператор +=
    Complex& operator +=(const Complex& z)
    {
        (*this).m_a += z.m_a;
        (*this).m_b += z.m_b;
        return *this;
    }

    //Оператор +
    Complex operator+(const Complex& z)
    {
        Complex temp = *this;
        temp += z;
        return temp;
    }

    //Оператор *= 
    Complex& operator *= (const Complex& z) 
    {
        double new_a, new_b;
        new_a = (m_a * z.m_a) - (m_b * z.m_b);
        new_b = (m_a * z.m_b) + (m_b * z.m_a);
        m_a = new_a;
        m_b = new_b;
        return *this;
    }
     
    //Оператор * 
    Complex operator * (const Complex& z) 
    {
        Complex result;
        result.m_a = (m_a * z.m_a) - (m_b * z.m_b);
        result.m_b = (m_a * z.m_b) + (m_b * z.m_a);
        return result;
    }

    //Префиксный оператор ++
    Complex& operator++()
    {
        m_a++;//увиличиваем a на 1
        return *this;//возвращаем объект класса после увеличения
    }

    //Постфиксный оператор ++
    Complex& operator++(int)// int нужен для отличия от префиксного инкремента
    {
        Complex temp(*this);
        m_a++;//увиличиваем a на 1
        return temp;//возвращаем объект класса до увеличения
    }

    //Оператор ввода 
    friend std::istream& operator >> (std::istream& in, Complex& z) 
    {
        in >> z.m_a;
        in >> z.m_b;
        return in;
    }

    //Оператор вывода
    friend std::ostream& operator << (std::ostream& out, const Complex& z)
    {
        out << z.m_a << "+" << z.m_b << "i" << std::endl;
        return out;
    }
    
};

int main()
{
    Complex z1(1,2), z2(3,4);
    

    Complex z3 = z1 + z2;
    std::cout << "z1 + z2:  ";
    std::cout << z3 << std::endl;


    z1 += z2;
    std::cout << "z1 += z2:  ";
    std::cout << z1 << std::endl;

    
    z3 = z1 * z2;
    std::cout << "z1 * z2:  ";
    std::cout << z3 << std::endl;


    z1 *= z2;
    std::cout << "z1 *= z2:  ";
    std::cout << z1 << std::endl;

}


