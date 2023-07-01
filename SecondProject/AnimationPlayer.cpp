#include "Player.hpp"
#include "Animation.hpp"

using namespace ma;


const int HEIGHT_MAP = 16;//размер карты высота
const int WIDTH_MAP = 31;//размер карты ширина 


// Карта
sf::String TileMap[HEIGHT_MAP] = {
    "0000000000000000000000000000000",
    "0                             0",
    "0                             0",
    "0                            10",
    "0                             0",
    "0                             0",
    "0                     11 000000",
    "0                  11 00      0",
    "0                  00         0",
    "0            11               0",
    "0            00               0",
    "0      11                     0",
    "0      00                     0",
    "0                             0",
    "0                             0",
    "0000000000000000000000000000000",
};





namespace ma
{
    //Класс содержащий информацию о игроке 

    //Конструктор 
    Player::Player(sf::Texture& image)
    {
        m_sprite.setTexture(image);
        m_sprite.setTextureRect(sf::IntRect(0, 0, 95, 130));
        m_rect = sf::FloatRect(0, 0, 95, 130);

        m_onGround = true;
        m_dx = m_dy = 0;
        m_currentFrame = 0;
    }

    //Возвращает скорость по x
    float Player::GetSpeedX()
    {
        return m_dx;
    }

    //Задает скорость по x
    void Player::SetSpeedX(float dx)
    {
        m_dx = dx;
    }

    //Возвращает скорость по y
    float Player::GetSpeedY()
    {
        return m_dy;
    }

    //Задает скорость по y
    void Player::SetSpeedY(float dy)
    {
        m_dy = dy;
    }

    //Задает переменную m_onGround 
    void Player::SetOnGround(bool position)
    {
        m_onGround = position;
    }

    //Возвращает переменную m_onGround
    bool Player::GetOnGround()
    {
        return m_onGround;
    }

    //Возврщает спрайт
    sf::Sprite Player::GetSprite()
    {
        return m_sprite;
    }





    //Метод который отвечает за движение и анимацию 
    void Player::Movement(float time)
    {
        m_rect.left += m_dx * time;//Движение по x 

        interactionWithMap(0);//взаимодействие с картой по x


        if (!m_onGround)//Если не на земле то падаем вниз 
        {
            m_dy = m_dy + 0.0005 * time;

        }

        m_rect.top += m_dy * time;//Движение по y

        m_onGround = false;

        interactionWithMap(1);//взаимодействие с картой по y


        if (m_rect.top == 0)//если персонаж находится в точке 0 по y
        {
            m_rect.top = 375;//То по y перемешаемся на землю 
        }

        if (m_rect.left == 0)////если персонаж находится в точке 0 по x
        {
            m_rect.left = 50;//То по y перемешаемся в право 
        }




        //Анимация
        m_currentFrame += 0.005 * time;
        if (m_currentFrame > 10)

        {
            m_currentFrame -= 10;

        }
        if (m_dx > 0)
        {
            m_sprite.setTextureRect(sf::IntRect(95 * static_cast<int>(m_currentFrame), 0, 95, 130));
        }

        if (m_dx < 0)
        {
            m_sprite.setTextureRect(sf::IntRect(95 * static_cast<int>(m_currentFrame) + 95, 0, -95, 130));
        }


        //Выводим спрайт в позицию x, y
        m_sprite.setPosition(m_rect.left, m_rect.top);



        m_dx = 0;


    }

    //Dзаимодействие с картой
    void Player::interactionWithMap(int dir)
    {
        for (int i = m_rect.top / 32; i < (m_rect.top + m_rect.height) / 32; i++)//проходимся по тайликам, контактирующим с игроком,, то есть по всем квадратикам размера 32*32, которые мы окрашивали
            for (int j = m_rect.left / 32; j < (m_rect.left + m_rect.width) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик,
                //с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах).
                //А j<(m_rect.left + m_rect.width) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем.
                //таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
            {
                if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
                {
                    if ((m_dx > 0) && (dir == 0))
                    {
                        m_rect.left = j * 32 - m_rect.width;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа

                    }
                    if ((m_dx < 0) && (dir == 0))
                    {
                        m_rect.left = j * 32 + 32;//аналогично идем влево

                    }
                    if ((m_dy > 0) && (dir == 1))
                    {
                        m_rect.top = i * 32 - m_rect.height;
                        m_dy = 0;
                        m_onGround = true;
                    }
                    if ((m_dy < 0) && (dir == 1))
                    {
                        m_rect.top = i * 32 + 32;
                        m_dy = 0;
                    }

                }

                if (TileMap[i][j] == '1')
                {
                    TileMap[i][j] = ' ';

                }

            }

    }



}






//Класс отвечающий за основную анимацию 


