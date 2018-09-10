#include "lineSegment3.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../utils/doctest.h"

using namespace LLib;

TEST_CASE("lineSegment3")
{
    vec3d p1, p2;
    p1 << 0, 0, 0;
    p2 << 2, 2, 3;

    lineSegment3d l(p1, p2);

    CHECK_EQ(l.getP0(), p1);
    CHECK_EQ(l.getP1(), p2);
}