//
//  Scene.cpp
//  GraphicAPI
//
//  Created by Jeb Collins on 2/10/21.
//

#include <iostream>
#include <cmath>

#include "Scene.hpp"



Scene::Scene(int CW, int CN)
{
    cam_.position = sf::Vector3f(0,0,0);
    cam_.view_depth = 1.0f;
    cam_.view_width = 1.0f;
    cam_.view_height = 1.0f;
    cam_.Vz = cam_.position.z + cam_.view_depth;
    
    spheres_.push_back(Sphere(sf::Vector3f(0,0,3), 0.25, sf::Color::Green));
    spheres_.push_back(Sphere(sf::Vector3f(-1,0,5), 1.f, sf::Color::Yellow));
    spheres_.push_back(Sphere(sf::Vector3f(1,-.5,4), 0.5, sf::Color::Red));
    
//    sphere_.position = sf::Vector3f(0, 0, 3);
//    sphere_.radius = 1.f;
//    sphere_.color = sf::Color::Green;
    
    CW_ = CW;
    CN_ = CN;
}




float Scene::intersectWithSphere(const sf::Vector3f& viewP, const Sphere& sphere)
{
    sf::Vector3f dir_vector = viewP - cam_.position;
    sf::Vector3f viewP_minus_sphere = viewP - sphere.position;
    
    // Quadratic coefficients
    float a = Dot(dir_vector, dir_vector);
    float b = 2*Dot(viewP_minus_sphere, dir_vector);
    float c = Dot(viewP_minus_sphere, viewP_minus_sphere) - sphere.radius*sphere.radius;
    
    float discriminant = b*b - 4*a*c;
    if(discriminant <= 0)
    {
        return -1;
    }
    
    float denom = 0.5*(1/a);
    float sqrt_disc = std::sqrt(discriminant);
    
    return std::min(denom*(-b + sqrt_disc), denom*(-b- sqrt_disc));
}










sf::Color Scene::computeValue(int Cx, int Cy)
{
    float x, y;
    canvasToView(Cx, Cy, x, y);
    
    // Compute interesection point $t$
    // Parameters: P = <x,y>, cam_.position, sphere data
    float t;
    float t_intersect = INFINITY;
    int sphere_idx = -1;
    for (int ii = 0; ii < spheres_.size(); ++ii)
    {
        t = intersectWithSphere(sf::Vector3f(x,y,cam_.view_depth), spheres_[ii]);
        if(t >= 0 && t < t_intersect)
        {
            t_intersect = t;
            sphere_idx = ii;
        }
            
    }
    
    
        

    if(sphere_idx >= 0)
    {
        return spheres_[sphere_idx].color;
    }
    else
    {
        return back_color_;
    }
    

}



void Scene::canvasToView(int x, int y, float &Vx, float& Vy)
{
    Vx = x * (cam_.view_width/(2*CW_));
    Vy = y * (cam_.view_height/(2*CN_));
}




