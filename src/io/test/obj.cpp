#include "../obj.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../utils/doctest.h"

using namespace LLib;

TEST_CASE("obj")
{
    // TODO: not work
    // obj objfile1;
    // objfile1.load("../data/cornell_box.mtl");
    // objfile1.print();
    // objfile1.write("../data/cornell_box_copy.mtl");

    obj objfile2;
    objfile2.load("../data/cornell_box.obj");
    objfile2.print();
    objfile2.write("../data/cornell_box_copy.obj");
}