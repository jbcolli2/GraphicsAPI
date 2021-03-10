//
//  Screen.hpp
//  GraphicAPI
//
//  Created by Jeb Collins on 2/9/21.
//

#ifndef Screen_h
#define Screen_h

#include <SFML/Graphics.hpp>

namespace rgl {
    
class Window
{
    // The SFML object needed to draw to the window
    sf::RenderWindow window;   // SFML Window object for rendering.  Initialized in the ctor
    sf::Event event;     // Event for closing the window
    sf::Image screenImage;
    sf::Texture screenTexture;
    sf::Sprite screenSprite;
    
    int Sw, Sh;  // number of pixels on the screen in each direction
    int CE, CW, CS, CN;  // The boundaries of the canvas, in pixels.
    
public:
    Window() {};
    Window(int Sw, int Sh);
    
    void pollEvents();
    
    void setPixel(int x, int y, sf::Color color);
    
    void display();
    
    
    bool getWindowOpen() { return this->window.isOpen();}
    
    
    
    
    
    ///////////////////////  Getters  //////////////////////////////
    int getCanvasW() {return CW;};
    int getCanvasE() {return CE;};
    int getCanvasS() {return CS;};
    int getCanvasN() {return CN;};
    
    
};

}



#endif /* Screen_h */
