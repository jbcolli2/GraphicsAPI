//
//  Object.cpp
//  GraphicsAPI
//
//  Created by Jeb Collins on 2/18/21.
//

#include <stdio.h>
#include <iostream>
#include <cmath>

#include "Object.hpp"


namespace rgl {

// ///////////// Light::computeIllumination()   ////////////////
/**
 \brief Computes the illumination(intensity at a point) of a point light given a point and normal.  This is the general computation for a light with a direction vector between light and point.
 
 \param objPos The position of the object the light is hitting
 \param normal Normal of the object at `objPos`
 \param viewPos The position of the viewer of the object (camera or another object if computing reflection)   Used for specular lighting
 \param specularity Specularity of the object at that point
 
 \returns The illumination to be used to modify the base color of the object at the point
 */

float Light::computeIllumination(const sf::Vector3f& objP, const sf::Vector3f& normal, const sf::Vector3f& viewPos, int specularity)
{
    sf::Vector3f pointToLight = -directionToPoint(objP);
    float illumination = 0;
    
    float angle = Dot(pointToLight, normal);
    if(angle >= 0)
    {
        illumination += intensity*angle/(Norm(pointToLight)*Norm(normal));
        
        if(specularity >= 0)
        {
            sf::Vector3f R = reflection(-pointToLight, normal/Norm(normal));

            sf::Vector3f V = viewPos - objP;
            angle = Dot(R,V);
            if(angle >= 0)
            {
                illumination += intensity * std::pow(angle/(Norm(R)*Norm(V)), specularity);
            }
        }
    }

    return illumination;
}


















Plane::Plane(const sf::Color& color, int specularity, float reflectivity)
{
    this->vertices.push_back(sf::Vector3f(0,0,2));
    this->vertices.push_back(sf::Vector3f(1,0,2));
    this->vertices.push_back(sf::Vector3f(1,1,2));
    this->vertices.push_back(sf::Vector3f(0,1,2));
}




/**               Plane Constructor

 - brief: Contructor for the Plane Object object.  Sets the private variables for the object.  Computes the normal based on the vertices in clockwise direction when looking at outside of plane
         also compute the min/max in each of the x/y/z directions.
 - parameters: `std::vector` of the position of vertices, listed in clockwise **direction** around the plane
            color of the plane
            specularity of the plane material
 */
 


Plane::Plane(const std::vector<sf::Vector3f>& verts, const sf::Color& color,
             int specularity, float reflectivity)
{
    this->vertices = verts;
    this-> color = color;
    this->specularity = specularity;
    this->reflectivity = reflectivity;
    
    normalVec = Cross(vertices[1] - vertices[0], vertices[3] - vertices[0]);
    normalVec = normalVec/Norm(normalVec);
    
    normal01 = Cross(normalVec, vertices[1] - vertices[0]);
    normal12 = Cross(normalVec, vertices[2] - vertices[1]);
    normal23 = Cross(normalVec, vertices[3] - vertices[2]);
    normal30 = Cross(normalVec, vertices[0] - vertices[3]);
    
    min_x = std::min({vertices[0].x, vertices[1].x, vertices[2].x, vertices[3].x});
    min_y = std::min({vertices[0].y, vertices[1].y, vertices[2].y, vertices[3].y});
    min_z = std::min({vertices[0].z, vertices[1].z, vertices[2].z, vertices[3].z});
    max_x = std::max({vertices[0].x, vertices[1].x, vertices[2].x, vertices[3].x});
    max_y = std::max({vertices[0].y, vertices[1].y, vertices[2].y, vertices[3].y});
    max_z = std::max({vertices[0].z, vertices[1].z, vertices[2].z, vertices[3].z});

}





/**         Plane::intersect
 
    -brief: Determine where plane intersect given ray.  Computes both the $t$ value on the ray and the 3D point where interseciton happens.  If $t$ is outside of [tmin, tmax] then returns false.
 
    -parameters: P = point that ray goes through
                D = Direction vector for the ray
            tmin, tmax = return false if intesection happens outside of [tmin, tmax]

    -returns: t = value of $t$ for ray where intersection occurs
            intersectP = 3D point of closes intersection of ray with plane
 */

bool Plane::intersect(const Ray& ray,
                            float& t, sf::Vector3f& intersectP)
{
    // set the return values if intersection does not occur
    t = INFINITY;
    
    
    //intersection of ray with plane
    float denom = Dot(normalVec, ray.dir);
    if(denom != 0)
    {
        t = Dot(normalVec, vertices[0] - ray.point)/denom;
    }
    else
    {
        return false;
    }
    
    if(not ray.isInBounds(t))
    {
        t = INFINITY;
        return false;
    }
    
    intersectP = ray.evaluateAt(t);
    
    float boundTest01 = Dot(intersectP - vertices[0], normal01);
    float boundTest12 = Dot(intersectP - vertices[1], normal12);
    float boundTest23 = Dot(intersectP - vertices[2], normal23);
    float boundTest30 = Dot(intersectP - vertices[0], normal30);
    
    if(boundTest01 > 0 && boundTest12 > 0 && boundTest23 > 0 && boundTest30 > 0)
    {
        return true;
    }
    else
    {
        t = INFINITY;
        intersectP.x = INFINITY;
        return false;
    }

}














/**         Sphere Constructor
 
 -brief: Contructs a sphere object
 
 -parameters: center and radius of the object.  Also color and specularity
 */
Sphere::Sphere(const sf::Vector3f& center, float radius, const sf::Color& color,
               int specularity, float reflectivity)
{
    this->center = center;
    this->radius = radius;
    this->color = color;
    this->specularity = specularity;
    this->reflectivity = reflectivity;

}





/**         intersect
 
    -brief: Determine where plane intersect given ray.  Computes both the $t$ value on the ray and the 3D point where interseciton happens.  If $t$ is outside of [tmin, tmax] then returns false.
 
    -parameters: P = point that ray goes through
                D = Direction vector for the ray
            tmin, tmax = return false if intesection happens outside of [tmin, tmax]

    -returns: t = value of $t$ for ray where intersection occurs
            intersectP = 3D point of closes intersection of ray with plane
 */
bool Sphere::intersect(const Ray& ray,
                       float& t, sf::Vector3f& intersectP)
{
    sf::Vector3f viewP_minus_sphere = ray.point - center;
    
    // Quadratic coefficients
    float a = Dot(ray.dir, ray.dir);
    float b = 2*Dot(viewP_minus_sphere, ray.dir);
    float c = Dot(viewP_minus_sphere, viewP_minus_sphere) - radius*radius;
    
    float discriminant = b*b - 4*a*c;
    if(discriminant <= 0)
    {
        t = INFINITY;
        return false;
    }
    
    float denom = 0.5*(1/a);
    float sqrt_disc = std::sqrt(discriminant);
    
    float t1 = denom*(-b + sqrt_disc);
    float t2 = denom*(-b - sqrt_disc);
    t1 = ray.isInBounds(t1) ? t1 : INFINITY;
    t2 = ray.isInBounds(t2) ? t2 : INFINITY;
    t =  std::min(t1, t2);
    if(ray.isInBounds(t) && t != INFINITY)
    {
        intersectP = ray.evaluateAt(t);
        return true;
    }
    else
    {
        t = INFINITY;
        return false;
    }
    
}







} // namespace rgl
