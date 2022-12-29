

#include "Ball.hpp"
#include "Animation.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    ma::Animation Animation;
    Animation.SetCaption("IDK");
    Animation.SetResolution(500, 200);
    Animation.Setup();
    Animation.Run();
}



