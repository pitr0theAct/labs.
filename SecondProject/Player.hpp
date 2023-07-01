#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace ma
{
	
    //����� ��������� 
    class Player
    {
    private:
        sf::FloatRect m_rect;
        float m_currentFrame;//������� ����
        //int m_ground = 375;//�����
        float m_dx, m_dy;//�������� 
        bool m_onGround;//��������� ��������� �� �� �� �����
        sf::Sprite m_sprite;//��������� ��������
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