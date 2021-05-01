//
//  main.cpp
//  RGLUnitTest
//
//  Created by Jeb Collins on 3/25/21.
//

#include<gtest/gtest.h>

#include "VectorTest.hpp"
#include "ObjectTest.hpp"

int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



