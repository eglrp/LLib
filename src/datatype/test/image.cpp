#include "../image.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../utils/doctest.h"

using namespace LLib;

TEST_CASE("image")
{
    image1f imgf(2, 2);
    imgf(0, 0) = 0;
    imgf(0, 1) = 1;
    imgf(1, 0) = 2;
    imgf(1, 1) = 3;

    CHECK_EQ(imgf[0], 0);
    CHECK_EQ(imgf[1], 1);
    CHECK_EQ(imgf[2], 2);
    CHECK_EQ(imgf[3], 3);
}
