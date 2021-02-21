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
sf::Vector3<T> Cross(const sf::Vector3<T>& u, const sf::Vector3<T>& v)
{
    return sf::Vector3<T>(u.y*v.z - u.z*v.y, u.z*v.x - u.x*v.z, u.x*v.y - u.y*v.x);
}


template <typename T>
float Norm(const sf::Vector3<T>& u)
{
    return std::sqrt( Dot(u,u) );
}








#endif /* VectorUtil_h */
