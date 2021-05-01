//
//  ObjectTest.hpp
//  GraphicsAPI
//
//  Created by Jeb Collins on 4/1/21.
//

#ifndef ObjectTest_h
#define ObjectTest_h

#include <iostream>
#include <cmath>

#include "gtest/gtest.h"
#include "Object.hpp"
#include <SFML/Graphics.hpp>


class ObjectIntersect : public testing::Test
{
protected:
    double tol = 1e-5;
    sf::Vector3f sphere_center{-0.4876, 1.00345, 3.9823};
    float sphere_radius = 1.5639;
    rgl::Sphere sphere{sphere_center, sphere_radius};
    
    std::vector<sf::Vector3f> plane_verts;
    sf::Vector3f plane_vert1{-0.5, -0.872, 1.76};
    sf::Vector3f plane_vert2{-.53, .872, 2.69};
    sf::Vector3f plane_vert3{0.5, .662, 1.56};
    sf::Vector3f plane_vert4{0.5, -.872, 1.52};
    
    rgl::Plane plane;
    
    
    void SetUp() override
    {
        plane_verts.push_back(plane_vert1);
        plane_verts.push_back(plane_vert2);
        plane_verts.push_back(plane_vert3);
        plane_verts.push_back(plane_vert4);
        
        plane = rgl::Plane(plane_verts);
    }
};

TEST_F(ObjectIntersect, SphereNormalRay)
{
    sf::Vector3f rayP{0,0,1};
    sf::Vector3f rayD = sphere_center;
    rayD.z -= 1.0f;
    
    float t;
    sf::Vector3f objP;
    bool didHit;
    
    didHit = sphere.intersect(rayP, rayD, 0, INFINITY, t, objP);
    sf::Vector3f normal = sphere.normal(objP);
    
    EXPECT_TRUE(didHit);
    EXPECT_LT(std::fabs(t - .5088477337), tol);
    EXPECT_LT(std::fabs(objP.x - (-.248114154941089)), tol);
    EXPECT_LT(std::fabs(objP.y - .510603258358564), tol);
    EXPECT_LT(std::fabs(objP.z - 2.51753659614604), tol);
    
    EXPECT_LT(std::fabs(normal.x - (.239485845058911)), tol);
    EXPECT_LT(std::fabs(normal.y - (-.492846741641436)), tol);
    EXPECT_LT(std::fabs(normal.z - (-1.46476340385396)), tol);
};



TEST_F(ObjectIntersect, SphereRayOutsidetRange)
{
    sf::Vector3f rayP{0,0,1};
    sf::Vector3f rayD = sphere_center;
    rayD.z -= 1.0f;
    
    float t;
    sf::Vector3f objP;
    bool didHit;
    
    didHit = sphere.intersect(rayP, rayD, 0, 0.5, t, objP);
    
    EXPECT_FALSE(didHit);
    
    
    didHit = sphere.intersect(rayP, rayD, 0.6, INFINITY, t, objP);
    
    EXPECT_FALSE(didHit);
};






TEST_F(ObjectIntersect, SphereMiss)
{
    sf::Vector3f rayP{0,0,0};
    sf::Vector3f rayD{0, 2, .5};
    
    float t;
    sf::Vector3f objP;
    bool didHit;
    
    didHit = sphere.intersect(rayP, rayD, 0, INFINITY, t, objP);
    
    EXPECT_FALSE(didHit);
    
    
};








TEST_F(ObjectIntersect, SphereObliqueRay)
{
    sf::Vector3f rayP{.567, -1.09, 2.123};
    sf::Vector3f rayD = (sphere_center + sf::Vector3f(.2, .6, -.5)) - rayP;
    
    float t;
    sf::Vector3f objP;
    bool didHit;
    
    didHit = sphere.intersect(rayP, rayD, 0, INFINITY, t, objP);
    sf::Vector3f normal = sphere.normal(objP);
    
    EXPECT_TRUE(didHit);
    EXPECT_LT(std::fabs(t - .487757714748829), tol);
    EXPECT_LT(std::fabs(objP.x - (.150162256975651)), tol);
    EXPECT_LT(std::fabs(objP.y - .223751016790234), tol);
    EXPECT_LT(std::fabs(objP.z - 2.78600906165808), tol);
    
    EXPECT_LT(std::fabs(normal.x - (.637762256975651)), tol);
    EXPECT_LT(std::fabs(normal.y - (-.779698983209766)), tol);
    EXPECT_LT(std::fabs(normal.z - (-1.19629093834192)), tol);
};
























TEST_F(ObjectIntersect, PlaneNormalRay)
{
    sf::Vector3f rayP{-.385946666666667, .170733333333333, 1.11800000000000};
    sf::Vector3f rayD{.418560000000000, -.922800000000000, 1.74400000000000};
    
    float t;
    sf::Vector3f objP;
    bool didHit;
    
    didHit = plane.intersect(rayP, rayD, 0, INFINITY, t, objP);
    sf::Vector3f normal = plane.normal(objP);

    
    EXPECT_TRUE(didHit);
    EXPECT_LT(std::fabs(t - .5), tol);
    EXPECT_LT(std::fabs(objP.x - (-.176666666666667)), tol);
    EXPECT_LT(std::fabs(objP.y - (-.290666666666667)), tol);
    EXPECT_LT(std::fabs(objP.z - (1.99000000000000)), tol);
    
    EXPECT_LT(std::fabs(normal.x - (-rayD.x)), tol);
    EXPECT_LT(std::fabs(normal.y - (-rayD.y)), tol);
    EXPECT_LT(std::fabs(normal.z - (-rayD.z)), tol);
    
};






