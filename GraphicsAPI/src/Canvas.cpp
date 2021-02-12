//
//  Screen.cpp
//  GraphicAPI
//
//  Created by Jeb Collins on 2/9/21.
//

#include <stdio.h>

#include "Canvas.hpp"


Canvas::Canvas(int Sw, int Sh)
{
    Sw_ = Sw;
    Sh_ = Sh;
    
    screenImage_.create(Sw_, Sh_, sf::Color::Blue);
}


void Canvas::setPixel(int x, int y, sf::Color color)
{
    int Sx = 0.5*Sw_ + x;
    int Sy = 0.5*Sh_ - y;
    
    screenImage_.setPixel(Sx, Sy, color);
}


void Canvas::setScreenSprite(sf::Sprite& sprite)
{
    screenTexture_.loadFromImage(screenImage_);
    sprite.setTexture(screenTexture_);
    
}
