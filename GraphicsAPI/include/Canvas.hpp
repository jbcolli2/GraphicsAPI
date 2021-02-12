//
//  Screen.hpp
//  GraphicAPI
//
//  Created by Jeb Collins on 2/9/21.
//

#ifndef Screen_h
#define Screen_h

#include <SFML/Graphics.hpp>


class Canvas
{
    // The SFML object needed to draw to the window
    sf::Image screenImage_;
    sf::Texture screenTexture_;
    sf::Sprite screenSprite_;
    
    int Sw_, Sh_;  // number of pixels on the screen in each direction
    
public:
    Canvas(int Sw, int Sh);
    
    void setPixel(int x, int y, sf::Color color);
    
    void setScreenSprite(sf::Sprite& sprite);
    
};





#endif /* Screen_h */
