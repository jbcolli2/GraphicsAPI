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
#include <nlohmann/json.hpp>

using namespace rgl;

int main(int argc, const char * argv[]) {
    
    int Sw = 1201;
    int Sh = 1201;
    
    bool rendered = false;
    
    std::shared_ptr<Window> window = std::make_shared<Window>(Sw, Sh);
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
//    scene->addAmbLight(.2);
    scene->addPointLight(sf::Vector3f(0, 0, 0), .8);
    
    scene->addSphere(sf::Vector3f(0,1,3), .5, sf::Color::Red, 2, 1);
    scene->addSphere(sf::Vector3f(1,0,3.3), .7, sf::Color::Yellow, 30, 0);
    scene->addPlane(sf::Vector3f(-5,-.3, 0), sf::Vector3f(-5,-.3, 7), sf::Vector3f(5,-.3, 7), sf::Vector3f(5,-.3, 0), sf::Color::Magenta);
    
    
    
    
    Renderer renderer(window, scene);
    
    // run the program as long as the window is open
    while (window->getWindowOpen())
    {
        
        
        // check all the window's events that were triggered since the last iteration of the loop
        window->pollEvents();
        
        
        // Only render the scene once, not every 1/60 of a second
        if(!rendered)
        {
            renderer.computePixelValue(0, 0);
            auto start = std::chrono::steady_clock::now();
            
            renderer.renderScene();
            rendered = true;
            
            auto end = std::chrono::steady_clock::now();
            std::cout<< "Time elasped in milliseconds = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
        }
        
        
        
        
        
        
        
    }

    return 0;
}
