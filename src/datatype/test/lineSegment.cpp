#include "../lineSegment.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../utils/doctest.h"

using namespace LLib;

TEST_CASE("lineSegment")
{
    vec2d p1, p2;
    p1 << 0, 0;
    p2 << 2, 2;

    lineSegment2d l1(p1, p2);

    CHECK_EQ(l1.getP0(), p1);
    CHECK_EQ(l1.getP1(), p2);

    vec3d p3, p4;
    p3 << 0, 0, 0;
    p4 << 2, 2, 3;

    lineSegment3d l2(p3, p4);

    CHECK_EQ(l2.getP0(), p3);
    CHECK_EQ(l2.getP1(), p4);
}