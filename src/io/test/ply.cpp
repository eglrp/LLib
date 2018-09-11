#define TINYPLY_IMPLEMENTATION
#include "../ply.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../utils/doctest.h"

using namespace LLib;

TEST_CASE("ply")
{
    ply plyfile("../data/scene.ply");
    plyfile.print();
    // TODO:
    // plyfile.write_ascii("../data/scene_ascii.ply");
    // plyfile.write_binary("../data/scene_binary.ply");
}