    //Конструктор
    Animation::Animation() = default;

    //Деструктор 
    Animation::~Animation()
    {
        if (m_window != nullptr)
        {
            delete m_window;
        }
    }

    //Название окна 
    void Animation::SetCaption(const std::string& caption)
    {
        m_caption = caption;
    }

    //Размер окна
    void Animation::SetResolution(int width, int height)
    {
        m_width = width;
        m_height = height;
    }


    //Создание окна
    void Animation::Setup()
    {
        m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), m_caption);
    }


    //Метод который отвечает за работу программы
    void Animation::Run()
    {

        //Используется для привязки движения ко времени
        sf::Clock clock1;






        //Загрузка шрифта для вывода fps
        sf::Font text;
        text.loadFromFile("intelone.otf");


        //Используется для реализации счетчика fps 
        sf::Clock clock;
        int fps = 0;
        int count_fps = 0;
        sf::Text fps_text;
        fps_text.setFont(text);
        fps_text.setFillColor(sf::Color::Green);
        fps_text.setCharacterSize(30);



        sf::Text Mission_text;
        Mission_text.setFont(text);
        Mission_text.setFillColor(sf::Color::White);
        Mission_text.setCharacterSize(20);
        Mission_text.setPosition(0, 30);
        Mission_text.setString("Misson: Collect the stones.");

        //Используется для реалезации анимации спрайта
        //float frame = 0;


        //Передаем спрайту текстуру
        sf::Texture Picture;
        Picture.loadFromFile("images/htmlimage.png");

        Player player(Picture);





        sf::Image map_image;//объект изображения для карты
        map_image.loadFromFile("images/map.png");//загружаем файл для карты
        sf::Texture map;//текстура карты
        map.loadFromImage(map_image);//заряжаем текстуру картинкой
        sf::Sprite sprite_map;//создаём спрайт для карты
        sprite_map.setTexture(map);//заливаем текстуру спрайтом



        //Задаем начальную позицию спрайта
        player.GetSprite().setPosition(0, 375);


        //Основной цикл программы
        while (m_window->isOpen())
        {
            //Использется для привязки движенения ко времени
            float time = clock1.getElapsedTime().asMicroseconds();
            clock1.restart();
            time = time / 600;



            sf::Event event;
            while (m_window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    m_window->close();
            }



            //Счетчик fps
            sf::Time elapsed = clock.getElapsedTime();
            if (elapsed.asMilliseconds() >= 100)
            {
                fps = count_fps;
                count_fps = -1;
                clock.restart();
            }
            fps_text.setString("FPS: " + std::to_string(fps));
            count_fps++;


            //Движение вправо
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {

                player.SetSpeedX(0.1);

            }


            //Движение влево
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {

                player.SetSpeedX(-0.1);

            }

            //Прыжок
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                if (player.GetOnGround())
                {
                    player.SetSpeedY(-0.4);
                    player.SetOnGround(false);
                }
            }

            player.Movement(time);

            //Отчистка окна путем заливыки цветом
            m_window->clear(sf::Color::White);


            //Рисуем карту
            for (int i = 0; i < HEIGHT_MAP; i++)//Высота карты 
            {
                for (int j = 0; j < WIDTH_MAP; j++)//Ширина карты
                {
                    if (TileMap[i][j] == ' ')
                    {
                        sprite_map.setTextureRect(sf::IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
                    }

                    if ((TileMap[i][j] == '0'))
                    {
                        sprite_map.setTextureRect(sf::IntRect(64, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
                    }

                    if ((TileMap[i][j] == '1'))
                    {
                        sprite_map.setTextureRect(sf::IntRect(32, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
                        m_window->draw(Mission_text);
                    }



                    sprite_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

                    m_window->draw(sprite_map);//рисуем квадратики на экран
                }
            }




            //Вывод fps
            m_window->draw(fps_text);

            //Вывод спрайта
            m_window->draw(player.GetSprite());

            //Показать все элементы
            m_window->display();
        }

    }
