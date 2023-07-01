#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace ma
{
	
    //Класс персонажа 
    class Player
    {
    private:
        sf::FloatRect m_rect;
        float m_currentFrame;//Текущий кадр
        //int m_ground = 375;//Земля
        float m_dx, m_dy;//Скорость 
        bool m_onGround;//Проверяет находимся ли мы на земле
        sf::Sprite m_sprite;//Загружаем картинку
    public:
        Player(sf::Texture& image);
        float GetSpeedX();
        void SetSpeedX(float dx);
        float GetSpeedY();
        void SetSpeedY(float dy);
        void SetOnGround(bool position);
        bool GetOnGround();
        sf::Sprite GetSprite();
        void Movement(float time);
        void interactionWithMap(int dir);
    };
}