//
//  Scene.cpp
//  GraphicAPI
//
//  Created by Jeb Collins on 2/10/21.
//

#include <iostream>
#include <cmath>

#include "Shape.hpp"
#include "Scene.hpp"



Scene::Scene(int CW, int CN)
{
    cam_.position = sf::Vector3f(0,0,0);
    cam_.view_depth = 1.0f;
    cam_.view_width = 1.0f;
    cam_.view_height = 1.0f;
    cam_.Vz = cam_.position.z + cam_.view_depth;
    
    pointLight_.position = sf::Vector3f(0, 2.0, 2.0);
    pointLight_.intensity = 0.3;
    
    dirLight_.direction = sf::Vector3f(0,-1, -1.0);
    dirLight_.intensity = 0.3;
    
    ambientLight_ = .4;
    
    
    
    
    makeObjects();
    
    CW_ = CW;
    CN_ = CN;
}



/**        Scene::makeObjects()
 - brief: Creates the objects in the scene.  Just nice to have this in it's own function in case I want to make different scenes for testing
 
 */

void Scene::makeObjects()
{
    std::vector<sf::Vector3f> plane_verts;
    plane_verts.push_back(sf::Vector3f(-4, -.5, 0.0));
    plane_verts.push_back(sf::Vector3f(-4, -.45, 10.0));
    plane_verts.push_back(sf::Vector3f(4, -.45, 10.0));
    plane_verts.push_back(sf::Vector3f(4, -.5, 0.0));
    Plane plane(plane_verts, sf::Color::Yellow, 0);
    
    objects_.push_back(std::make_unique<Plane>(plane_verts, sf::Color::Yellow, 40));
    objects_.push_back(std::make_unique<Sphere>(sf::Vector3f(0,-.5,7), 1, sf::Color::Red, 200));

}



/**     int nearest_intersection(P of ray, D of ray, tmin, tmax, out P on object)
 - brief: Finds the nearest intersection between a given ray and all objects in the scene that lies in the interval [tmin, tmax]

 - parameters: P = Point that defines the ray
                D = Direction vector of the ray
                tmin, tmax = defines the relavant interval for the t variable
                obj_P = output the point of nearest intersection
 
 - returns: index of the nearest object in the object vector
 
 */

int Scene::nearest_intersection(const sf::Vector3f& P, const sf::Vector3f& D, float tmin, float tmax, sf::Vector3f& obj_P)
{
    float t_intersect = INFINITY;
    int obj_idx = -1;
    
    float t;
    for(int ii = 0; ii < objects_.size(); ++ii)
    {
        if(objects_[ii]->intersect(P, D, tmin, tmax, t, obj_P) && t < t_intersect)
        {
            obj_idx = ii;
            t_intersect = t;
        }
    }
    
    
    return obj_idx;
}




float Scene::computeLights(const sf::Vector3f& P, const sf::Vector3f& N, int specularity)
{
    float I = ambientLight_;
    sf::Vector3f R, V;
    
    // Point light
    sf::Vector3f ptLightD = P - pointLight_.position;
    float angle = -Dot(ptLightD, N);
    if(angle >= 0)
    {
        I += pointLight_.intensity*angle/(Norm(ptLightD));
    }
    
    if(specularity >= 0)
    {
        R = -2.f*N*Dot(N,ptLightD) + ptLightD;
        V = cam_.position - P;
        angle = Dot(R,V);
        if(angle >= 0)
        {
             I += pointLight_.intensity * std::pow(angle/(Norm(R)*Norm(V)), specularity);
        }
    }
    
    
    
    
    
    // Direcitonal Light
    angle = -Dot(dirLight_.direction, N);
    if(angle >= 0)
    {
        I += dirLight_.intensity*angle/(Norm(dirLight_.direction));
    }
    
    if(specularity >= 0)
    {
        R = -2.f*N*Dot(N,dirLight_.direction) + dirLight_.direction;
        V = cam_.position - P;
        angle = Dot(R,V);
        if(angle >= 0)
        {
            I += dirLight_.intensity * std::pow(angle/(Norm(R)*Norm(V)), specularity);
        }
    }

    
    return I;
}




sf::Color Scene::computeValue(int Cx, int Cy)
{
    float x, y;
    canvasToView(Cx, Cy, x, y);
    sf::Vector3f D = sf::Vector3f(x,y,cam_.view_depth) - cam_.position;
    
    
    sf::Vector3f obj_P{0,0,0};
    
    // Find the intersection of camera ray with the nearest object
    int obj_idx = nearest_intersection(cam_.position, D, 1, INFINITY, obj_P);
    
    
    // Compute the value at that intersection
    if(obj_idx >= 0)
    {
        sf::Vector3f N = objects_[obj_idx]->normal(obj_P);
        float I = computeLights(obj_P, N, objects_[obj_idx]->getSpecularity());
        sf::Color value = objects_[obj_idx]->getColor();
        value.r = sf::Uint8(std::min(value.r * I, 255.f));
        value.g = sf::Uint8(std::min(value.g * I, 255.f));
        value.b = sf::Uint8(std::min(value.b * I, 255.f));
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




