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
    
    pointLight_.position = sf::Vector3f(4.0, -10.0, 4.0);
    pointLight_.direction = sf::Vector3f(-1,-1,0);
    pointLight_.intensity = .8;
    
    dirLight_.direction = sf::Vector3f(0,0,1);
    dirLight_.intensity = .1;
    
    ambientLight_ = .1;
    
    
    
    
    spheres_.push_back(Sphere(sf::Vector3f(0,0,3), 0.25, sf::Color::Green));
    spheres_.push_back(Sphere(sf::Vector3f(-1,0,5), 1.f, sf::Color::Yellow));
    spheres_.push_back(Sphere(sf::Vector3f(1,-.5,4), 0.5, sf::Color::Red));
    
    
    CW_ = CW;
    CN_ = CN;
}




float Scene::intersectWithSphere(const sf::Vector3f& viewP, const Sphere& sphere, sf::Vector3f& sphereP)
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
    
    float t =  std::min(denom*(-b + sqrt_disc), denom*(-b- sqrt_disc));
    sphereP = viewP + t*dir_vector;
    
    return t;
}





float Scene::computeLights(const sf::Vector3f& P, const sf::Vector3f& N)
{
    float I = ambientLight_;
    
    // Point light
    sf::Vector3f ptLightD = P - pointLight_.position;
    float angle = Dot(ptLightD, N);
    if(angle >= 0)
    {
        I += pointLight_.intensity*angle/(Norm(N)*Norm(ptLightD));
    }
    
    
    // Direcitonal Light
    angle = Dot(dirLight_.direction, N);
    if(angle >= 0)
    {
        I += dirLight_.intensity*angle/(Norm(N)*Norm(dirLight_.direction));
    }
    
    return I;
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
    sf::Vector3f sphere_intersect, sphereP;
    for (int ii = 0; ii < spheres_.size(); ++ii)
    {
        t = intersectWithSphere(sf::Vector3f(x,y,cam_.view_depth), spheres_[ii], sphereP);
        if(t >= 0 && t < t_intersect)
        {
            t_intersect = t;
            sphere_idx = ii;
            sphere_intersect = sphereP;
        }
            
    }
    
    
        

    if(sphere_idx >= 0)
    {
        sf::Vector3f N = spheres_[sphere_idx].position - sphere_intersect;
        N = N/Norm(N);
        float I = computeLights(sphere_intersect, N);
        sf::Color value = spheres_[sphere_idx].color;
        value.r = sf::Uint8(value.r * I);
        value.g = sf::Uint8(value.g * I);
        value.b = sf::Uint8(value.b * I);
        return value;
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




