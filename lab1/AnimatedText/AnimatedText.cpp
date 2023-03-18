

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <windows.h>

class AnimatedText 
{
private:
    std::string text;
    int duration;//отвечает за время вывода всей строки
    int CurrentDuration = 0;

public:
    AnimatedText(const std::string& m_text, const int& m_duration) 
    {
        text = m_text;
        duration = m_duration;
    }

    std::string Animation() //Отвечает за вывод каждой буквы отдельно 
    {
        CurrentDuration++;
        std::string out = text.substr(0, CurrentDuration);//substr возвращает подстроку начиная с символа с индексом 0 и до CurrentDuration
        return out;
    }


    ~AnimatedText()
    {

    }
};



int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");//задаем размер окна 

    std::string text = "Hello, world!";
    int duration = 13; //Отвечает за скорость вывода 
    int c = 0;//счетчик

    AnimatedText animatedText(text, duration);

    sf::Font font;//содержит информацию о шрифте 
    font.loadFromFile("C:\\Users\\Andrew\\source\\repos\\AnimatedText\\AnimatedText\\Decrypted.ttf");//файл содержащий шрифт
    sf::Text TEXT;//содержится вся инфрмация о тексте 
    TEXT.setColor(sf::Color::Red);//задаем цвет 
    TEXT.setFont(font);//передаем шрифт в переменную 
    TEXT.setPosition(200, 200);//задаем начальную позицию 

    //основной цикл, отвечает за вывод на экран 
    while (window.isOpen())
    {
        sf::Event event;

        for (int i = 0; i < (duration); i++)
        {
            c++;
            TEXT.setString(animatedText.Animation());
            window.draw(TEXT);
            window.display();
            Sleep(1000);//задержка на 1 секунду между выводом каждой буквы 
        }
        //как только цикл выполняется 13 раз окно закрывается 
        if (c == duration) 
        {
            Sleep(500);//задержка на 0,5 секунд перед закрытием окна 
            window.close();
        }


    }

    return 0;
}






