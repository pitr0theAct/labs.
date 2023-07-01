#include <iostream>
#include "Animation.hpp"
#include "Player.hpp"
#include "SFML/Graphics.hpp"




int main()
{

    ma::Animation animation;
    animation.SetCaption("Animation");
    animation.SetResolution(1000, 500);
    animation.Setup();
    animation.Run();

}


