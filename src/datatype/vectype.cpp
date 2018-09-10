#include "vectype.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../utils/doctest.h"

using namespace LLib;

TEST_CASE("Inilization")
{
    vecXd vx1(3);
    vx1(0) = 0;
    vx1(1) = 1;
    vx1(2) = 2;

    vecXd vx2(3);
    vx2 << 0, 1, 2;

    CHECK_EQ(vx1, vx2);

    vec3f v1;
    v1(0) = 0;
    v1(1) = 1;
    v1(2) = 2;

    vec3f v2;
    v2 << 0, 1, 2;

    CHECK_EQ(v1, v2);

    vecXf vx(3);
    vx << 0, 1, 2;

    CHECK_EQ(v1, vx);

    CHECK_EQ(vecXf::Constant(2, 1), (vecXf(2) << 1, 1).finished());
    CHECK_EQ(vecXf::Zero(2), (vecXf(2) << 0, 0).finished());
    CHECK_EQ(vecXf::Constant(2, 2), (vecXf(2) << 2, 2).finished());
    CHECK_EQ(vecXf::LinSpaced(3, 0, 20), (vecXf(3) << 0, 10, 20).finished());
}

TEST_CASE("Resizing")
{
    vecXd vx(3);
    CHECK_EQ(vx.rows(), 3);
    CHECK_EQ(vx.size(), 3);

    vx.resize(2);
    CHECK_EQ(vx.size(),2);
}

TEST_CASE("Block")
{
/*
    Block containing the first n elements *	                vector.head(n);         vector.head<n>();
    Block containing the last n elements *	                vector.tail(n);         vector.tail<n>();
    Block containing n elements, starting at position i *	vector.segment(i,n);    vector.segment<n>(i);
*/
}

TEST_CASE("Operation")
{
    // v.dot(w)
    // v.cross(w)

    // Reduction
    // v.sum()
    // v.prod()
    // v.mean()
    // v.minCoeff()
    // v.minCoeff(&i) return position in (i)
    // v.maxCoeff()
    // v.maxCoeff(&i) return position in (i)
}