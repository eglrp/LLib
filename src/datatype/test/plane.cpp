#include "../plane.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../utils/doctest.h"

using namespace LLib;

TEST_CASE("Inilization")
{
    planef p1(vec3f::Constant(2));

    CHECK_EQ(p1.getNormal(), vec3f::Constant(2)/vec3f::Constant(2).norm());
    CHECK_EQ(p1.getDistance(),vec3f::Constant(2).norm());
    CHECK_EQ(p1.distanceToPoint(vec3f::Zero()), float(sqrt(12)));
}