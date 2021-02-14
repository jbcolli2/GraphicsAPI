//
//  VectorUtil.hpp
//  GraphicAPI
//
//  Created by Jeb Collins on 2/11/21.
//

#ifndef VectorUtil_h
#define VectorUtil_h

#include <cmath>

#include <SFML/Graphics.hpp>

template <typename T>
float Dot(const sf::Vector2<T>& u, const sf::Vector2<T>& v)
{
    return u.x*v.x + u.y*v.y;
}

template <typename T>
float Dot(const sf::Vector3<T>& u, const sf::Vector3<T>& v)
{
    return u.x*v.x + u.y*v.y + u.z*v.z;
}


template <typename T>
float Norm(const sf::Vector3<T>& u)
{
    return std::sqrt( Dot(u,u) );
}








#endif /* VectorUtil_h */
