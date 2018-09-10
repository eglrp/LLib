#include "line3.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../utils/doctest.h"

using namespace LLib;

TEST_CASE("line3")
{
    vec3d p1, p2;
    p1 << 0, 0, 0;
    p2 << 2, 3, 4;
    vec3d dir = p2 - p1;
    dir /= dir.norm();

    line3d l(p1, p2);

    CHECK_EQ(l.getP(), p1);
    CHECK_EQ(l.getDir(), dir);
}