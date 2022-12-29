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
	class Ball
	{
	private:
		Point m_p0;
		Point m_velocity;
		float m_r;
		sf::CircleShape* m_shape;
	public:
		Ball(Point p0, Point velocity, float r, sf::Color color);
		~Ball();
		void Move(double dt);
		sf::CircleShape* Get();
		Point GetPosition();
		float Radius();
		void setVelocity(Point velocity);
		Point GetVelocity();
		
	};
}