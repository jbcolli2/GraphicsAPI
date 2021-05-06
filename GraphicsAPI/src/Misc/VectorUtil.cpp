//
//  VectorUtil.cpp
//  GraphicAPI
//
//  Created by Jeb Collins on 2/11/21.
//

#include <stdio.h>
#include <cmath>

#include <SFML/Graphics.hpp>




//namespace rgl{
//
//
//template <typename T>
//float Dot(const sf::Vector2<T>& u, const sf::Vector2<T>& v)
//{
//    return u.x*v.x + u.y*v.y;
//}
//
//template <typename T>
//float Dot(const sf::Vector3<T>& u, const sf::Vector3<T>& v)
//{
//    return u.x*v.x + u.y*v.y + u.z*v.z;
//}
//
//template <typename T>
//sf::Vector3<T> Cross(const sf::Vector3<T>& u, const sf::Vector3<T>& v)
//{
//    return sf::Vector3<T>(u.y*v.z - u.z*v.y, u.z*v.x - u.x*v.z, u.x*v.y - u.y*v.x);
//}
//
//
//template <typename T>
//float Norm(const sf::Vector3<T>& u)
//{
//    return std::sqrt( Dot(u,u) );
//}
//
//
//
//// Compute reflection vector
//sf::Vector3f reflection(const sf::Vector3f& L, const sf::Vector3f& N) {return 2.f*N*Dot(N,L) - L;};
//
//
//
//
//} // namespace rgl
