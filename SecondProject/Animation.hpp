#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

namespace ma
{ 
    //Класс который отвечает за основную анимацию
    class Animation
    {
    private:
        int m_width, m_height;
        std::string m_caption;
        sf::RenderWindow* m_window = nullptr;
    public:
        Animation();
        ~Animation();
        void SetCaption(const std::string& caption);
        void SetResolution(int width, int height);
        void Setup();
        void Run();
    };
}
