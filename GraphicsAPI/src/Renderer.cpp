//
//  Renderer.cpp
//  GraphicAPI
//
//  Created by Jeb Collins on 2/12/21.
//

#include <stdio.h>
#include <thread>

#include "Renderer.hpp"





namespace rgl
{


//void Renderer::f(int ii)
//{
//    for (int jj = CS_; jj < CN_; ++jj)
//    {
//        sf::Color value = scene_.computePixelValue(ii,jj);
//        canvas_.setPixel(ii, jj, value);
//    }
//    
//}





/**
  \brief Draws the scene onto a sprite and displays it in the window.
 
 */
void Renderer::renderScene()
{
    // Fill in the screen pixels
    for (int ii = window->getCanvasE(); ii < window->getCanvasW(); ++ii)
    {
        for (int jj = window->getCanvasS(); jj < window->getCanvasN(); ++jj)
        {
            sf::Color value = scene->computePixelValue(ii,jj);

            window->setPixel(ii, jj, value);
        }
    }
    
    
    

    window->display();
}


/**
 \brief: Draws the scene onto a sprite and displays it in the window.  Function is threaded by assigning each row of pixels on the screen to a thread.
 */
//void Renderer::renderSceneThreaded()
//{
//    std::vector<std::thread> threads;
//    // Fill in the screen pixels
//    for (int ii = CE_; ii < CW_; ++ii)
//    {
////        for (int jj = CS_; jj < CN_; ++jj)
////        {
////            sf::Color value = scene_.computeValue(ii,jj);
////
////            canvas_.setPixel(ii, jj, value);
//            threads.push_back(std::thread(&Renderer::f,this, ii));
////        }
//    }
//    
//    for(auto& th : threads)
//    {
//        th.join();
//    }
//    
//    
//
//    canvas_.setScreenSprite(sprite_);
//    window_.draw(sprite_);
//    
//    
//    window_.display();
//
//}


} // rgl namespace





