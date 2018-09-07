#include <gtest/gtest.h>

#include "../vec4.h"

#include <type_traits>

using namespace LLib;

using v4d = vec4<double>;
using v4f = vec4<float>;
using v4i = vec4<int>;

TEST(VEC4, DATA){
    v4d v(1, 2, 3, 4);

    EXPECT_TRUE((std::is_same<v4f::ValueType, float>::value));

    EXPECT_EQ(v.Dim, 4);
    EXPECT_EQ(v4f::Dim, 4);


    EXPECT_EQ(v.x, 1);
    EXPECT_EQ(v.y, 2);
    EXPECT_EQ(v.z, 3);
    EXPECT_EQ(v.w, 4);
    EXPECT_EQ(v.r, 1);
    EXPECT_EQ(v.g, 2);
    EXPECT_EQ(v.b, 3);
    EXPECT_EQ(v.a, 4);
    EXPECT_EQ(v.array[0], 1);
    EXPECT_EQ(v.array[1], 2);
    EXPECT_EQ(v.array[2], 3);
    EXPECT_EQ(v.array[3], 4);
}

TEST(VEC4, STATIC_FUNC){
    EXPECT_EQ(v4d::zeros(), v4d(0, 0, 0, 0));
    EXPECT_EQ(v4d::ones(), v4d(1, 1, 1, 1));
    EXPECT_EQ(v4d::full(2), v4d(2, 2, 2, 2));
}

TEST(VEC4, CONSTRUCTOR){
    v4d v1;
    v4d v2(1);
    v4i v3(1.0f, 2.0f, 3.0f, 4.0f);
    v4i v4(v2);
    v4i v5(v2.getData());
    v4i v6(v2.getDehomogenize());
    EXPECT_EQ(v1, v4d(0, 0, 0, 0));
    EXPECT_EQ(v2, v4d(1, 1, 1, 1));
    EXPECT_EQ(v3, v4i(1, 2, 3, 4));
    EXPECT_EQ(v4, v4i(1, 1, 1, 1));
    EXPECT_EQ(v5, v4i(1, 1, 1, 1));
    EXPECT_EQ(v6, v4i(1, 1, 1, 1));
}

TEST(VEC4, CONVERT_TYPE){
    v4d v1 = v4i(1, 2, 3, 4).toType<double>();

    EXPECT_EQ(v1, v4d(1, 2, 3, 4));
}

TEST(VEC4, ACCESS){
    v4d v(1, 2, 3, 4);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(1), 2);
    EXPECT_EQ(v.at(2), 3);
    EXPECT_EQ(v.at(3), 4);

    ASSERT_DEATH(v.at(4), "Assert");
    ASSERT_DEATH(v[4], "Assert");
}

TEST(VEC4, ASSIGN){
    v4d v = v4d(1, 2, 3, 4);

    EXPECT_EQ(v, v4d(1, 2, 3, 4));
}

TEST(VEC4, NEGATIVE){
    v4d v = -v4d(1, 2, 3, 4);

    EXPECT_EQ(v, v4d(-1, -2, -3, -4));
}

TEST(VEC4, ADD){
    v4d v1 = v4d(1, 2, 3, 2);
    v4d v2 = v4d(2, 3, 4, 2);

    v1 += 1;
    EXPECT_EQ(v1, v4d(2, 3, 4, 3));
    v2 += v1;
    EXPECT_EQ(v2, v4d(4, 6, 8, 5));
    v4d v3 = v1 + v2;
    EXPECT_EQ(v3, v4d(6, 9, 12, 8));
    v4d v4 = v1 + 1;
    EXPECT_EQ(v4, v4d(3, 4, 5, 4));
    v4d v5 = 1 + v1;
    EXPECT_EQ(v5, v4d(3, 4, 5, 4));
}

TEST(VEC4, SUB){
    v4d v1 = v4d(1, 2, 3, 4);
    v4d v2 = v4d(2, 3, 4, 5);

    v1 -= 1;
    EXPECT_EQ(v1, v4d(0, 1, 2, 3));
    v2 -= v1;
    EXPECT_EQ(v2, v4d(2, 2, 2, 2));
    v4d v3 = v1 - v2;
    EXPECT_EQ(v3, v4d(-2, -1, 0, 1));
    v4d v4 = v1 - 1;
    EXPECT_EQ(v4, v4d(-1, 0, 1, 2));
    v4d v5 = 1 - v1;
    EXPECT_EQ(v5, v4d(1, 0, -1, -2));
}

TEST(VEC45, MUL){
    v4d v1 = v4d(1, 2, 3, 2);
    v4d v2 = v4d(2, 3, 4, 2);

    v1 *= 2;
    EXPECT_EQ(v1, v4d(2, 4, 6, 4));
    v2 *= v1;
    EXPECT_EQ(v2, v4d(4, 12, 24, 8));
    v4d v3 = v1 * v2;
    EXPECT_EQ(v3, v4d(8, 48, 144, 32));
    v4d v4 = v1 * 2;
    EXPECT_EQ(v4, v4d(4, 8, 12, 8));
    v4d v5 = 2 * v1;
    EXPECT_EQ(v5, v4d(4, 8, 12, 8));
}

