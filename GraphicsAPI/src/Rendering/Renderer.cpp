//
//  Renderer.cpp
//  GraphicAPI
//
//  Created by Jeb Collins on 2/12/21.
//

#include <stdio.h>
#include <thread>

#include "Renderer.hpp"

namespace rgl
{


//void Renderer::f(int ii)
//{
//    for (int jj = CS_; jj < CN_; ++jj)
//    {
//        sf::Color value = scene_.computePixelValue(ii,jj);
//        canvas_.setPixel(ii, jj, value);
//    }
//    
//}




// /////////////  renderScene  ////////////////
/**
  \brief Draws the scene onto a sprite and displays it in the window.
 
 */
void Renderer::renderScene()
{
    // Fill in the screen pixels
    for (int ii = window->getCanvasE(); ii < window->getCanvasW(); ++ii)
    {
        for (int jj = window->getCanvasS(); jj < window->getCanvasN(); ++jj)
        {
            sf::Color value = computePixelValue(ii,jj);

            window->setPixel(ii, jj, value);
        }
    }
    
    
    

    window->display();
}


/**
 \brief: Draws the scene onto a sprite and displays it in the window.  Function is threaded by assigning each row of pixels on the screen to a thread.
 */
//void Renderer::renderSceneThreaded()
//{
//    std::vector<std::thread> threads;
//    // Fill in the screen pixels
//    for (int ii = CE_; ii < CW_; ++ii)
//    {
////        for (int jj = CS_; jj < CN_; ++jj)
////        {
////            sf::Color value = scene_.computeValue(ii,jj);
////
////            canvas_.setPixel(ii, jj, value);
//            threads.push_back(std::thread(&Renderer::f,this, ii));
////        }
//    }
//    
//    for(auto& th : threads)
//    {
//        th.join();
//    }
//    
//    
//
//    canvas_.setScreenSprite(sprite_);
//    window_.draw(sprite_);
//    
//    
//    window_.display();
//
//}








// /////////////  computePixelValue  ////////////////
/**
    \brief Computes the color value of a single pixel (ii,jj) on the Canvas.
 
    \param canvasX,canvasY The coordinates of the pixel in Canvas coordinates
 
    \returns The color value for that pixel.
 */
sf::Color Renderer::computePixelValue(int canvasX, int canvasY)
{
    float viewX, viewY;
    
    canvasToView(canvasX, canvasY, viewX, viewY);
    sf::Vector3f camDirVector = sf::Vector3f(viewX,viewY,scene->getViewDepth()) - scene->getCameraPos();
    
    sf::Color retValue;
    traceRay(scene->getCameraPos(), camDirVector, 1, INFINITY, retValue);
    
    return retValue;
}











// /////////////  traceRay  ////////////////
/**
    
 
    \brief Follows a ray defined by point P and direction vector D.  Finds the nearest object in the scene the intersects that ray and satisfies t \in [tmin, tmax].
 Returns the rendered value of that intersected object.
 
    \param viewPos Point that defines the ray.  Also the point of view of the reciever of the light bouncing off the object.
    \param D Direction vector of the ray
    \param tmin/tmax Defines the valid interval for the line parameter t
    \param reflectionDepth How many reflections have we calculated thus far.  Essentially what is the recursion depth of this function call.
 
 */
bool Renderer::traceRay(const sf::Vector3f& viewPos, const sf::Vector3f& D, float tmin, float tmax,
                   sf::Color& obj_value, int reflectionDepth)
{
    std::shared_ptr<Object> object;
    sf::Vector3f obj_P{0,0,0};
    
    // Find the intersection of camera ray with the nearest object
    Ray ray{viewPos, D, tmin, tmax};
    bool hitObject = scene->nearestIntersection(ray, obj_P, object);
    obj_value = object->getColor();
    
    if(hitObject)
    {
        obj_value = computeLitValue(obj_P, object->normal(obj_P), viewPos, object->getSpecularity(), obj_value);
        
        if(reflectionDepth <= max_reflections)
        {
            obj_value = computeReflection(obj_P, reflection(obj_P - viewPos, object->normal(obj_P)), reflectionDepth, object->getReflectivity(), obj_value);
        }
        
    }
    
    
    
    return hitObject;
}












// /////////////  computeLitValue  ////////////////
/**
 
 
    \brief Take a point on an object and the raw value of that point and light it.  Modify the value of that object at point objP using the lights from the scene.
 
    \param objP Point on the object
    \param normal Normal vector of the point
    \param specularity Specularity value of the object at that point
    \param rawValue The raw color value of the object at that point.
 
    \returns The color value of the object at point objP after lighting has been taken into account
 */
sf::Color Renderer::computeLitValue(const sf::Vector3f& objP, const sf::Vector3f& normal, const sf::Vector3f& viewPos, int specularity, const sf::Color& rawValue)
{
    float total_illumination = 0;
    sf::Color litValue = rawValue;
    auto scene_lights = scene->getLights();
    for(auto& light : scene_lights)
    {
        if(not scene->isInShadow(objP, light))
        {
            total_illumination += light->computeIllumination(objP, normal, viewPos, specularity);
        }
    }
    
    litValue.r = sf::Uint8(std::min(litValue.r * total_illumination, 255.f));
    litValue.g = sf::Uint8(std::min(litValue.g * total_illumination, 255.f));
    litValue.b = sf::Uint8(std::min(litValue.b * total_illumination, 255.f));
    
    
    return litValue;
}



// /////////////  computeReflection  ////////////////
/**
    \brief Call traceRay again, but this time starting at the hit point on the object and looking in the reflection direction of the camera.
    \param objP The position on the object that the ray is reflecting on
    \param reflectD The reflection direction
    \param reflectionDepth The number of reflections that have been done thus far
    \param reflectivity How reflective the object is.  This is the convex combination parameter \in [0,1]
    \param rawValue[out] The original color before the reflection calculation is done
 
    
 */
sf::Color Renderer::computeReflection(const sf::Vector3f& objP, const sf::Vector3f& reflectD, int reflectionDepth, float reflectivity, const sf::Color& localValue)
{
    sf::Color reflectValue, retValue;
    if(traceRay(objP, reflectD, scene->getRayhit(), INFINITY,reflectValue, reflectionDepth + 1))
    {
        retValue.r = reflectivity*reflectValue.r + (1-reflectivity)*localValue.r;
        retValue.g = reflectivity*reflectValue.g + (1-reflectivity)*localValue.g;
        retValue.b = reflectivity*reflectValue.b + (1-reflectivity)*localValue.b;
    }
    else
    {
        retValue = localValue;
    }
    
    return retValue;
    
    
}











// ///////////// canvasToView   ////////////////
/**
 \brief Converts Canvas pixel coordinates to viewport float coordinates
 

 */
void Renderer::canvasToView(int canvasX, int canvasY, float& viewX, float& viewY)
{
    viewX = canvasX * (scene->getViewWidth()/(2*window->getCanvasW() ));
    viewY = canvasY * (scene->getViewHeight()/(2*window->getCanvasN() ));
}

} // rgl namespace




