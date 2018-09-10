#include "line2.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../utils/doctest.h"

using namespace LLib;

TEST_CASE("line2")
{
    vec2d p1, p2;
    p1 << 0, 0;
    p2 << 2, 2;
    vec2d dir = p2 - p1;
    dir /= dir.norm();

    line2d l(p1, p2);

    CHECK_EQ(l.getP(), p1);
    CHECK_EQ(l.getDir(), dir);
}