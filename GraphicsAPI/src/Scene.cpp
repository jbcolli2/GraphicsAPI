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
    
    sphere_.position = sf::Vector3f(0, 0, 3);
    sphere_.radius = 1.f;
    sphere_.color = sf::Color::Green;
    
    CW_ = CW;
    CN_ = CN;
}




float Scene::intersectWithSphere(const sf::Vector3f& viewP, const sf::Vector3f& camP, const Sphere& sphere)
{
    sf::Vector3f dir_vector = viewP - camP;
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





sf::Color Scene::computeValue(int ii, int jj)
{
    float x, y;
    canvasToView(ii, jj, x, y);
    
    // Compute interesection point $t$
    // Parameters: P = <x,y>, cam_.position, sphere data
    float t = intersectWithSphere(sf::Vector3f(x,y,cam_.view_depth), cam_.position, sphere_);
    
        

    if(t >=0)
    {
        return sphere_.color;
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




