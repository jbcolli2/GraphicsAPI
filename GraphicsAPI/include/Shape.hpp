//
//  Shape.hpp
//  GraphicsAPI
//
//  Created by Jeb Collins on 2/18/21.
//

#ifndef Shape_h
#define Shape_h

#include <SFML/Graphics.hpp>



class Shape
{
    
protected:
    sf::Color color_;
    int specularity_;
    float reflectivity_;
    
    
public:
    virtual bool intersect(const sf::Vector3f& P, const sf::Vector3f& D,
                           float tmin, float tmax,
                           float& t, sf::Vector3f& intersectP) = 0;
    virtual sf::Vector3f normal(const sf::Vector3f& P) = 0;
    sf::Color getColor() { return color_;};
    int getSpecularity() { return specularity_;};
    float getReflectivity() {return reflectivity_;};
};





class Plane : public Shape
{
    sf::Vector3f normal_;
    std::vector<sf::Vector3f> vertices_;
    float min_x_, max_x_;
    float min_y_, max_y_;
    float min_z_, max_z_;
    
public:
    Plane(const std::vector<sf::Vector3f>& verts, const sf::Color& color = sf::Color::White,
          int specularity = -1, float reflectivity = 0);
    bool virtual intersect(const sf::Vector3f& P, const sf::Vector3f& D,
                           float tmin, float tmax,
                           float& t, sf::Vector3f& intersectP) override;
    sf::Vector3f virtual normal(const sf::Vector3f& P) override {return normal_;};
    

};



class Sphere : public Shape
{
    sf::Vector3f center_;
    float radius_;
    
public:
    Sphere(const sf::Vector3f& center, float radius, const sf::Color& color = sf::Color::White,
           int specularity = -1, float reflectivity = 0);
    bool intersect(const sf::Vector3f& P, const sf::Vector3f& D,
                           float tmin, float tmax,
                           float& t, sf::Vector3f& intersectP) override;
    sf::Vector3f normal(const sf::Vector3f& P) override {return P - center_;};
};





#endif /* Shape_h */
