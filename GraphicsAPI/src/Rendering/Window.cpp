//
//  Screen.cpp
//  GraphicAPI
//
//  Created by Jeb Collins on 2/9/21.
//

#include <stdio.h>

#include "Window.hpp"

namespace rgl
{

Window::Window(int Sw, int Sh) : window(sf::VideoMode(Sw, Sh), "Graphics Renderer")
{
    this->Sw = Sw;
    this->Sh = Sh;
    this->CE = -Sw/2;
    this->CW = Sw/2;
    this->CN = Sh/2;
    this->CS = -Sh/2;

    screenImage.create(this->Sw, this->Sh, sf::Color::Blue);
}




/**
 \brief: Checks window events each loop.  Currently used to close window.
 */
void Window::pollEvents()
{
    // check all the window's events that were triggered since the last iteration of the loop
    
    while (window.pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            window.close();
    }

}





void Window::setPixel(int x, int y, sf::Color color)
{
    int Sx = 0.5*Sw + x;
    int Sy = 0.5*Sh - y;
    
    screenImage.setPixel(Sx, Sy, color);
}






void Window::display()
{
    this->screenTexture.loadFromImage(screenImage);
    this->screenSprite.setTexture(screenTexture);
    
    
    this->window.draw(this->screenSprite);
    
    
    this->window.display();
    
}



} // Namespace rgl
