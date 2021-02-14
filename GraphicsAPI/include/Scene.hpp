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




struct PointLight
{
    sf::Vector3f position;
    sf::Vector3f direction;
    float intensity;
};


struct DirLight
{
    sf::Vector3f direction;
    float intensity;
};





struct Sphere
{
    sf::Vector3f position;
    float radius;
    sf::Color color;
    
    Sphere(const sf::Vector3f& position, float radius, const sf::Color& color)
    {
        this->position = position;
        this->radius = radius;
        this->color = color;
    }
};


class Scene
{
    // Camera and lighting
    Camera cam_;
    PointLight pointLight_;
    DirLight dirLight_;
    float ambientLight_;
    
    
    // Objects in the scene
    std::vector<Sphere> spheres_;
    
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
    float intersectWithSphere(const sf::Vector3f& viewP, const Sphere& sphere, sf::Vector3f& sphereP);
    
    // Compute the light intensity given a point and a normal
    float computeLights(const sf::Vector3f& P, const sf::Vector3f& N);
    
    
    
};







#endif /* Scene_hpp */
