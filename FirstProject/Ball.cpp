#include "Ball.hpp"
#include "Animation.hpp"

namespace ma

{

	Ball::Ball(Point p0, Point velocity, float r, sf::Color color)
	{
		m_p0 = p0;
		m_velocity = velocity;
		m_r = r; m_shape = new sf::CircleShape(m_r);
		m_shape->setFillColor(sf::Color::White);
		m_shape->setOrigin(m_r, m_r);
		m_shape->setFillColor(color);
	}
		

		 
		Ball::~Ball()
		{
			delete m_shape;
		}

		//Метод движения шариков
		void Ball::Move(double dt)
		{
			m_p0.x += m_velocity.x * dt;
			m_p0.y += m_velocity.y * dt;
			m_shape->setPosition(m_p0.x, m_p0.y);
		}

		//Ращзмер шара 
		sf::CircleShape* Ball::Get()
		{
			return m_shape;
		}


		Point Ball::GetPosition()
		{
			return m_p0;
		}


		float Ball::Radius()
		{
			return m_r;
		}


		void Ball::setVelocity(Point velocity)
		{
			m_velocity = velocity;
			//std::cout << m_velocity.x << std::endl;
			//std::cout << m_velocity.y << std::endl;
		}


		Point Ball::GetVelocity()
		{
			return m_velocity;
		}
}