TEST(VEC4, DIV){
    v4d v1 = v4d(1, 2, 4, 8);
    v4d v2 = v4d(2, 4, 2, 4);

    v1 /= 2;
    EXPECT_EQ(v1, v4d(0.5, 1, 2, 4));
    v2 /= v1;
    EXPECT_EQ(v2, v4d(4, 4, 1, 1));
    v4d v3 = v1 / v2;
    EXPECT_EQ(v3, v4d(0.125, 0.25, 2, 4));
    v4d v4 = v1 / 2;
    EXPECT_EQ(v4, v4d(0.25, 0.5, 1, 2));
    v4d v5 = 2 / v1;
    EXPECT_EQ(v5, v4d(4, 2, 1, 0.5));

    ASSERT_DEATH(v1/0, "Assert");
    ASSERT_DEATH(v1/v4d(1, 0, 0, 0), "Assert");
}

TEST(VEC4, BOOL){
    EXPECT_TRUE(v4d(1, 2, 3, 4) == v4d(1, 2, 3, 4));
    EXPECT_TRUE(v4d(1, 2, 3, 4) != v4d(1, 1, 3, 4));
}

TEST(VEC4, DOT){
    v4d v1(1, 2, 3, 4);
    v4d v2(3, 4, 5, 6);
    EXPECT_EQ(v1.dot(v2), 50);
    EXPECT_EQ(dot(v1, v2), 50);
}

TEST(VEC4, LENGTH){
    v4d v(1, 2, 3, 4);
    EXPECT_EQ(v.lengthSq(), 30);
    EXPECT_EQ(v.length(), sqrt(30));
}

TEST(VEC4, DISTANCE){
    v4d v1(1, 2, 3, 4);
    v4d v2(3, 4, 5, 6);

    EXPECT_EQ(distSq(v1, v2), 16);
    EXPECT_EQ(dist(v1, v2), 4);
}

TEST(VEC4, NORMALIZE){
    v4f v(3, 4, 5, 6);

    EXPECT_TRUE(Math::floatEqual(v.getNormalize(), v4f(3/sqrt(86), 4/sqrt(86), 5/sqrt(86), 6/sqrt(86))));
    EXPECT_TRUE(Math::floatEqual(v.normalize(), v4f(3/sqrt(86), 4/sqrt(86), 5/sqrt(86), 6/sqrt(86))));
}

TEST(VEC4, PER_ELEMENT_FUNC){
    v4f v(1.3, 1.6, 1.5, 1.2);
    v4f vn(1.3, -1.6, 1.5, -1.2);

    EXPECT_TRUE(Math::floatEqual(v.frac(), v4f(0.3, 0.6, 0.5, 0.2)));
    EXPECT_TRUE(Math::floatEqual(Math::frac(v), v4f(0.3, 0.6, 0.5, 0.2)));
    EXPECT_EQ(v.round(), v4f(1, 2, 2, 1));
    EXPECT_EQ(Math::round(v), v4f(1, 2, 2, 1));
    EXPECT_EQ(v.ceil(), v4f(2, 2, 2, 2));
    EXPECT_EQ(Math::ceil(v), v4f(2, 2, 2, 2));
    EXPECT_EQ(v.floor(), v4f(1, 1, 1, 1));
    EXPECT_EQ(Math::floor(v), v4f(1, 1, 1, 1));
    EXPECT_EQ(vn.abs(), v4f(1.3, 1.6, 1.5, 1.2));
    EXPECT_EQ(Math::abs(vn), v4f(1.3, 1.6, 1.5, 1.2));

}

TEST(VEC4, STATISTICS_FUNC){
    v4f v(1, 2, 3, 4);
    
    EXPECT_EQ(v.sum(), 10);
    EXPECT_EQ(Math::sum(v), 10);
    EXPECT_EQ(v.mean(), 2.5);
    EXPECT_EQ(Math::mean(v), 2.5);
    EXPECT_EQ(v.var(), 1.25);
    EXPECT_EQ(Math::var(v), 1.25);
}

TEST(VEC4, IN_OUT){
    v4f v;
    std::cout << "Input vec4 : ";
    std::cin >> v;
    std::cout << v << std::endl;
}

TEST(VEC4, MIN_MAX){
    v4f v(1, 3, 5, 7);

    EXPECT_EQ(Math::max(v, 5.5f), v4f(5.5, 5.5, 5.5, 7));
    EXPECT_EQ(Math::max(v, v4f(2, 2, 7, 5)), v4f(2, 3, 7, 7));
    EXPECT_EQ(Math::min(v, 5.5f), v4f(1, 3, 5, 5.5));
    EXPECT_EQ(Math::min(v, v4f(2, 2, 1, 7)), v4f(1, 2, 1, 7));
}

TEST(VEC4, CROSS){
    v4f v1(1, 2, 3, 4);
    v4f v2(2, 3, 4, 1);

    EXPECT_EQ(v1.cross(v2), v4f(-1, 2, -1, 1));
    EXPECT_EQ(v1^(v2), v4f(-1, 2, -1, 1));
    EXPECT_EQ(cross(v1, v2), v4f(-1, 2, -1, 1));
}

TEST(VEC4, DEHOMOGENIZE){
    v4f v1(1, 2, 3, 4);
    v4f v2(1, 2, 3, 0);

    EXPECT_EQ(v1.getDehomogenize(), vec3<float>(0.25, 0.5, 0.75));
    EXPECT_EQ(v1.dehomogenize(), v4f(0.25, 0.5, 0.75, 1));
    ASSERT_DEATH(v2.getDehomogenize(), "Assert");
    ASSERT_DEATH(v2.dehomogenize(), "Assert");
}