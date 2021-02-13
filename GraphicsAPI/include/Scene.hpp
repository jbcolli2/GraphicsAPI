//
//  Scene.hpp
//  GraphicAPI
//
//  Created by Jeb Collins on 2/10/21.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>

#include <SFML/Graphics.hpp>

#include "VectorUtil.hpp"

struct Camera
{
    sf::Vector3f position;
    sf::Vector3f direction;
    
    float view_width, view_height, view_depth;
    float Vz;
};


struct Sphere
{
    sf::Vector3f position;
    float radius;
    sf::Color color;
};


class Scene
{
    Camera cam_;
    Sphere sphere_;
    
    int CW_, CN_;  // The western and northern edge in pixels of the canvas
    sf::Color back_color_ = sf::Color::Black;
    
public:
    Scene() {};
    Scene(int Cw, int Ch);
    
    sf::Color computeValue(int ii, int jj);
    
private:
    // Convert from canvas pixel coordinates to float viewport coordinates
    void canvasToView(int Cx, int Cy, float& Vx, float& Vy);
    
    // Compute intersection of ray with sphere
    float intersectWithSphere(const sf::Vector3f& viewP, const sf::Vector3f& camP, const Sphere& sphere);
    
    
    
};







#endif /* Scene_hpp */
