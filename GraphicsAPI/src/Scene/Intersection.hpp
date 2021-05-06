//
//  Intersection.hpp
//  GraphicsAPI
//
//  Created by Jeb Collins on 5/3/21.
//

#ifndef Intersection_h
#define Intersection_h
#include <stdio.h>

#include <SFML/Graphics.hpp>

#include "Object.hpp"


class Intersection
{
    
    
private:
    std::shared_ptr<Object> object;
    float t;
    sf::Vector3f objP;
}

#endif /* Intersection_h */
