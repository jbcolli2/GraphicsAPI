//
//  main.cpp
//  GraphicAPI
//
//  Created by Jeb Collins on 2/7/21.
//

#include <iostream>
#include <chrono>

//#include "Canvas.hpp"
//#include "Scene.hpp"
#include "Renderer.hpp"

#include <SFML/Graphics.hpp>

int main(int argc, const char * argv[]) {
    
    int Sw = 1201;
    int Sh = 1201;
    
    bool rendered = false;
    
    Renderer renderer(Sw, Sh);
    
    // run the program as long as the window is open
    while (renderer.getWindowOpen())
    {
        
        
        // check all the window's events that were triggered since the last iteration of the loop
        renderer.pollEvents();
        
        
        // Only render the scene once, not every 1/60 of a second
        if(!rendered)
        {
            auto start = std::chrono::steady_clock::now();
            
            renderer.renderScene();
            rendered = true;
            
            auto end = std::chrono::steady_clock::now();
            std::cout<< "Time elasped in milliseconds = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
        }
        
        
        
        
        
        
        
    }

    return 0;
}
