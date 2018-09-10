#include "../pointcloud.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../utils/doctest.h"

using namespace LLib;

TEST_CASE("image")
{
    pointcloud2f pc(4);
    pc(0) = vec2f::Constant(0);
    pc(1) = vec2f::Constant(1);
    pc(2) = vec2f::Constant(2);
    pc(3) = vec2f::Constant(3);

    CHECK_EQ(pc[0], vec2f::Constant(0));
    CHECK_EQ(pc[1], vec2f::Constant(1));
    CHECK_EQ(pc[2], vec2f::Constant(2));
    CHECK_EQ(pc[3], vec2f::Constant(3));
}