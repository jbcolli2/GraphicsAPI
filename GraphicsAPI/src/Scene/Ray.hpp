//
//  Ray.hpp
//  GraphicsAPI
//
//  Created by Jeb Collins on 5/3/21.
//

#ifndef Ray_h
#define Ray_h
#include <stdio.h>
#include <limits>
#include <cmath>

#include <SFML/Graphics.hpp>

class Ray
{
    
public:
    Ray(const sf::Vector3f& point, const sf::Vector3f& dir, float tmin = 0, float tmax = INFINITY)
    {
        this->point = point;
        this->dir = dir;
        this->tmin = tmin;
        this->tmax = tmax;
    };
    
    bool isInBounds(float t) const {return t >= tmin && t <= tmax;};
    sf::Vector3f evaluateAt(float t) const {return sf::Vector3f(point.x + t*dir.x, point.y + t*dir.y, point.z + t*dir.z);};
    void setBounds(float tmin, float tmax){this->tmin = tmin; this->tmax = tmax;};

    sf::Vector3f point;
    sf::Vector3f dir;
    
private:
    float tmin, tmax;
};
#endif /* Ray_h */
