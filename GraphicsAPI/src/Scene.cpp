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
    sphere_.color = sf::Color::Red;
    
    CW_ = CW;
    CN_ = CN;
}







sf::Color Scene::computeValue(int ii, int jj)
{
    float x, y;
    float r = .25;
    canvasToView(ii, jj, x, y);
    
    sf::Vector3f d = sf::Vector3f(x,y,cam_.Vz) - cam_.position;
    sf::Vector3f sphereToCamera = cam_.position - sphere_.position;
    
    float a = Dot(d,d);
    float b = 2*Dot(sphereToCamera, d);
    float c = Dot(sphereToCamera, sphereToCamera) - sphere_.radius*sphere_.radius;
    
    float discriminant = b*b - 4*a*c;
    if(discriminant <= 0)
        return sf::Color::Black;
    
    
    float sol1 = (1/(2*a))*(-b + std::sqrt(discriminant));
    float sol2 = (1/(2*a))*(-b - std::sqrt(discriminant));
    
    float t = std::min(sol1, sol2);
//    std::cout << "t = " << t << std::endl;
//    std::cout << "d = " << d.x << ", " << d.y << ", " << d.z << std::endl;
//    std::cout << "CO = " << sphereToCamera.x << ", " << sphereToCamera.y << ", " << sphereToCamera.z << std::endl;

    if(t > 1)
    {
        return sphere_.color;
    }
    else
    {
        return sf::Color::Black;
    }
    
//    if(x*x + y*y < r*r)
//    {
//        return sf::Color::Blue;
//    }
//    else
//    {
//        return sf::Color::Green;
//    }
}



void Scene::canvasToView(int x, int y, float &Vx, float& Vy)
{
    Vx = x * (cam_.view_width/(2*CW_));
    Vy = y * (cam_.view_height/(2*CN_));
}




