
#include "Ball.hpp"
#include "Animation.hpp"
using namespace ma;


Animation::Animation()
{
	int m_width, m_height;
	std::string m_caption;
	sf::RenderWindow* m_window;
}

Animation::~Animation()
{
	delete m_window;
}

//Метод который задает название 
void Animation::SetCaption(const std::string& caption)
{
	m_caption = caption;
}

//Метод который задает высоту и ширину окна
void Animation::SetResolution(int width, int height)
{
	m_width = width;
	m_height = height;
}

//Генерация окна 
void Animation::Setup()
{
	m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), m_caption);
}

//Основная анимация
void Animation::Run()
{
	//Вектор содержаший инфомацию о шариках
	std::vector <ma::Ball*> balls;
	balls.push_back(new ma::Ball({ 0,0 }, { 40,40 }, 50, sf::Color::White));
	balls.push_back(new ma::Ball({ 0,0 }, { 40,40 }, 45, sf::Color::Green));
	balls.push_back(new ma::Ball({ 0,0 }, { 40,40 }, 25, sf::Color::Red));
	balls.push_back(new ma::Ball({ 0,0 }, { 40,40 }, 15, sf::Color::Blue));
	balls.push_back(new ma::Ball({ 0,0 }, { 40,40 }, 5, sf::Color::Black));

	sf::Clock timer;



	while (m_window->isOpen())
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window->close();
			}
		}

		sf::Time dt = timer.restart();
		//Движение шариков 
		for (int i = 0; i < balls.size(); i++)
		{
			balls[i]->Move(dt.asSeconds());
		}

		//Столкновение с нижней границой 
		for (int i = 0; i < balls.size(); i++)
		{
			Point p = balls[i]->GetPosition();
			float r = balls[i]->Radius();

			if (p.y + r > m_height)
			{
				Point velocity = balls[i]->GetVelocity();
				balls[i]->setVelocity({ velocity.x,-velocity.y });
				//std::cout << velocity.x << " " << -velocity.y << std::endl;
			}
		}

		//Столкновение с верхней границей
		for (int i = 0; i < balls.size(); i++)
		{
			Point p = balls[i]->GetPosition();
			float r = balls[i]->Radius();
			if (p.y <= 0)
			{
				Point velocity = balls[i]->GetVelocity();
				balls[i]->setVelocity({ velocity.x,-velocity.y });
			}
		}

		//Столкновение с правой границой 
		for (int i = 0; i < balls.size(); i++)
		{
			Point p = balls[i]->GetPosition();
			float r = balls[i]->Radius();
			if (p.x + r > m_width)
			{
				Point velocity = balls[i]->GetVelocity();
				balls[i]->setVelocity({ -velocity.x,velocity.y });
			}
		}

		//Столкновение с левой границей
		for (int i = 0; i < balls.size(); i++)
		{
			Point p = balls[i]->GetPosition();
			float r = balls[i]->Radius();
			if (p.x <= 0)
			{
				Point velocity = balls[i]->GetVelocity();
				balls[i]->setVelocity({ -velocity.x,velocity.y });
			}
		}

		m_window->clear(sf::Color(128, 106, 255));
		//Вывод шариков 
		for (int i = 0; i < balls.size(); i++)
		{
			m_window->draw(*balls[i]->Get());
		}
		m_window->display();
	}

	for (int i = 0; i < balls.size(); i++)
	{
		delete balls[i];
	}
	}
