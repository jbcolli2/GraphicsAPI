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
#include "Ray.hpp"
#include "Scene.hpp"
#include <SFML/Graphics.hpp>


using namespace rgl;

class SceneTest : public testing::Test
{
protected:
    double tol = 1e-5;
};



TEST_F(SceneTest, NoHit)
{
    Scene scene;

    scene.addPlane(sf::Vector3f(-2, -.5, 0), sf::Vector3f(-2, -.4, 5), sf::Vector3f(2, -.4, 5), sf::Vector3f(2, -.5, 0));
    scene.addSphere(sf::Vector3f(.5, 1, .5), .5);
    
    Ray ray(sf::Vector3f(0,0,0), sf::Vector3f(-.5,0,1));
    sf::Vector3f objP;
    std::shared_ptr<Object> obj;
    bool isHit = scene.nearestIntersection(ray, objP, obj);
    
    EXPECT_FALSE(isHit);
}












TEST_F(SceneTest, SpherePlaneHitBoth)
{
    Scene scene;
    int spec = 23;

    scene.addPlane(sf::Vector3f(-2, -5, 5), sf::Vector3f(-2, 4, 5), sf::Vector3f(2, 4, 5.1), sf::Vector3f(2, -4,4.9));
    scene.addSphere(sf::Vector3f(0, 0, 3), 1, sf::Color::Red, spec);
    
    Ray ray(sf::Vector3f(0,0,0), sf::Vector3f(0,0.1,1));
    sf::Vector3f objP;
    std::shared_ptr<Object> obj;
    bool isHit = scene.nearestIntersection(ray, objP, obj);
    
    EXPECT_TRUE(isHit);
    
    EXPECT_LT(std::fabs(objP.x - (0)), tol);
    EXPECT_LT(std::fabs(objP.y - (.2020627421)), tol);
    EXPECT_LT(std::fabs(objP.z - (2.020627421)), tol);
    EXPECT_EQ(obj->getSpecularity(), spec);
}










TEST_F(SceneTest, PlaneSphereHitBoth)
{
    Scene scene;
    int spec = 13;

    scene.addPlane(sf::Vector3f(-5, -5, 1.5), sf::Vector3f(-5, 5, 1.5), sf::Vector3f(5, 5, 2.5), sf::Vector3f(5, -5,2.5), sf::Color::Blue, spec);
    scene.addSphere(sf::Vector3f(-.5, 0, 6), 3, sf::Color::Red, spec);
    
    Ray ray(sf::Vector3f(0,0,0), sf::Vector3f(-.2,0,10));
    sf::Vector3f objP;
    std::shared_ptr<Object> obj;
    bool isHit = scene.nearestIntersection(ray, objP, obj);
    
    EXPECT_TRUE(isHit);
    
    EXPECT_LT(std::fabs(objP.x - (-0.3992015968e-1)), tol);
    EXPECT_LT(std::fabs(objP.y - (0)), tol);
    EXPECT_LT(std::fabs(objP.z - (1.996007984)), tol);
    EXPECT_EQ(obj->getSpecularity(), spec);
}









TEST_F(SceneTest, SphereSphereHitOne)
{
    Scene scene;
    int spec = 15;

    scene.addSphere(sf::Vector3f(-1.5, 0, 3), .98, sf::Color::Red, spec);
    scene.addSphere(sf::Vector3f(1.6, .11, 2), 1.5, sf::Color::Red, spec-1);
    
    Ray ray(sf::Vector3f(0,0,0), sf::Vector3f(-.5,0.1,1));
    sf::Vector3f objP;
    std::shared_ptr<Object> obj;
    bool isHit = scene.nearestIntersection(ray, objP, obj);
    
    EXPECT_TRUE(isHit);
    
    EXPECT_LT(std::fabs(objP.x - (-1.072354771)), tol);
    EXPECT_LT(std::fabs(objP.y - (.2144709542)), tol);
    EXPECT_LT(std::fabs(objP.z - (2.144709542)), tol);
    EXPECT_EQ(obj->getSpecularity(), spec);
}











TEST_F(SceneTest, SphereSphereHitBoth)
{
    Scene scene;
    int spec = 13;

    scene.addSphere(sf::Vector3f(-1.5, 0, 3), .98, sf::Color::Red, spec);
    scene.addSphere(sf::Vector3f(-1.6, .11, 6), 1.5, sf::Color::Red, spec-1);
    
    Ray ray(sf::Vector3f(0,0,0), sf::Vector3f(-.5,0.1,1));
    sf::Vector3f objP;
    std::shared_ptr<Object> obj;
    bool isHit = scene.nearestIntersection(ray, objP, obj);
    
    EXPECT_TRUE(isHit);
    
    EXPECT_LT(std::fabs(objP.x - (-1.072354771)), tol);
    EXPECT_LT(std::fabs(objP.y - (.2144709542)), tol);
    EXPECT_LT(std::fabs(objP.z - (2.144709542)), tol);
    EXPECT_EQ(obj->getSpecularity(), spec);
}













