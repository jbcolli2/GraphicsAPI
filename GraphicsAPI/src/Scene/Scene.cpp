//
//  Scene.cpp
//  GraphicAPI
//
//  Created by Jeb Collins on 2/10/21.
//

#include <iostream>
#include <cmath>

#include "Object.hpp"
#include "Scene.hpp"


namespace rgl
{


Scene::Scene()
{
    cam = Camera(sf::Vector3f(0,0,0), sf::Vector3f(0,0,1), 1, 1, 1);
    
    std::shared_ptr<Object> skybox = std::make_shared<Skybox>(sf::Color(0,0,60));
}







void Scene::addObject(const std::shared_ptr<Object>& object)
{
    this->objects.push_back(object);
}

void Scene::addSphere(const sf::Vector3f& center, float radius, const sf::Color& color,
                      int specularity, float reflection)
{
    this->objects.push_back(std::make_shared<Sphere>(center, radius, color, specularity, reflection));
}



void Scene::addPlane(const std::vector<sf::Vector3f>& verts, const sf::Color& color,
                     int specularity, float reflection)
{
    this->objects.push_back(std::make_shared<Plane>(verts, color, specularity, reflection));
}

void Scene::addPlane(const sf::Vector3f& v0, const sf::Vector3f& v1, const sf::Vector3f& v2,
                     const sf::Vector3f& v3, const sf::Color& color, int specularity, float reflection)
{
    std::vector<sf::Vector3f> verts;
    verts.push_back(v0);
    verts.push_back(v1);
    verts.push_back(v2);
    verts.push_back(v3);
    
    this->objects.push_back(std::make_shared<Plane>(verts, color, specularity, reflection));
}


void Scene::addLight(const std::shared_ptr<Light>& light)
{
    this->lights.push_back(light);
}



void Scene::addAmbLight(float intensity)
{
    this->lights.push_back(std::make_shared<AmbientLight>(intensity));
}


void Scene::addPointLight(const sf::Vector3f& position, float intensity)
{
    this->lights.push_back(std::make_shared<PointLight>(position, intensity));
}


void Scene::addDirLight(const sf::Vector3f& direction, float intensity)
{
    this->lights.push_back(std::make_shared<DirLight>(direction, intensity));
}





/**        Scene::makeObjects()
 - brief: Creates the objects in the scene.  Just nice to have this in it's own function in case I want to make different scenes for testing
 
 */

void Scene::makeObjects()
{
    std::vector<sf::Vector3f> plane_verts;
    // Vertices for the floor
    plane_verts.push_back(sf::Vector3f(-4, -.4, 0.75));
    plane_verts.push_back(sf::Vector3f(-4, -.3, 10.0));
    plane_verts.push_back(sf::Vector3f(4, -.3, 10.0));
    plane_verts.push_back(sf::Vector3f(4, -.4, 0.75));
    
    objects.push_back(std::make_shared<Plane>(plane_verts, sf::Color::Yellow, -1));
    
    objects.push_back(std::make_shared<Sphere>(sf::Vector3f(-.4,0,1.3), .3, sf::Color::Green, -1));
    objects.push_back(std::make_shared<Sphere>(sf::Vector3f(.5,-.2,2.5), .5, sf::Color::White, 100, 0.2));
//    objects.push_back(std::make_shared<Sphere>(sf::Vector3f(0,.8,2.5), .4, sf::Color::Red, 1));

//    objects.push_back(std::make_shared<Sphere>(sf::Vector3f(1.3,.5,3.2), .4, sf::Color(50, 120,0), 2));

    
    // A wall facing the camera on the left
    plane_verts[0] = sf::Vector3f(-4, 2, 5);
    plane_verts[1] = sf::Vector3f(-1, 2, 5);
    plane_verts[2] = sf::Vector3f(-1,0, 7);
    plane_verts[3] = sf::Vector3f(-4, 0, 7);
//    objects.push_back(std::make_shared<Plane>(plane_verts, sf::Color::Red, -1));

    // A wall facing the camera on the right
    plane_verts[0] = sf::Vector3f(1, 2, 5);
    plane_verts[1] = sf::Vector3f(4, 2, 5);
    plane_verts[2] = sf::Vector3f(4, -2, 5);
    plane_verts[3] = sf::Vector3f(1, -2, 5);
//    objects.push_back(std::make_shared<Plane>(plane_verts, sf::Color::Red, -1));

}











// ///////////// nearestIntersection   ////////////////
/**
 \brief Given a ray (P,D) finds the first object in the scene to intersect that ray as long as t \in [tmin, tmax].  Saves the position of the intersections and
 returns the object index.
 
 \param P Point that defines the ray
 \param D Direction vector for the ray
 \param tmin,tmax Defines the acceptable interval for the t parameter of the ray
 \param obj_P[out] Position of the interseciton of the ray with the object
 
 \returns Index of the object vector corresponding to the object that the ray hit.
 */
bool Scene::nearestIntersection(const Ray& ray, sf::Vector3f& obj_P, std::shared_ptr<Object>& object)
{
    float t_intersect = INFINITY;
    int obj_idx = -1;
    
    float t;
    sf::Vector3f temp_obj_P;
    for(int ii = 0; ii < objects.size(); ++ii)
    {
        if(objects[ii]->intersect(ray, t, temp_obj_P))
        {
            if(t < t_intersect)
            {
                obj_idx = ii;
                obj_P = temp_obj_P;
                t_intersect = t;
            }
            
        }
    }
    
    
    if(obj_idx == -1)
    {
        object = this->skybox;
        return false;
    }
    else
    {
        object = this->objects[obj_idx];
        return true;
    }
    
}









// ///////////// isInShadow   ////////////////
/**
 \brief Checks to actually see if a point is in shadow from a given light
 
 \param objP The point to determine whether it is in shadow
 \param light The light possibly creating the shadow
 
 \returns True if point is in shadow from light
 */
bool Scene::isInShadow(const sf::Vector3f &objP, const std::shared_ptr<Light>& light)
{
    sf::Vector3f tempP;
    std::shared_ptr<Object> tempObj;
    
    Ray ray{objP, -light->directionToPoint(objP), rayhit_eps, INFINITY};
    return nearestIntersection(ray, tempP, tempObj);
    
}

























} // namespace rgl

