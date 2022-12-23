//Вам даны два объекта, которые связаны между собой. Необходимо создать 2 класса, описывающие эти объекты и принадлежность 2го объекта 1ому.
//Преподаватель и студенты.


#include <iostream>
#include <string>
#include <vector>
//Класс содержащий информацию о студенте 
class Student
{
private:
    int m_age;
    std::string m_name;
public:
    Student(std::string name, int age)
    {
        m_name = name;
        m_age = age;
    }
    //Возвращает имя 
    std::string GetName()
    {
        return m_name;
    }
    //Возвращает возраст 
    int GetAge()
    {
        return m_age;
    }
};

//Класс содержащий информацию о преподавателе 
class Theacher
{
private:
    //Вектор с иноформацией о студентах 
    std::vector <Student*> m_Students;
public:
    //Добовление инормации о студентах в вектор 
    void AddStudent(Student* Student)
    {
        m_Students.push_back(Student);
    }
    //Вывод иноформции о студентах
    void PrintStudnets()
    {
        for (int i = 0; i < m_Students.size(); i++)
        {
            std::cout << m_Students[i]->GetName() << " ";
            std::cout << m_Students[i]->GetAge() << std::endl;
        }
    }

};

int main()
{
    //Информация о студентах
    Student Student1("Andrew", 18);
    Student Student2("Dima", 21);
    Student Student3("Nikita", 17);
    Theacher Theacher1;
    //Передача информации о студентах 
    Theacher1.AddStudent(&Student1);
    Theacher1.AddStudent(&Student2);
    Theacher1.AddStudent(&Student3);
    //Вывод 
    Theacher1.PrintStudnets();
}
