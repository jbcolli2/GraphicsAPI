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
 
    
    
    
    
private:
    bool traceRay(const sf::Vector3f& P, const sf::Vector3f& D, float tmin, float tmax, sf::Color& obj_value,
                       int reflectionDepth = 0);
    
    
    sf::Color computeLitValue(const sf::Vector3f& objP, const sf::Vector3f& normal, const sf::Vector3f& viewPos, int specularity, const sf::Color& rawValue);
    
    sf::Color computeReflection(const sf::Vector3f& objP, const sf::Vector3f& reflectD, int reflectionDepth, float reflectivity, const sf::Color& localValue);
    
    
    void canvasToView(int , int , float& , float& );
    
//    void renderSceneThreaded();
    
//    void f(int ii);
    
    
    int max_reflections = 0;
    
    
};



} //namespace rgl





#endif /* Renderer_h */
