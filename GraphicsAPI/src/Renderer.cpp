//
//  Renderer.cpp
//  GraphicAPI
//
//  Created by Jeb Collins on 2/12/21.
//

#include <stdio.h>
#include <thread>

#include "Renderer.hpp"



/*
 \brief: Initializes all the variables to run the renderer program
 
 \parameters: Sw - width in pixels of the window
            Sh - height in pixels of the window
 */
Renderer::Renderer(int Sw, int Sh) : window_(sf::VideoMode(Sw, Sh), "Graphics Renderer"),
                                    canvas_(Sw,Sh), scene_(Sw/2, Sh/2)
{
    Sw_ = Sw;
    Sh_ = Sh;
    CE_ = -Sw/2;
    CW_ = Sw/2;
    CN_ = Sh/2;
    CS_ = -Sh/2;
    
    
}



/*
 \brief: Checks window events each loop.  Currently used to close window.
 */
void Renderer::pollEvents()
{
    // check all the window's events that were triggered since the last iteration of the loop
    
    while (window_.pollEvent(event_))
    {
        // "close requested" event: we close the window
        if (event_.type == sf::Event::Closed)
            window_.close();
    }

}


void Renderer::f(int ii)
{
    for (int jj = CS_; jj < CN_; ++jj)
    {
        sf::Color value = scene_.computeValue(ii,jj);
        canvas_.setPixel(ii, jj, value);
    }
    
}





/**
 \brief: Draws the scene onto a sprite and displays it in the window.
 */
void Renderer::renderScene()
{
    // Fill in the screen pixels
    for (int ii = CE_; ii < CW_; ++ii)
    {
        for (int jj = CS_; jj < CN_; ++jj)
        {
            sf::Color value = scene_.computeValue(ii,jj);

            canvas_.setPixel(ii, jj, value);
        }
    }
    
    
    

    canvas_.setScreenSprite(sprite_);
    window_.draw(sprite_);
    
    
    window_.display();

}


/**
 \brief: Draws the scene onto a sprite and displays it in the window.  Function is threaded by assigning each row of pixels on the screen to a thread.
 */
void Renderer::renderSceneThreaded()
{
    std::vector<std::thread> threads;
    // Fill in the screen pixels
    for (int ii = CE_; ii < CW_; ++ii)
    {
//        for (int jj = CS_; jj < CN_; ++jj)
//        {
//            sf::Color value = scene_.computeValue(ii,jj);
//
//            canvas_.setPixel(ii, jj, value);
            threads.push_back(std::thread(&Renderer::f,this, ii));
//        }
    }
    
    for(auto& th : threads)
    {
        th.join();
    }
    
    

    canvas_.setScreenSprite(sprite_);
    window_.draw(sprite_);
    
    
    window_.display();

}








/*
 \brief: Return the window object for the main loop
 */
bool Renderer::getWindowOpen()
{
    return window_.isOpen();
}