TEST_F(ObjectIntersect, PlaneObliqueRay)
{
    sf::Vector3f rayP{-.385946666666667, .170733333333333, 1.11800000000000};
    sf::Vector3f rayD{.618560000000000, -1.02280000000000, 2.74400000000000};
    
    float t;
    sf::Vector3f objP;
    bool didHit;
    
    didHit = plane.intersect(rayP, rayD, 0, INFINITY, t, objP);

    
    EXPECT_TRUE(didHit);
    EXPECT_LT(std::fabs(t - (.339687531356916)), tol);
    EXPECT_LT(std::fabs(objP.x - (-.175829547270533)), tol);
    EXPECT_LT(std::fabs(objP.y - (-.176699073738520)), tol);
    EXPECT_LT(std::fabs(objP.z - (2.05010258604338)), tol);
    
    
};






TEST_F(ObjectIntersect, PlaneMissBounds)
{
    sf::Vector3f rayP{.176666666666667, 2.70933333333333, 1.99000000000000};
    sf::Vector3f rayD{.418560000000000, -.922800000000000, 1.74400000000000};

    float t;
    sf::Vector3f objP;
    bool didHit;
    
    didHit = plane.intersect(rayP, rayD, 0, INFINITY, t, objP);

    
    EXPECT_FALSE(didHit);
    
    
};







TEST_F(ObjectIntersect, PlaneMissParallel)
{
    sf::Vector3f rayP{0, 0, 0};
    sf::Vector3f rayD{-1.40900400000000, -2.26929280000000, -.862586400000000};

    float t;
    sf::Vector3f objP;
    bool didHit;
    
    didHit = plane.intersect(rayP, rayD, 0, INFINITY, t, objP);

    
    EXPECT_FALSE(didHit);
    
    
};






TEST_F(ObjectIntersect, PlaneMisstBounds)
{
    sf::Vector3f rayP{-.385946666666667, .170733333333333, 1.11800000000000};
    sf::Vector3f rayD{.618560000000000, -1.02280000000000, 2.74400000000000};
    
    float t;
    sf::Vector3f objP;
    bool didHit;
    
    didHit = plane.intersect(rayP, rayD, .5, INFINITY, t, objP);

    
    EXPECT_FALSE(didHit);
    
    
    
    didHit = plane.intersect(rayP, rayD, 0, .3, t, objP);

    
    EXPECT_FALSE(didHit);

    
};










class ObjectLight : public testing::Test
{
protected:
    double tol = 1e-5;
    sf::Vector3f objP{.1, -.2, 3.2};
    int specularity = 2;
    
    sf::Vector3f litN{.1, 1, -.5};
    sf::Vector3f shadowN{-.2, 0, 1};
    
    sf::Vector3f camP{0,0,0};
    
    rgl::PointLight ptLight{sf::Vector3f(1.2, .345, 2.965), .41};
    rgl::DirLight dirLight{sf::Vector3f(-.1, -1.32, .154), .95};
    rgl::AmbientLight ambLight{.745};
    
    
};

TEST_F(ObjectLight, AmbLight)
{
    float illum = ambLight.computeIllumination(objP, litN, camP, -1);

    
    EXPECT_LT(std::fabs(illum - (.745)), tol);
};



TEST_F(ObjectLight, PointLightIllumLitNoSpec)
{
    float illum = ptLight.computeIllumination(objP, litN, camP, -1);

    
    EXPECT_LT(std::fabs(illum - (.225746905394113)), tol);
};



TEST_F(ObjectLight, PointLightIllumLitSpec)
{
    float illum = ptLight.computeIllumination(objP, litN, camP, specularity);

    
    EXPECT_LT(std::fabs(illum - (.278918627106688)), tol);
};

TEST_F(ObjectLight, PointLightIllumShadow)
{
    float illum = ptLight.computeIllumination(objP, shadowN, camP, specularity);

    
    EXPECT_LT(std::fabs(illum - (0)), tol);
};






TEST_F(ObjectLight, DirLightIllumLitNoSpec)
{
    float illum = dirLight.computeIllumination(objP, litN, camP, -1);

    
    EXPECT_LT(std::fabs(illum - (.893504546827114)), tol);
};



TEST_F(ObjectLight, DirLightIllumLitSpec)
{
    float illum = dirLight.computeIllumination(objP, litN, camP, specularity);

    
    EXPECT_LT(std::fabs(illum - (1.44283695185005)), tol);
};


TEST_F(ObjectLight, DirLightIllumLShadow)
{
    float illum = dirLight.computeIllumination(objP, shadowN, camP, specularity);

    
    EXPECT_LT(std::fabs(illum - (0)), tol);
};



#endif /* ObjectTest_h */
