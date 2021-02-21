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
    
    
    
    
    std::vector<sf::Vector3f> plane_verts;
    plane_verts.push_back(sf::Vector3f(-4, -.5, 0.0));
    plane_verts.push_back(sf::Vector3f(4, -.5, 0.0));
    plane_verts.push_back(sf::Vector3f(4, 0, 10.0));
    plane_verts.push_back(sf::Vector3f(-4, 0, 10.0));
    
    plane = Plane(plane_verts, sf::Color::Yellow, 40);
//    plane.vert_minus_cam = plane.vertices[0] - cam_.position;
    
    
//    spheres_.push_back(Sphere(sf::Vector3f(0,0,3), 0.5, sf::Color(255, 0, 100), 200));
//    spheres_.push_back(Sphere(sf::Vector3f(-2,0,6), 1.0, sf::Color::Red, 3));
//    spheres_.push_back(Sphere(sf::Vector3f(1,1.2,4), .7, sf::Color::Blue, -1));
    
    
    CW_ = CW;
    CN_ = CN;
}



float Scene::intersectWithPlane(const sf::Vector3f& D, const Plane& plane, sf::Vector3f& P)
{
    float t = Dot(plane.normal, plane.vert_minus_cam)/Dot(plane.normal, D);
    
    P = cam_.position + t*D;
    
    if(plane.min_x <= P.x && P.x <= plane.max_x &&
       plane.min_y <= P.y && P.y <= plane.max_y &&
       plane.min_z <= P.z && P.z <= plane.max_z)
    {
        return t;
    }
    else
    {
        return -1;
    }
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
    bool draw_plane = false;
    
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
    t = intersectWithPlane(sf::Vector3f(x,y,cam_.view_depth) - cam_.position, plane, sphereP);
    if(t > 0 && t < t_intersect)
    {
        draw_plane = true;
        t_intersect = t;
        sphere_intersect = sphereP;
    }
    
    if(draw_plane)
    {
        sf::Vector3f N = plane.normal;
        N = -N/Norm(N);
        float I = computeLights(sphere_intersect, N, plane.specularity);
        sf::Color value = plane.color;
        value.r = sf::Uint8(std::min(value.r * I, 255.f));
        value.g = sf::Uint8(std::min(value.g * I, 255.f));
        value.b = sf::Uint8(std::min(value.b * I, 255.f));
        return value;
    }
        

    if(sphere_idx >= 0)
    {
        sf::Vector3f N = sphere_intersect - spheres_[sphere_idx].position;
        N = N/Norm(N);
        float I = computeLights(sphere_intersect, N, spheres_[sphere_idx].specularity);
        sf::Color value = spheres_[sphere_idx].color;
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




