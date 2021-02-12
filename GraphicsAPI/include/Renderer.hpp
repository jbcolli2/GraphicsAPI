//
//  Renderer.hpp
//  GraphicAPI
//
//  Created by Jeb Collins on 2/12/21.
//

#ifndef Renderer_h
#define Renderer_h


#include "Canvas.hpp"
#include "Scene.hpp"

#include <SFML/Graphics.hpp>




class Renderer
{
    int Sw_, Sh_;    // The width and height of the screen in pixels.
    int CE_, CW_, CS_, CN_;  // The boundaries of the canvas, in pixels.
    
    sf::RenderWindow window_;   // SFML Window object for rendering.  Initialized in the ctor
    sf::Event event_;     // Event for closing the window
    sf::Sprite sprite_;  // Sprite holding the rendered image.
    
    Canvas canvas_;
    Scene scene_;
    
    
    
    
    
public:
    // Constructor
    Renderer();
    
    void pollEvents();
    
    void renderScene();
    
    
    
    
    // Getters and Setters
    sf::RenderWindow getWindowOpen();
    
    
};





#endif /* Renderer_h */
