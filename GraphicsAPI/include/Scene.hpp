//
//  Scene.hpp
//  GraphicAPI
//
//  Created by Jeb Collins on 2/10/21.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>

#include <SFML/Graphics.hpp>

#include "Shape.hpp"
#include "VectorUtil.hpp"

struct Camera
{
    sf::Vector3f position;
    sf::Vector3f direction;
    
    float view_width, view_height, view_depth;
    float Vz;
};




struct PointLight
{
    sf::Vector3f position;
    sf::Vector3f direction;
    float intensity;
};


struct DirLight
{
    sf::Vector3f direction;
    float intensity;
};





//struct Sphere
//{
//    sf::Vector3f position;
//    float radius;
//    sf::Color color;
//    int specularity;
//    
//    Sphere(const sf::Vector3f& position, float radius, const sf::Color& color, int specularity)
//    {
//        this->position = position;
//        this->radius = radius;
//        this->color = color;
//        this->specularity = specularity;
//    }
//};
//
//
//
//
//struct Plane
//{
//    sf::Vector3f normal;
//    std::vector<sf::Vector3f> vertices;
//    sf::Color color;
//    float min_x, max_x;
//    float min_y, max_y;
//    float min_z, max_z;
//    int specularity;
//    
//    sf::Vector3f vert_minus_cam;
//    
//    Plane() {};
//    Plane(const std::vector<sf::Vector3f>& verts, sf::Color color, int specularity)
//    {
//        vertices = verts;
//        this-> color = color;
//        this->specularity = specularity;
//        normal = Cross(vertices[1] - vertices[0], vertices[3] - vertices[0]);
//        min_x = std::min({vertices[0].x, vertices[1].x, vertices[2].x, vertices[3].x});
//        min_y = std::min({vertices[0].y, vertices[1].y, vertices[2].y, vertices[3].y});
//        min_z = std::min({vertices[0].z, vertices[1].z, vertices[2].z, vertices[3].z});
//        max_x = std::max({vertices[0].x, vertices[1].x, vertices[2].x, vertices[3].x});
//        max_y = std::max({vertices[0].y, vertices[1].y, vertices[2].y, vertices[3].y});
//        max_z = std::max({vertices[0].z, vertices[1].z, vertices[2].z, vertices[3].z});
//   }
//};


class Scene
{
    // Camera and lighting
    Camera cam_;
    PointLight pointLight_;
    DirLight dirLight_;
    float ambientLight_;
    
    float shadow_eps_ = 1e-7;
    int maxReflectionDepth_ = 1;
    
    
    // Objects in the scene
    std::vector< std::unique_ptr<Shape> > objects_;
    
    int CW_, CN_;  // The western and northern edge in pixels of the canvas
    sf::Color back_color_ = sf::Color(0, 0, 40);
    
public:
    Scene(int Cw, int Ch);
    
    sf::Color computePixelValue(int ii, int jj);
    
private:
    // Trace a ray and return color value at nearest intersection
    sf::Color traceRay(const sf::Vector3f& P, const sf::Vector3f& D, float tmin, float tmax,
                       int reflectionDepth = 0);
    
    // Create the objects in the scene
    void makeObjects();
    
    // Convert from canvas pixel coordinates to float viewport coordinates
    void canvasToView(int Cx, int Cy, float& Vx, float& Vy);
    
    // Find nearest intersection btwn ray and all objects in scene
    int nearest_intersection(const sf::Vector3f& P, const sf::Vector3f& D, float tmin, float tmax, sf::Vector3f& obj_P);
    
    
    // Compute the light intensity given a point and a normal
    float computeLights(const sf::Vector3f& P, const sf::Vector3f& N, int specularity);
    
    // Compute reflection vector
    sf::Vector3f reflection(const sf::Vector3f& L, const sf::Vector3f& N) {return 2.f*N*Dot(N,L) - L;};
    
    
    
};







#endif /* Scene_hpp */
