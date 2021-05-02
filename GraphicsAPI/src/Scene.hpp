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

#include "Object.hpp"


namespace rgl{















// ///////////// Scene   ////////////////
/**
\class Scene
 \brief Class to hold all objects, both rendered objects and unrendered like cameras and lights, that are in the theoretical 3D space.  Has the ability to take a ray and find
    the first object to intersect that ray within a given bound.

 */
class Scene
{
    
public:
    Scene();
    
    // Computation methods
    bool nearestIntersection(const sf::Vector3f& P, const sf::Vector3f& D, float tmin, float tmax, sf::Vector3f& obj_P,
                                                 std::shared_ptr<Object>& object);
    bool isInShadow(const sf::Vector3f& objP, const std::shared_ptr<Light>& light);
    
    
    
    
    //Scene creation methods
    void addCamera(const sf::Vector3f& position = sf::Vector3f(0,0,0), const sf::Vector3f& direction = sf::Vector3f(0,0,1),
                   float viewWidth = 1, float viewHeight = 1, float viewDepth = 1)
    {this->cam = Camera(position, direction viewWidth, viewHeight, viewDepth);};
    
    void addObject(const Object& object);
    void addSphere(const sf::Vector3f& center, float radius, const sf::Color& color = sf::Color::White, int specularity = -1);
    void addPlane(const std::vector<sf::Vector3f>& verts, const sf::Color& color = sf::Color::White, int specularity = -1);
    void addPlane(const sf::Vector3f& v0, const sf::Vector3f& v1, const sf::Vector3f& v2,
                  const sf::Vector3f& v3, const sf::Color& color = sf::Color::White, int specularity = -1);
    
    void addLight(const std::shared_ptr<Light>& light)
    void addAmbLight(float intensity)
    void addPointLight(const sf::Vector3f& position, float intensity)
    void addDirLight(const sf::Vector3f& direction, float intensity)
    
    
    // Getters and Setters
    sf::Vector3f getCameraPos() {return cam.getPosition();};
    float getViewWidth() {return cam.getViewWidth();};
    float getViewHeight() {return cam.getViewHeight();};
    float getViewDepth() {return cam.getViewDepth(); };
    float getRayhit() {return this->rayhit_eps;};
    std::vector< std::shared_ptr<Light> > getLights() {return lights;};
    
private:
    // Camera and lighting
    Camera cam;
    std::vector< std::shared_ptr<Light> > lights;
    
    // Objects in the scene
    std::vector< std::shared_ptr<Object> > objects;

    
    static constexpr float rayhit_eps = 5e-5;
    static constexpr int maxReflectionDepth = 1;
    std::shared_ptr<Object> skybox = std::make_shared<Skybox>(sf::Color(0,0,60));
    
    
    
    
    
    
    // Create the objects in the scene
    void makeObjects();
    
    
    
    
    
    
};  // class Scene




} //namespace rgl


#endif /* Scene_hpp */
