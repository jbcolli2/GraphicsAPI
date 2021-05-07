//
//  Object.hpp
//  GraphicsAPI
//
//  Created by Jeb Collins on 2/18/21.
//

#ifndef Object_h
#define Object_h

#include <SFML/Graphics.hpp>
#include "Ray.hpp"
#include "VectorUtil.hpp"


namespace rgl {

// ///////////// Camera class   ////////////////
/**
 \class Camera
 \brief Stores the position and direction of the camera.  Also stores the viewport information, width, height and depth.
 

 */
class Camera
{
public:
    Camera() = default;
    Camera(const sf::Vector3f& position, const sf::Vector3f& direction, float viewWidth, float viewHeight, float viewDepth) :
        position(position), direction(direction), viewWidth(viewWidth), viewHeight(viewHeight), viewDepth(viewDepth) {};
    
    
    
    // Getters and Setters
    sf::Vector3f getPosition() {return position;};
    sf::Vector3f getDirection() {return direction;};
    float getViewWidth() {return viewWidth;};
    float getViewHeight() {return viewHeight;};
    float getViewDepth() {return viewDepth;};
    
private:
    sf::Vector3f position;
    sf::Vector3f direction;
    
    float viewWidth, viewHeight, viewDepth;
};



















// ///////////// Light   ////////////////
/**
 \class Light
 \brief Abstract class for lights in the scene.
 
 
 Contains virtual pure method to compute the intensity of the light at a particular point given a normal.
 
 */
class Light
{
public:
    virtual float computeIllumination(const sf::Vector3f& objPos, const sf::Vector3f& normal, const sf::Vector3f& viewPos, int specularity);
    
    virtual sf::Vector3f directionToPoint(const sf::Vector3f& point) = 0;
    
protected:
    float intensity;
    
    
};


class PointLight : public Light
{
public:
    PointLight(const sf::Vector3f& position, float intensity){this->position = position; this->intensity = intensity;};
    
    
    virtual sf::Vector3f directionToPoint(const sf::Vector3f& point) override { return point - position;};
    
private:
    sf::Vector3f position;
};


class DirLight : public Light
{
public:
    DirLight(const sf::Vector3f& direction, float intensity){this->direction = direction; this->intensity = intensity;};
    
    
    virtual sf::Vector3f directionToPoint(const sf::Vector3f& point) override { return direction;};

    
private:
    sf::Vector3f direction;
};



class AmbientLight : public Light
{
public:
    AmbientLight(float intensity){this->intensity = intensity;};
    
    virtual float computeIllumination(const sf::Vector3f& objPos, const sf::Vector3f& normal, const sf::Vector3f& viewPos, int specularity) override
    {return intensity;};
    
    virtual sf::Vector3f directionToPoint(const sf::Vector3f& point) override { return sf::Vector3f(0,0,0);};

    
};






















// ///////////// Object class   ////////////////
/**
 \class Object [abstract]
 \brief an abstract class to describe all rendered objects in a scene
 
 */
class Object
{
public:
    virtual bool intersect(const Ray& ray,
                           float& t, sf::Vector3f& intersectP) = 0;
    virtual sf::Vector3f normal(const sf::Vector3f& P) = 0;
    sf::Color getColor() { return color;};
    int getSpecularity() { return specularity;};
    float getReflectivity() {return reflectivity;};

    
protected:
    sf::Color color;
    int specularity;
    float reflectivity;
    
    
};




class Skybox : public Object
{
public:
    Skybox(const sf::Color& back_color) {color = back_color;};
    
    virtual bool intersect(const Ray& ray,
                           float& t, sf::Vector3f& intersectP) override {return true;};
    
    virtual sf::Vector3f normal(const sf::Vector3f& P) override {return sf::Vector3f(0,0,0);};

};




class Plane : public Object
{
    sf::Vector3f normalVec;
    sf::Vector3f normal01, normal12, normal23, normal30;  // normals for testing intersection
    std::vector<sf::Vector3f> vertices;
    float min_x, max_x;
    float min_y, max_y;
    float min_z, max_z;
    
public:
    Plane(const sf::Color& color = sf::Color::White,
          int specularity = -1, float reflectivity = 0);
    Plane(const std::vector<sf::Vector3f>& verts, const sf::Color& color = sf::Color::White,
          int specularity = -1, float reflectivity = 0);
    Plane(const sf::Vector3f& v0, const sf::Vector3f& v1,const sf::Vector3f& v2,const sf::Vector3f& v3,
          const sf::Color& color = sf::Color::White, int specularity = -1, float reflectivity = 0) :
    Plane(std::vector<sf::Vector3f>{v0, v1, v2, v3}, color, specularity, reflectivity) {};
    
    virtual bool intersect(const Ray& ray,
                           float& t, sf::Vector3f& intersectP) override;
    sf::Vector3f virtual normal(const sf::Vector3f& P) override {return normalVec;};
    

};



class Sphere : public Object
{
    sf::Vector3f center;
    float radius;
    
public:
    Sphere(const sf::Vector3f& center, float radius, const sf::Color& color = sf::Color::White,
           int specularity = -1, float reflectivity = 0);
    virtual bool intersect(const Ray& ray,
                           float& t, sf::Vector3f& intersectP) override;
    sf::Vector3f normal(const sf::Vector3f& P) override {return P - center;};
};



} // namespace rgl

#endif /* Object_h */