TEST_F(SceneTest, FloorSphereHitFloor)
{
    int spec = 17;
    Scene scene;

    std::shared_ptr<Plane> plane = std::make_shared<Plane>(sf::Vector3f(-2, -.5, 0), sf::Vector3f(-2, -.5, 5), sf::Vector3f(2, -.5, 5), sf::Vector3f(2, -.5, 0), sf::Color::Blue, spec);
    scene.addObject(plane);
    scene.addSphere(sf::Vector3f(.5, 1, 2.5), .5);
    
    
    Ray ray(sf::Vector3f(0,0,0), sf::Vector3f(-.5,-.3,1));
    sf::Vector3f objP;
    std::shared_ptr<Object> obj;
    bool isHit = scene.nearestIntersection(ray, objP, obj);
    
    EXPECT_TRUE(isHit);
    
    EXPECT_LT(std::fabs(objP.x - (-.8333333335)), tol);
    EXPECT_LT(std::fabs(objP.y - (-.5000000001)), tol);
    EXPECT_LT(std::fabs(objP.z - (1.666666667)), tol);
    EXPECT_EQ(obj->getSpecularity(), spec);
}












TEST_F(SceneTest, FloorSphereHitSphere)
{
    int spec = 17;
    Scene scene;

    std::shared_ptr<Plane> plane = std::make_shared<Plane>(sf::Vector3f(-2, -.5, 0), sf::Vector3f(-2, -.5, 5), sf::Vector3f(2, -.5, 5), sf::Vector3f(2, -.5, 0), sf::Color::Blue, spec);
    scene.addObject(plane);
    scene.addSphere(sf::Vector3f(-1.5, 0, 3), .98, sf::Color::Red, spec);

    
    Ray ray(sf::Vector3f(0,0,0), sf::Vector3f(-.5,0.1,1));
    sf::Vector3f objP;
    std::shared_ptr<Object> obj;
    bool isHit = scene.nearestIntersection(ray, objP, obj);
    
    EXPECT_TRUE(isHit);
    
    EXPECT_LT(std::fabs(objP.x - (-1.072354771)), tol);
    EXPECT_LT(std::fabs(objP.y - (.2144709542)), tol);
    EXPECT_LT(std::fabs(objP.z - (2.144709542)), tol);
    EXPECT_EQ(obj->getSpecularity(), spec);
}











TEST_F(SceneTest, SphereHalfBehindCam)
{
    int spec = 18;
    Scene scene;

    scene.addSphere(sf::Vector3f(0, 0.1, 0), 3, sf::Color::Red, spec);

    
    Ray ray(sf::Vector3f(0,0,0), sf::Vector3f(-.5,-.47,.87));
    sf::Vector3f objP;
    std::shared_ptr<Object> obj;
    bool isHit = scene.nearestIntersection(ray, objP, obj);
    
    EXPECT_TRUE(isHit);
    
    EXPECT_LT(std::fabs(objP.x - (-1.333958812)), tol);
    EXPECT_LT(std::fabs(objP.y - (-1.253921283)), tol);
    EXPECT_LT(std::fabs(objP.z - (2.321088333)), tol);
    EXPECT_EQ(obj->getSpecularity(), spec);
}













TEST_F(SceneTest, SphereInFloorHitSphere)
{
    int spec = 21;
    Scene scene;

    scene.addSphere(sf::Vector3f(0, -.5, 3), 1, sf::Color::Red, spec);
    scene.addPlane(sf::Vector3f(-5, -5, -19.5), sf::Vector3f(-5, 5, 30.5), sf::Vector3f(5, 5, 30.5), sf::Vector3f(5, -5,-19.5), sf::Color::Blue, spec+3);
    
    Ray ray(sf::Vector3f(0,0,0), sf::Vector3f(0,-.25,1));
    sf::Vector3f objP;
    std::shared_ptr<Object> obj;
    bool isHit = scene.nearestIntersection(ray, objP, obj);
    
    EXPECT_TRUE(isHit);
    
    EXPECT_LT(std::fabs(objP.x - (0)), tol);
    EXPECT_LT(std::fabs(objP.y - (-.5)), tol);
    EXPECT_LT(std::fabs(objP.z - (2)), tol);
    EXPECT_EQ(obj->getSpecularity(), spec);
}


#endif /* SceneTest_h */
