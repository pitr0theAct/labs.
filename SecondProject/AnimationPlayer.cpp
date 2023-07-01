#include "Player.hpp"
#include "Animation.hpp"

using namespace ma;


const int HEIGHT_MAP = 16;//������ ����� ������
const int WIDTH_MAP = 31;//������ ����� ������ 


// �����
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
    //����� ���������� ���������� � ������ 

    //����������� 
    Player::Player(sf::Texture& image)
    {
        m_sprite.setTexture(image);
        m_sprite.setTextureRect(sf::IntRect(0, 0, 95, 130));
        m_rect = sf::FloatRect(0, 0, 95, 130);

        m_onGround = true;
        m_dx = m_dy = 0;
        m_currentFrame = 0;
    }

    //���������� �������� �� x
    float Player::GetSpeedX()
    {
        return m_dx;
    }

    //������ �������� �� x
    void Player::SetSpeedX(float dx)
    {
        m_dx = dx;
    }

    //���������� �������� �� y
    float Player::GetSpeedY()
    {
        return m_dy;
    }

    //������ �������� �� y
    void Player::SetSpeedY(float dy)
    {
        m_dy = dy;
    }

    //������ ���������� m_onGround 
    void Player::SetOnGround(bool position)
    {
        m_onGround = position;
    }

    //���������� ���������� m_onGround
    bool Player::GetOnGround()
    {
        return m_onGround;
    }

    //��������� ������
    sf::Sprite Player::GetSprite()
    {
        return m_sprite;
    }





    //����� ������� �������� �� �������� � �������� 
    void Player::Movement(float time)
    {
        m_rect.left += m_dx * time;//�������� �� x 

        interactionWithMap(0);//�������������� � ������ �� x


        if (!m_onGround)//���� �� �� ����� �� ������ ���� 
        {
            m_dy = m_dy + 0.0005 * time;

        }

        m_rect.top += m_dy * time;//�������� �� y

        m_onGround = false;

        interactionWithMap(1);//�������������� � ������ �� y


        if (m_rect.top == 0)//���� �������� ��������� � ����� 0 �� y
        {
            m_rect.top = 375;//�� �� y ������������ �� ����� 
        }

        if (m_rect.left == 0)////���� �������� ��������� � ����� 0 �� x
        {
            m_rect.left = 50;//�� �� y ������������ � ����� 
        }




        //��������
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


        //������� ������ � ������� x, y
        m_sprite.setPosition(m_rect.left, m_rect.top);



        m_dx = 0;


    }

    //D������������� � ������
    void Player::interactionWithMap(int dir)
    {
        for (int i = m_rect.top / 32; i < (m_rect.top + m_rect.height) / 32; i++)//���������� �� ��������, �������������� � �������,, �� ���� �� ���� ����������� ������� 32*32, ������� �� ����������
            for (int j = m_rect.left / 32; j < (m_rect.left + m_rect.width) / 32; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������,
                //� ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������).
                //� j<(m_rect.left + m_rect.width) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������.
                //����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
            {
                if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
                {
                    if ((m_dx > 0) && (dir == 0))
                    {
                        m_rect.left = j * 32 - m_rect.width;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������

                    }
                    if ((m_dx < 0) && (dir == 0))
                    {
                        m_rect.left = j * 32 + 32;//���������� ���� �����

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






//����� ���������� �� �������� �������� 


    //�����������
    Animation::Animation() = default;

    //���������� 
    Animation::~Animation()
    {
        if (m_window != nullptr)
        {
            delete m_window;
        }
    }

    //�������� ���� 
    void Animation::SetCaption(const std::string& caption)
    {
        m_caption = caption;
    }

    //������ ����
    void Animation::SetResolution(int width, int height)
    {
        m_width = width;
        m_height = height;
    }


    //�������� ����
    void Animation::Setup()
    {
        m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), m_caption);
    }


    //����� ������� �������� �� ������ ���������
    void Animation::Run()
    {

        //������������ ��� �������� �������� �� �������
        sf::Clock clock1;






        //�������� ������ ��� ������ fps
        sf::Font text;
        text.loadFromFile("intelone.otf");


        //������������ ��� ���������� �������� fps 
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

        //������������ ��� ���������� �������� �������
        //float frame = 0;


        //�������� ������� ��������
        sf::Texture Picture;
        Picture.loadFromFile("images/htmlimage.png");

        Player player(Picture);





        sf::Image map_image;//������ ����������� ��� �����
        map_image.loadFromFile("images/map.png");//��������� ���� ��� �����
        sf::Texture map;//�������� �����
        map.loadFromImage(map_image);//�������� �������� ���������
        sf::Sprite sprite_map;//������ ������ ��� �����
        sprite_map.setTexture(map);//�������� �������� ��������



        //������ ��������� ������� �������
        player.GetSprite().setPosition(0, 375);


        //�������� ���� ���������
        while (m_window->isOpen())
        {
            //����������� ��� �������� ���������� �� �������
            float time = clock1.getElapsedTime().asMicroseconds();
            clock1.restart();
            time = time / 600;



            sf::Event event;
            while (m_window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    m_window->close();
            }



            //������� fps
            sf::Time elapsed = clock.getElapsedTime();
            if (elapsed.asMilliseconds() >= 100)
            {
                fps = count_fps;
                count_fps = -1;
                clock.restart();
            }
            fps_text.setString("FPS: " + std::to_string(fps));
            count_fps++;


            //�������� ������
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {

                player.SetSpeedX(0.1);

            }


            //�������� �����
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {

                player.SetSpeedX(-0.1);

            }

            //������
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                if (player.GetOnGround())
                {
                    player.SetSpeedY(-0.4);
                    player.SetOnGround(false);
                }
            }

            player.Movement(time);

            //�������� ���� ����� �������� ������
            m_window->clear(sf::Color::White);


            //������ �����
            for (int i = 0; i < HEIGHT_MAP; i++)//������ ����� 
            {
                for (int j = 0; j < WIDTH_MAP; j++)//������ �����
                {
                    if (TileMap[i][j] == ' ')
                    {
                        sprite_map.setTextureRect(sf::IntRect(0, 0, 32, 32)); //���� ��������� ������ ������, �� ������ 1� ���������
                    }

                    if ((TileMap[i][j] == '0'))
                    {
                        sprite_map.setTextureRect(sf::IntRect(64, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
                    }

                    if ((TileMap[i][j] == '1'))
                    {
                        sprite_map.setTextureRect(sf::IntRect(32, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
                        m_window->draw(Mission_text);
                    }



                    sprite_map.setPosition(j * 32, i * 32);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������

                    m_window->draw(sprite_map);//������ ���������� �� �����
                }
            }




            //����� fps
            m_window->draw(fps_text);

            //����� �������
            m_window->draw(player.GetSprite());

            //�������� ��� ��������
            m_window->display();
        }

    }
