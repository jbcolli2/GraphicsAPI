//
//  Shape.cpp
//  GraphicsAPI
//
//  Created by Jeb Collins on 2/18/21.
//

#include <stdio.h>
#include <cmath>

#include "Shape.hpp"
#include "VectorUtil.hpp"


/**               Plane Constructor

 - brief: Contructor for the Plane shape object.  Sets the private variables for the object.  Computes the normal based on the vertices in clockwise direction
         also compute the min/max in each of the x/y/z directions.
 - parameters: `std::vector` of the position of vertices, listed in clockwise **direction** around the plane
            color of the plane
            specularity of the plane material
 */
 


Plane::Plane(const std::vector<sf::Vector3f>& verts, const sf::Color& color, int specularity)
{
    vertices_ = verts;
    this-> color_ = color;
    this->specularity_ = specularity;
    
    normal_ = Cross(vertices_[1] - vertices_[0], vertices_[3] - vertices_[0]);
    min_x_ = std::min({vertices_[0].x, vertices_[1].x, vertices_[2].x, vertices_[3].x});
    min_y_ = std::min({vertices_[0].y, vertices_[1].y, vertices_[2].y, vertices_[3].y});
    min_z_ = std::min({vertices_[0].z, vertices_[1].z, vertices_[2].z, vertices_[3].z});
    max_x_ = std::max({vertices_[0].x, vertices_[1].x, vertices_[2].x, vertices_[3].x});
    max_y_ = std::max({vertices_[0].y, vertices_[1].y, vertices_[2].y, vertices_[3].y});
    max_z_ = std::max({vertices_[0].z, vertices_[1].z, vertices_[2].z, vertices_[3].z});

}





/**         Plane::intersect
 
    -brief: Determine where plane intersect given ray.  Computes both the $t$ value on the ray and the 3D point where interseciton happens.  If $t$ is outside of [tmin, tmax] then returns false.
 
    -parameters: P = point that ray goes through
                D = Direction vector for the ray
            tmin, tmax = return false if intesection happens outside of [tmin, tmax]

    -returns: t = value of $t$ for ray where intersection occurs
            intersectP = 3D point of closes intersection of ray with plane
 */

bool Plane::intersect(const sf::Vector3f& P, const sf::Vector3f& D,
                       float tmin, float tmax,
                       float& t, sf::Vector3f& intersectP)
{
    // set the return values if intersection does not occur
    t = INFINITY;
    
    
    //intersection of ray with plane
    float denom = Dot(normal_, D);
    if(denom != 0)
    {
        t = Dot(normal_, vertices_[0] - P)/denom;
    }
    else
    {
        return false;
    }
    
    intersectP = P + t*D;
    
    if(min_x_ <= intersectP.x && intersectP.x <= max_x_ &&
       min_y_ <= intersectP.y && intersectP.y <= max_y_ &&
       min_z_ <= intersectP.z && intersectP.z <= max_z_)
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
Sphere::Sphere(const sf::Vector3f& center, float radius, const sf::Color& color, int specularity)
{
    center_ = center;
    radius_ = radius;
    color_ = color;
    specularity_ = specularity;

}





/**         intersect
 
    -brief: Determine where plane intersect given ray.  Computes both the $t$ value on the ray and the 3D point where interseciton happens.  If $t$ is outside of [tmin, tmax] then returns false.
 
    -parameters: P = point that ray goes through
                D = Direction vector for the ray
            tmin, tmax = return false if intesection happens outside of [tmin, tmax]

    -returns: t = value of $t$ for ray where intersection occurs
            intersectP = 3D point of closes intersection of ray with plane
 */
bool Sphere::intersect(const sf::Vector3f& P, const sf::Vector3f& D,
                       float tmin, float tmax,
                       float& t, sf::Vector3f& intersectP)
{
    sf::Vector3f viewP_minus_sphere = P - center_;
    
    // Quadratic coefficients
    float a = Dot(D, D);
    float b = 2*Dot(viewP_minus_sphere, D);
    float c = Dot(viewP_minus_sphere, viewP_minus_sphere) - radius_*radius_;
    
    float discriminant = b*b - 4*a*c;
    if(discriminant <= 0)
    {
        t = INFINITY;
        intersectP.x = INFINITY;
        return false;
    }
    
    float denom = 0.5*(1/a);
    float sqrt_disc = std::sqrt(discriminant);
    
    t =  std::min(denom*(-b + sqrt_disc), denom*(-b- sqrt_disc));
    intersectP = P + t*D;
    return true;
}
