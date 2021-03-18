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
    
    bool nearestIntersection(const sf::Vector3f& P, const sf::Vector3f& D, float tmin, float tmax, sf::Vector3f& obj_P,
                                                 std::shared_ptr<Object>& object);
 
    bool isInShadow(const sf::Vector3f& objP, const std::shared_ptr<Light>& light);
    
    
    sf::Vector3f getCameraPos() {return cam.getPosition();};
    float getViewWidth() {return cam.getViewWidth();};
    float getViewHeight() {return cam.getViewHeight();};
    float getViewDepth() {return cam.getViewDepth(); };
    std::vector< std::shared_ptr<Light> > getLights() {return lights;};
    
private:
    // Camera and lighting
    Camera cam;
    std::vector< std::shared_ptr<Light> > lights;
    
    // Objects in the scene
    std::vector< std::shared_ptr<Object> > objects;

    
    static constexpr float rayhit_eps = 5e-7;
    static constexpr int maxReflectionDepth = 1;
    std::shared_ptr<Object> skybox = std::make_shared<Skybox>(sf::Color(0,0,60));
    
    
    
    
    
    
    // Create the objects in the scene
    void makeObjects();
    
    
    
    
    
    
};  // class Scene




} //namespace rgl


#endif /* Scene_hpp */
