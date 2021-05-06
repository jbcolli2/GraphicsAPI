//
//  SceneTest.hpp
//  GraphicsAPI
//
//  Created by Jeb Collins on 5/2/21.
//

#ifndef SceneTest_h
#define SceneTest_h

#include <iostream>
#include <cmath>
#include <limits>

#include "gtest/gtest.h"
#include "Object.hpp"
#include "Scene.hpp"
#include <SFML/Graphics.hpp>




class SceneTest : public Testing::Test
{
    Scene scene;
    double tol = 1e-5;
    float inf = std::numerical_limits<float>::infinity();
}



TEST_F(SceneTest, NoIntersect)
{
    scene.addPlane(sf::Vector3f(-2, -.5, 0), sf::Vector3f(-2, -.4, 5), sf::Vector3f(2, -.4, 5), sf::Vector3f(2, -.5, 0));
    scene.addSphere(sf::Vector3f(.5, 1, .5), .5);
    
    scene.nearestIntersection(sf::Vector3f(0,0,0), sf::Vector3f(-.5, 0, 1), 0, inf)
}


#endif /* SceneTest_h */
