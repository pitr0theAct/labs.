
#include <iostream>

class String
{
private:
    size_t m_size;
    char* m_str = nullptr;
public:

    String() = default;//Используется для реализации оператора сложения 

    //Конструктор
    String(const char* str)
    {
        m_size = strlen(str);//Длина строки
        m_str = new char[m_size+1];//Выделение памяти под строку 
        std::copy(str, str + m_size+1, m_str);
    }
    

    //Конструктор копирования 
    String(const String& other)
    {
        m_size = other.m_size;
        m_str = new char[m_size + 1];
        std::copy(other.m_str, other.m_str + other.m_size, m_str);
    }

    //Оператор присваивания 
    String& operator=(const String& other) 
    {
        delete[] m_str;
        m_size = other.m_size;
        m_str = new char[m_size+1];
        std::copy(other.m_str, other.m_str + other.m_size, m_str);
        return *this;//Разыменование потому что this - указатель
    }

    //Деструктор 
    ~String()
    {
        //Изначально m_str = nullptr
        if (m_str != nullptr)
        {
            delete[] m_str;
        }
    }

    //Оператор + 
    String operator+(const String& other) const 
    {
        String result;
        result.m_size = m_size + other.m_size;
        result.m_str = new char[result.m_size + 1];
        strcpy_s(result.m_str, result.m_size + 1, m_str);//strcpy копирует строку  
        strcat_s(result.m_str, result.m_size + 1, other.m_str);//strcat добавляет копию строки в конец другой строки
        return result;
    }

    //Оператор +=
    String& operator +=(const String& other) 
    {
        char* temp = new char[m_size + other.m_size + 1];
        strcpy_s(temp, m_size + other.m_size + 1, m_str);
        strcat_s(temp, m_size + other.m_size + 1, other.m_str);
        delete[] m_str;
        m_str = temp;
        m_size = m_size + other.m_size;
        return *this;
    }

    //Оператор [] 
    char& operator[](size_t i)
    {
        return m_str[i];
    }

    //Операторы <, >, ==
    bool operator == (const String& other)
    {
        return std::strcmp(m_str, other.m_str) == 0;//strcmp сравнивает строки, если первая строка меньше второй, функция возращает число меньше нуля
    }

    bool operator < (const String& other)
    {
        return std::strcmp(m_str, other.m_str) < 0;
    }

    bool operator > (const String& other)
    {
        return std::strcmp(m_str, other.m_str) > 0;
    }

    //Оператор вывода 
    friend std::ostream& operator<<(std::ostream& out, const String& str)
    {
        for (int i = 0; i < str.m_size; i++) 
        {
            out << str.m_str[i];
        }
        str.m_str[str.m_size] = '\0';//Добавление терминирующего символа
        return out;
    }
    

    //Оператор ввода
    friend std::istream& operator>>(std::istream& in, String& str)
    {
        str.m_size = 1;
        in >> str.m_str;
        while (str.m_str[str.m_size]) 
        {
            str.m_size++;
        }
        return in;
    }

    //Метод find 
    int find(char c)
    {
        for (int i = 0; i < m_size+1; i++)
        {
            if (m_str[i] == c)
            {
                return i;
            }
            else
            {
                return -1;//В случае если символ не найден 
            }
        }
    }

    //Длинна 
    size_t Length()
    {
        return m_size;
    }
    
    //Метод c_str 
    char* c_str()
    {
        return m_str;
    }

    //Метод at 
    char& at(int i)
    {
        if ((i >= 0) && (i < m_size))
        {
            return m_str[i];
        }
        else
        {
            return m_str[0];
        }
    }

    /*
    void Print()
    {
        for (int i = 0; i < m_size; i++)
        {
            std::cout << m_str[i];
        }
        std::cout << std::endl;
    }
    */
};



int main()
{
   String str1("Hello, ");
   String str2("World!");
   String str3;

   str1 += str2;
   str3=str1;
   String str4 = str2;
   
   std::cout << str4 << std::endl;
   std::cout << std::endl;
  
   //str3.Print();

   str3[5] = 'H';

   std::cout << str1 << std::endl;
   std::cout << std::endl;
   
   std::cout << str3 << std::endl;
   std::cout << std::endl;
   
   std::cout << str3.Length() << std::endl;
   std::cout << std::endl;
   
   std::cout << (str2 > str1) << std::endl;
   

}


