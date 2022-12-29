#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
namespace ma
{
	class Animation
	{
	private:
		int m_width, m_height;
		std::string m_caption;
		sf::RenderWindow* m_window;
	public:
		Animation();
		~Animation();
		void SetCaption(const std::string& caption);
		void SetResolution(int width, int height);
		void Setup();
		void Run();
	};
}
