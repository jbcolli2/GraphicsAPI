//
//  main.cpp
//  GraphicAPI
//
//  Created by Jeb Collins on 2/7/21.
//

#include <iostream>
#include <chrono>

#include "Canvas.hpp"
#include "Scene.hpp"

#include <SFML/Graphics.hpp>

int main(int argc, const char * argv[]) {
    
    constexpr int Sw = 801;
    constexpr int Sh = 801;
    sf::RenderWindow window(sf::VideoMode(Sw, Sh), "My window");
    
    sf::Sprite sprite;
    Screen screen(Sw, Sh);
    Scene scene(Sw, Sh);
    
    int circ_x = -Sw/2;
    int circ_y = -Sh/2;
    // run the program as long as the window is open
    
    

    while (window.isOpen())
    {
        auto start = std::chrono::steady_clock::now();
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // Fill in the screen pixels
        for (int ii = -Sw/2; ii < Sw/2; ++ii)
        {
            for (int jj = -Sh/2; jj < Sh/2; ++jj)
            {
                sf::Color value = scene.computeValue(ii,jj);

                screen.setPixel(ii, jj, value);
            }
        }
        
        

//        window.clear(sf::Color::Black);
        screen.setScreenSprite(sprite);
        window.draw(sprite);
        
        
        window.display();
        
        ++circ_x;
        ++circ_y;
        
        auto end = std::chrono::steady_clock::now();
        
        std::cout<< "Time elasped in milliseconds = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
        
    }

    return 0;
}
