#include <gtest/gtest.h>

#include "../vec3.h"

#include <type_traits>

using namespace LLib;

using v3d = vec3<double>;
using v3f = vec3<float>;
using v3i = vec3<int>;

TEST(VEC3, DATA){
    v3d v(1, 2, 3);

    EXPECT_TRUE((std::is_same<v3f::ValueType, float>::value));

    EXPECT_EQ(v.Dim, 3);
    EXPECT_EQ(v3f::Dim, 3);


    EXPECT_EQ(v.x, 1);
    EXPECT_EQ(v.y, 2);
    EXPECT_EQ(v.z, 3);
    EXPECT_EQ(v.r, 1);
    EXPECT_EQ(v.g, 2);
    EXPECT_EQ(v.b, 3);
    EXPECT_EQ(v.yaw, 1);
    EXPECT_EQ(v.pitch, 2);
    EXPECT_EQ(v.roll, 3);
    EXPECT_EQ(v.array[0], 1);
    EXPECT_EQ(v.array[1], 2);
    EXPECT_EQ(v.array[2], 3);
}

TEST(VEC3, STATIC_FUNC){
    EXPECT_EQ(v3d::zeros(), v3d(0, 0, 0));
    EXPECT_EQ(v3d::ones(), v3d(1, 1, 1));
    EXPECT_EQ(v3d::full(2), v3d(2, 2, 2));
}

TEST(VEC3, CONSTRUCTOR){
    v3d v1;
    v3d v2(1);
    v3i v3(1.0f, 2.0f, 3.0f);
    v3i v4(v2);
    v3i v5(v2.getData());
    EXPECT_EQ(v1, v3d(0, 0, 0));
    EXPECT_EQ(v2, v3d(1, 1, 1));
    EXPECT_EQ(v3, v3i(1, 2, 3));
    EXPECT_EQ(v4, v3i(1, 1, 1));
    EXPECT_EQ(v5, v3i(1, 1, 1));
}

TEST(VEC3, CONVERT_TYPE){
    v3d v1 = v3i(1, 2, 3).toType<double>();

    EXPECT_EQ(v1, v3d(1, 2, 3));
}

TEST(VEC3, ACCESS){
    v3d v(1, 2, 3);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(1), 2);
    EXPECT_EQ(v.at(2), 3);

    ASSERT_DEATH(v.at(3), "Assert");
    ASSERT_DEATH(v[3], "Assert");
}

TEST(VEC3, ASSIGN){
    v3d v = v3d(1, 2, 3);

    EXPECT_EQ(v, v3d(1, 2, 3));
}

TEST(VEC3, NEGATIVE){
    v3d v = -v3d(1, 2, 3);

    EXPECT_EQ(v, v3d(-1, -2, -3));
}

TEST(VEC3, ADD){
    v3d v1 = v3d(1, 2, 3);
    v3d v2 = v3d(2, 3, 4);

    v1 += 1;
    EXPECT_EQ(v1, v3d(2, 3, 4));
    v2 += v1;
    EXPECT_EQ(v2, v3d(4, 6, 8));
    v3d v3 = v1 + v2;
    EXPECT_EQ(v3, v3d(6, 9, 12));
    v3d v4 = v1 + 1;
    EXPECT_EQ(v4, v3d(3, 4, 5));
    v3d v5 = 1 + v1;
    EXPECT_EQ(v5, v3d(3, 4, 5));
}

TEST(VEC3, SUB){
    v3d v1 = v3d(1, 2, 3);
    v3d v2 = v3d(2, 3, 4);

    v1 -= 1;
    EXPECT_EQ(v1, v3d(0, 1, 2));
    v2 -= v1;
    EXPECT_EQ(v2, v3d(2, 2, 2));
    v3d v3 = v1 - v2;
    EXPECT_EQ(v3, v3d(-2, -1, 0));
    v3d v4 = v1 - 1;
    EXPECT_EQ(v4, v3d(-1, 0, 1));
    v3d v5 = 1 - v1;
    EXPECT_EQ(v5, v3d(1, 0, -1));
}

TEST(VEC3, MUL){
    v3d v1 = v3d(1, 2, 3);
    v3d v2 = v3d(2, 3, 4);

    v1 *= 2;
    EXPECT_EQ(v1, v3d(2, 4, 6));
    v2 *= v1;
    EXPECT_EQ(v2, v3d(4, 12, 24));
    v3d v3 = v1 * v2;
    EXPECT_EQ(v3, v3d(8, 48, 144));
    v3d v4 = v1 * 2;
    EXPECT_EQ(v4, v3d(4, 8, 12));
    v3d v5 = 2 * v1;
    EXPECT_EQ(v5, v3d(4, 8, 12));
}

