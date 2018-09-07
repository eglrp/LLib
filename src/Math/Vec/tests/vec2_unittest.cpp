#include <gtest/gtest.h>

#include "../vec2.h"

#include <type_traits>

using namespace LLib;

using v2d = vec2<double>;
using v2f = vec2<float>;
using v2i = vec2<int>;

TEST(VEC2, DATA){
    v2d v(1, 2);

    EXPECT_TRUE((std::is_same<v2f::ValueType, float>::value));

    EXPECT_EQ(v.Dim, 2);
    EXPECT_EQ(v2f::Dim, 2);


    EXPECT_EQ(v.x, 1);
    EXPECT_EQ(v.y, 2);
    EXPECT_EQ(v.width, 1);
    EXPECT_EQ(v.height, 2);
    EXPECT_EQ(v.array[0], 1);
    EXPECT_EQ(v.array[1], 2);
}

TEST(VEC2, STATIC_FUNC){
    EXPECT_EQ(v2d::zeros(), v2d(0, 0));
    EXPECT_EQ(v2d::ones(), v2d(1, 1));
    EXPECT_EQ(v2d::full(2), v2d(2, 2));
}

TEST(VEC2, CONSTRUCTOR){
    v2d v1;
    v2d v2(1);
    v2i v3(1.0f, 2.0f);
    v2i v4(v2);
    v2i v5(v2.getData());
    EXPECT_EQ(v1, v2d(0, 0));
    EXPECT_EQ(v2, v2d(1, 1));
    EXPECT_EQ(v3, v2i(1, 2));
    EXPECT_EQ(v4, v2i(1, 1));
    EXPECT_EQ(v5, v2i(1, 1));
}

TEST(VEC2, CONVERT_TYPE){
    v2d v1 = v2i(1, 2).toType<double>();

    EXPECT_EQ(v1, v2d(1, 2));
}

TEST(VEC2, ACCESS){
    v2d v(1, 2);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(1), 2);

    ASSERT_DEATH(v.at(2), "Assert");
    ASSERT_DEATH(v[2], "Assert");
}

TEST(VEC2, ASSIGN){
    v2d v = v2d(1, 2);

    EXPECT_EQ(v, v2d(1, 2));
}

TEST(VEC2, NEGATIVE){
    v2d v = -v2d(1, 2);

    EXPECT_EQ(v, v2d(-1, -2));
}

TEST(VEC2, ADD){
    v2d v1 = v2d(1, 2);
    v2d v2 = v2d(2, 3);

    v1 += 1;
    EXPECT_EQ(v1, v2d(2, 3));
    v2 += v1;
    EXPECT_EQ(v2, v2d(4, 6));
    v2d v3 = v1 + v2;
    EXPECT_EQ(v3, v2d(6, 9));
    v2d v4 = v1 + 1;
    EXPECT_EQ(v4, v2d(3, 4));
    v2d v5 = 1 + v1;
    EXPECT_EQ(v5, v2d(3, 4));
}

TEST(VEC2, SUB){
    v2d v1 = v2d(1, 2);
    v2d v2 = v2d(2, 3);

    v1 -= 1;
    EXPECT_EQ(v1, v2d(0, 1));
    v2 -= v1;
    EXPECT_EQ(v2, v2d(2, 2));
    v2d v3 = v1 - v2;
    EXPECT_EQ(v3, v2d(-2, -1));
    v2d v4 = v1 - 1;
    EXPECT_EQ(v4, v2d(-1, 0));
    v2d v5 = 1 - v1;
    EXPECT_EQ(v5, v2d(1, 0));
}

TEST(VEC2, MUL){
    v2d v1 = v2d(1, 2);
    v2d v2 = v2d(2, 3);

    v1 *= 2;
    EXPECT_EQ(v1, v2d(2, 4));
    v2 *= v1;
    EXPECT_EQ(v2, v2d(4, 12));
    v2d v3 = v1 * v2;
    EXPECT_EQ(v3, v2d(8, 48));
    v2d v4 = v1 * 2;
    EXPECT_EQ(v4, v2d(4, 8));
    v2d v5 = 2 * v1;
    EXPECT_EQ(v5, v2d(4, 8));
}

