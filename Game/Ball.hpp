#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace ma
{
	struct Point
	{
		float x;
		float y;
	};
	//Класс содержащий информацию о шарике
	class Ball
	{
	private: 
		Point m_p0;
		Point m_velocity;
		float m_r;
		sf::CircleShape* m_shape;
	public:
		Ball(Point p0,Point velocity,float r,sf::Color color)
		{
			m_p0 = p0;
			m_velocity = velocity;
			m_r = r;
			m_shape = new sf::CircleShape(m_r);
			m_shape->setFillColor(sf::Color::White);
			m_shape->setOrigin(m_r, m_r);
			m_shape->setFillColor(color);
		}

		//Деструктор 
		~Ball()
		{
			delete m_shape;
		}
		
		//Метод движения шариков
		void Move(double dt)
		{
			m_p0.x += m_velocity.x * dt;
			m_p0.y += m_velocity.y * dt;
			m_shape->setPosition(m_p0.x, m_p0.y);
		}
		
		//Ращзмер шара 
		sf::CircleShape* Get()
		{
			return m_shape;
		}
		

		Point GetPosition()
		{
			return m_p0;
		}

		
		float Radius()
		{
			return m_r;
		}

		
		void setVelocity(Point velocity)
		{
			m_velocity = velocity;
			//std::cout << m_velocity.x << std::endl;
			//std::cout << m_velocity.y << std::endl;
		}
		
		
		Point GetVelocity()
		{
			return m_velocity;
		}
	};
}