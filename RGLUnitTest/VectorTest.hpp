//
//  VectorTest.hpp
//  GraphicsAPI
//
//  Created by Jeb Collins on 3/27/21.
//

#ifndef VectorTest_h
#define VectorTest_h


#include <iostream>
#include <cmath>

#include "gtest/gtest.h"
#include "VectorUtil.hpp"
#include <SFML/Graphics.hpp>


class VectorOperations : public testing::Test
{
protected:
    double tol = 1e-5;
    sf::Vector3f u{1.234567f, -9.876543f, 5.647382f};
    sf::Vector3f v{7.12987f, 10.89234f, -3.98167f};
};

TEST_F(VectorOperations, DotProduct1)
{
    EXPECT_LT(std::fabs(rgl::Dot(u,v) -(-121.262373652270014)), tol);
}


TEST_F(VectorOperations, DotProduct2)
{
    EXPECT_LT(std::fabs(rgl::Dot(v,u) -(-121.262373652270014)), tol);
}




TEST_F(VectorOperations, CrossProductUV)
{
    float cross_prod_x = -22.18806988707;
    float cross_prod_y = 45.18073788723;
    float cross_prod_z = 83.86579115619;
    
    sf::Vector3f cross_product = rgl::Cross(u,v);
    
    EXPECT_LT(std::fabs(cross_product.x - cross_prod_x), tol);
    EXPECT_LT(std::fabs(cross_product.y - cross_prod_y), tol);
    EXPECT_LT(std::fabs(cross_product.z - cross_prod_z), tol);

}



TEST_F(VectorOperations, CrossProductVU)
{
    float cross_prod_x = 22.18806988707;
    float cross_prod_y = -45.18073788723;
    float cross_prod_z = -83.86579115619;
    
    sf::Vector3f cross_product = rgl::Cross(v,u);
    
    EXPECT_LT(std::fabs(cross_product.x - cross_prod_x), tol);
    EXPECT_LT(std::fabs(cross_product.y - cross_prod_y), tol);
    EXPECT_LT(std::fabs(cross_product.z - cross_prod_z), tol);

}




TEST_F(VectorOperations, Norm)
{
    float norm_u = 11.4439145733556575;
    float norm_v = 13.6136627283549245;
    
    EXPECT_LT(std::fabs(rgl::Norm(u) - norm_u), tol);
    EXPECT_LT(std::fabs(rgl::Norm(v) - norm_v), tol);

}



TEST_F(VectorOperations, reflection1)
{
    sf::Vector3f R = rgl::reflection(sf::Vector3f(1,-1,0),sf::Vector3f(0,1,0));
    
    float ref_x = 1;
    float ref_y = 1;
    float ref_z = 0;
    
    
    EXPECT_LT(std::fabs(R.x - ref_x), tol);
    EXPECT_LT(std::fabs(R.y - ref_y), tol);
    EXPECT_LT(std::fabs(R.z - ref_z), tol);

}



#endif /* VectorTest_h */