TEST(VEC2, DIV){
    v2d v1 = v2d(1, 2);
    v2d v2 = v2d(2, 3);

    v1 /= 2;
    EXPECT_EQ(v1, v2d(0.5, 1));
    v2 /= v1;
    EXPECT_EQ(v2, v2d(4, 3));
    v2d v3 = v1 / v2;
    EXPECT_EQ(v3, v2d(0.125, 1.0/3));
    v2d v4 = v1 / 2;
    EXPECT_EQ(v4, v2d(0.25, 0.5));
    v2d v5 = 2 / v1;
    EXPECT_EQ(v5, v2d(4, 2));

    ASSERT_DEATH(v1/0, "Assert");
    ASSERT_DEATH(v1/v2d(0, 0), "Assert");
}

TEST(VEC2, BOOL){
    EXPECT_TRUE(v2d(1, 2) == v2d(1, 2));
    EXPECT_TRUE(v2d(1, 2) != v2d(1, 1));
}

TEST(VEC2, DOT){
    v2d v1(1, 2);
    v2d v2(3, 4);
    EXPECT_EQ(v1.dot(v2), 11);
    EXPECT_EQ(dot(v1, v2), 11);
}

TEST(VEC2, LENGTH){
    v2d v(1, 2);
    EXPECT_EQ(v.lengthSq(), 5);
    EXPECT_EQ(v.length(), sqrt(5));
}

TEST(VEC2, DISTANCE){
    v2d v1(1, 2);
    v2d v2(3, 4);

    EXPECT_EQ(distSq(v1, v2), 8);
    EXPECT_EQ(dist(v1, v2), sqrt(8));
}

TEST(VEC2, NORMALIZE){
    v2f v(3, 4);

    EXPECT_EQ(v.getNormalize(), v2f(0.6, 0.8));
    EXPECT_EQ(v.normalize(), v2f(0.6, 0.8));
}

TEST(VEC2, PER_ELEMENT_FUNC){
    v2f v(1.3, 1.6);
    v2f vn(1.3, -1.6);

    EXPECT_TRUE(Math::floatEqual(v.frac(), v2f(0.3, 0.6)));
    EXPECT_TRUE(Math::floatEqual(Math::frac(v), v2f(0.3, 0.6)));
    EXPECT_EQ(v.round(), v2f(1, 2));
    EXPECT_EQ(Math::round(v), v2f(1, 2));
    EXPECT_EQ(v.ceil(), v2f(2, 2));
    EXPECT_EQ(Math::ceil(v), v2f(2, 2));
    EXPECT_EQ(v.floor(), v2f(1, 1));
    EXPECT_EQ(Math::floor(v), v2f(1, 1));
    EXPECT_EQ(vn.abs(), v2f(1.3, 1.6));
    EXPECT_EQ(Math::abs(vn), v2f(1.3, 1.6));

}

TEST(VEC2, STATISTICS_FUNC){
    v2f v(1, 2);
    
    EXPECT_EQ(v.sum(), 3);
    EXPECT_EQ(Math::sum(v), 3);
    EXPECT_EQ(v.mean(), 1.5);
    EXPECT_EQ(Math::mean(v), 1.5);
    EXPECT_EQ(v.var(), 0.25);
    EXPECT_EQ(Math::var(v), 0.25);
}

TEST(VEC2, IN_OUT){
    v2f v;
    std::cout << "Input vec2 : ";
    std::cin >> v;
    std::cout << v << std::endl;
}

TEST(VEC2, MIN_MAX){
    v2f v(1, 3);

    EXPECT_EQ(Math::max(v, 2.0f), v2f(2, 3));
    EXPECT_EQ(Math::max(v, v2f(2, 2)), v2f(2, 3));
    EXPECT_EQ(Math::min(v, 2.0f), v2f(1, 2));
    EXPECT_EQ(Math::min(v, v2f(2, 2)), v2f(1, 2));
}

