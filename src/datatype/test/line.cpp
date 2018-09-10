#include "../line.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../utils/doctest.h"

using namespace LLib;

TEST_CASE("line2")
{
    vec2d p1, p2;
    p1 << 0, 0;
    p2 << 2, 2;
    vec2d dir1 = p2 - p1;
    dir1 /= dir1.norm();

    line2d l1(p1, p2);

    CHECK_EQ(l1.getP(), p1);
    CHECK_EQ(l1.getDir(), dir1);

    vec3d p3, p4;
    p3 << 0, 0, 0;
    p4 << 2, 3, 4;
    vec3d dir2 = p4 - p3;
    dir2 /= dir2.norm();

    line3d l2(p3, p4);

    CHECK_EQ(l2.getP(), p3);
    CHECK_EQ(l2.getDir(), dir2);
}