TEST(VEC3, DIV){
    v3d v1 = v3d(1, 2, 4);
    v3d v2 = v3d(2, 4, 8);

    v1 /= 2;
    EXPECT_EQ(v1, v3d(0.5, 1, 2));
    v2 /= v1;
    EXPECT_EQ(v2, v3d(4, 4, 4));
    v3d v3 = v1 / v2;
    EXPECT_EQ(v3, v3d(0.125, 0.25, 0.5));
    v3d v4 = v1 / 2;
    EXPECT_EQ(v4, v3d(0.25, 0.5, 1));
    v3d v5 = 2 / v1;
    EXPECT_EQ(v5, v3d(4, 2, 1));

    ASSERT_DEATH(v1/0, "Assert");
    ASSERT_DEATH(v1/v3d(0, 0, 0), "Assert");
}

TEST(VEC3, BOOL){
    EXPECT_TRUE(v3d(1, 2, 3) == v3d(1, 2, 3));
    EXPECT_TRUE(v3d(1, 2, 3) != v3d(1, 1, 3));
}

TEST(VEC3, DOT){
    v3d v1(1, 2, 3);
    v3d v2(3, 4, 5);
    EXPECT_EQ(v1.dot(v2), 26);
    EXPECT_EQ(dot(v1, v2), 26);
}

TEST(VEC3, LENGTH){
    v3d v(1, 2, 3);
    EXPECT_EQ(v.lengthSq(), 14);
    EXPECT_EQ(v.length(), sqrt(14));
}

TEST(VEC3, DISTANCE){
    v3d v1(1, 2, 3);
    v3d v2(3, 4, 5);

    EXPECT_EQ(distSq(v1, v2), 12);
    EXPECT_EQ(dist(v1, v2), sqrt(12));
}

TEST(VEC3, NORMALIZE){
    v3f v(3, 4, 5);

    EXPECT_TRUE(Math::floatEqual(v.getNormalize(), v3f(3/sqrt(50), 4/sqrt(50), 5/sqrt(50))));
    EXPECT_TRUE(Math::floatEqual(v.normalize(), v3f(3/sqrt(50), 4/sqrt(50), 5/sqrt(50))));
}

TEST(VEC3, PER_ELEMENT_FUNC){
    v3f v(1.3, 1.6, 1.5);
    v3f vn(1.3, -1.6, 1.5);

    EXPECT_TRUE(Math::floatEqual(v.frac(), v3f(0.3, 0.6, 0.5)));
    EXPECT_TRUE(Math::floatEqual(Math::frac(v), v3f(0.3, 0.6, 0.5)));
    EXPECT_EQ(v.round(), v3f(1, 2, 2));
    EXPECT_EQ(Math::round(v), v3f(1, 2, 2));
    EXPECT_EQ(v.ceil(), v3f(2, 2, 2));
    EXPECT_EQ(Math::ceil(v), v3f(2, 2, 2));
    EXPECT_EQ(v.floor(), v3f(1, 1, 1));
    EXPECT_EQ(Math::floor(v), v3f(1, 1, 1));
    EXPECT_EQ(vn.abs(), v3f(1.3, 1.6, 1.5));
    EXPECT_EQ(Math::abs(vn), v3f(1.3, 1.6, 1.5));

}

TEST(VEC3, STATISTICS_FUNC){
    v3f v(1, 2, 3);
    
    EXPECT_EQ(v.sum(), 6);
    EXPECT_EQ(Math::sum(v), 6);
    EXPECT_EQ(v.mean(), 2);
    EXPECT_EQ(Math::mean(v), 2);
    EXPECT_EQ(v.var(), 2.0/3);
    EXPECT_EQ(Math::var(v), 2.0/3);
}

TEST(VEC3, IN_OUT){
    v3f v;
    std::cout << "Input vec3 : ";
    std::cin >> v;
    std::cout << v << std::endl;
}

TEST(VEC3, MIN_MAX){
    v3f v(1, 3, 5);

    EXPECT_EQ(Math::max(v, 2.0f), v3f(2, 3, 5));
    EXPECT_EQ(Math::max(v, v3f(2, 2, 7)), v3f(2, 3, 7));
    EXPECT_EQ(Math::min(v, 2.0f), v3f(1, 2, 2));
    EXPECT_EQ(Math::min(v, v3f(2, 2, 1)), v3f(1, 2, 1));
}

TEST(VEC3, CROSS){
    v3f v1(1, 2, 3);
    v3f v2(2, 3, 4);

    EXPECT_EQ(v1.cross(v2), v3f(-1, 2, -1));
    EXPECT_EQ(v1^(v2), v3f(-1, 2, -1));
    EXPECT_EQ(cross(v1, v2), v3f(-1, 2, -1));
}

// TEST(VEC3, HOMOGENIZE){
//     v3f v1(1, 2, 3);

//     EXPECT_EQ(v1.getHomogenize(), vec4<float>(1, 2, 3, 1));
// }