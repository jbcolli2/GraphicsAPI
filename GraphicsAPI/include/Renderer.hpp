//
//  Renderer.hpp
//  GraphicAPI
//
//  Created by Jeb Collins on 2/12/21.
//

#ifndef Renderer_h
#define Renderer_h


#include "Window.hpp"
#include "Scene.hpp"

#include <SFML/Graphics.hpp>


namespace rgl {



class Renderer
{
    
    std::shared_ptr<Window> window;   //  Window object for rendering.  Initialized in the ctor
    std::shared_ptr<Scene> scene;
    
    

    
    
    
    
    
public:
    // Constructor
    Renderer(std::shared_ptr<Window> window, std::shared_ptr<Scene> scene) : window(window), scene(scene) {};
    
    void renderScene();
    
    
    
    
    
    sf::Color computePixelValue(int canvasX, int cavasY);
    
    sf::Color traceRay(const sf::Vector3f& P, const sf::Vector3f& D, float tmin, float tmax,
                       int reflectionDepth = 0);
    
    
    sf::Color computeLitValue(const sf::Vector3f& objP, const sf::Vector3f& normal, int specularity, const sf::Color& rawValue);
    
    void computeReflection(){};
    
    
    void canvasToView(int , int , float& , float& );
    
//    void renderSceneThreaded();
    
//    void f(int ii);
    
    
    
    
};



} //namespace rgl





#endif /* Renderer_h */
