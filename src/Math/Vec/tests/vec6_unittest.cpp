#include <gtest/gtest.h>

#include "../vec3.h"
#include "../vec6.h"

#include <type_traits>

using namespace LLib;

using v6d = vec6<double>;
using v6f = vec6<float>;
using v6i = vec6<int>;

TEST(VEC6, DATA){
    v6d v(1, 2, 3, 4, 5, 6);

    EXPECT_TRUE((std::is_same<v6f::ValueType, float>::value));

    EXPECT_EQ(v.Dim, 6);
    EXPECT_EQ(v6f::Dim, 6);

    EXPECT_EQ(v.array[0], 1);
    EXPECT_EQ(v.array[1], 2);
    EXPECT_EQ(v.array[2], 3);
    EXPECT_EQ(v.array[3], 4);
    EXPECT_EQ(v.array[4], 5);
    EXPECT_EQ(v.array[5], 6);
    EXPECT_EQ(v.rot_, vec3<double>(1, 2, 3));
    EXPECT_EQ(v.t_, vec3<double>(4, 5, 6));
}

TEST(VEC6, STATIC_FUNC){
    EXPECT_EQ(v6d::zeros(), v6d(0, 0, 0, 0, 0, 0));
    EXPECT_EQ(v6d::ones(), v6d(1, 1, 1, 1, 1, 1));
    EXPECT_EQ(v6d::full(2), v6d(2, 2, 2, 2, 2, 2));
}

TEST(VEC6, CONSTRUCTOR){
    v6d v1;
    v6d v2(1);
    v6i v3(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
    v6i v4(v2);
    v6i v5(v2.getData());
    v6i v6(vec3<int>(1, 2, 3), vec3<float>(4, 5, 6));
    EXPECT_EQ(v1, v6d(0, 0, 0, 0, 0, 0));
    EXPECT_EQ(v2, v6d(1, 1, 1, 1, 1, 1));
    EXPECT_EQ(v3, v6i(1, 2, 3, 4, 5, 6));
    EXPECT_EQ(v4, v6i(1, 1, 1, 1, 1, 1));
    EXPECT_EQ(v5, v6i(1, 1, 1, 1, 1, 1));
    EXPECT_EQ(v6, v6i(1, 2, 3, 4, 5, 6));
}

TEST(VEC6, CONVERT_TYPE){
    v6d v1 = v6i(1, 2, 3, 4, 5, 6).toType<double>();

    EXPECT_EQ(v1, v6d(1, 2, 3, 4, 5, 6));
}

TEST(VEC6, ACCESS){
    v6d v(1, 2, 3, 4, 5, 6);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
    EXPECT_EQ(v[4], 5);
    EXPECT_EQ(v[5], 6);
    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(1), 2);
    EXPECT_EQ(v.at(2), 3);
    EXPECT_EQ(v.at(3), 4);
    EXPECT_EQ(v.at(4), 5);
    EXPECT_EQ(v.at(5), 6);

    ASSERT_DEATH(v.at(6), "Assert");
    ASSERT_DEATH(v[6], "Assert");
}

TEST(VEC6, ASSIGN){
    v6d v = v6d(1, 2, 3, 4, 5, 6);

    EXPECT_EQ(v, v6d(1, 2, 3, 4, 5, 6));
}

TEST(VEC6, NEGATIVE){
    v6d v = -v6d(1, 2, 3, 4, 5, 6);

    EXPECT_EQ(v, v6d(-1, -2, -3, -4, -5, -6));
}

TEST(VEC6, ADD){
    v6d v1 = v6d(1, 2, 3, 2, 3, 4);
    v6d v2 = v6d(2, 3, 4, 2, 3, 4);

    v1 += 1;
    EXPECT_EQ(v1, v6d(2, 3, 4, 3, 4, 5));
    v2 += v1;
    EXPECT_EQ(v2, v6d(4, 6, 8, 5, 7, 9));
    v6d v3 = v1 + v2;
    EXPECT_EQ(v3, v6d(6, 9, 12, 8, 11, 14));
    v6d v4 = v1 + 1;
    EXPECT_EQ(v4, v6d(3, 4, 5, 4, 5, 6));
    v6d v5 = 1 + v1;
    EXPECT_EQ(v5, v6d(3, 4, 5, 4, 5, 6));
}

TEST(VEC6, SUB){
    v6d v1 = v6d(1, 2, 3, 4, 5, 6);
    v6d v2 = v6d(2, 3, 4, 5, 5, 6);

    v1 -= 1;
    EXPECT_EQ(v1, v6d(0, 1, 2, 3, 4, 5));
    v2 -= v1;
    EXPECT_EQ(v2, v6d(2, 2, 2, 2, 1, 1));
    v6d v3 = v1 - v2;
    EXPECT_EQ(v3, v6d(-2, -1, 0, 1, 3, 4));
    v6d v4 = v1 - 1;
    EXPECT_EQ(v4, v6d(-1, 0, 1, 2, 3, 4));
    v6d v5 = 1 - v1;
    EXPECT_EQ(v5, v6d(1, 0, -1, -2, -3, -4));
}

TEST(VEC6, MUL){
    v6d v1 = v6d(1, 2, 3, 2, 1, 2);
    v6d v2 = v6d(2, 3, 4, 2, 1, 2);

    v1 *= 2;
    EXPECT_EQ(v1, v6d(2, 4, 6, 4, 2, 4));
    v2 *= v1;
    EXPECT_EQ(v2, v6d(4, 12, 24, 8, 2, 8));
    v6d v3 = v1 * v2;
    EXPECT_EQ(v3, v6d(8, 48, 144, 32, 4, 32));
    v6d v4 = v1 * 2;
    EXPECT_EQ(v4, v6d(4, 8, 12, 8, 4, 8));
    v6d v5 = 2 * v1;
    EXPECT_EQ(v5, v6d(4, 8, 12, 8, 4, 8));
}

TEST(VEC6, DIV){
    v6d v1 = v6d(1, 2, 4, 8, 2, 4);
    v6d v2 = v6d(2, 4, 2, 4, 2, 4);

    v1 /= 2;
    EXPECT_EQ(v1, v6d(0.5, 1, 2, 4, 1, 2));
    v2 /= v1;
    EXPECT_EQ(v2, v6d(4, 4, 1, 1, 2, 2));
    v6d v3 = v1 / v2;
    EXPECT_EQ(v3, v6d(0.125, 0.25, 2, 4, 0.5, 1));
    v6d v4 = v1 / 2;
    EXPECT_EQ(v4, v6d(0.25, 0.5, 1, 2, 0.5, 1));
    v6d v5 = 2 / v1;
    EXPECT_EQ(v5, v6d(4, 2, 1, 0.5, 2, 1));

    ASSERT_DEATH(v1/0, "Assert");
    ASSERT_DEATH(v1/v6d(1, 0, 0, 0, 1, 1), "Assert");
}

TEST(VEC6, BOOL){
    EXPECT_TRUE(v6d(1, 2, 3, 4, 5, 6) == v6d(1, 2, 3, 4, 5, 6));
    EXPECT_TRUE(v6d(1, 2, 3, 4, 5, 6) != v6d(1, 1, 3, 4, 5, 6));
}

TEST(VEC6, DOT){
    v6d v1(1, 2, 3, 4, 5, 5);
    v6d v2(3, 4, 5, 6, 5, 5);
    EXPECT_EQ(v1.dot(v2), 100);
    EXPECT_EQ(dot(v1, v2), 100);
}

TEST(VEC6, LENGTH){
    v6d v(1, 2, 3, 4, 5, 5);
    EXPECT_EQ(v.lengthSq(), 80);
    EXPECT_EQ(v.length(), sqrt(80));
}

TEST(VEC6, DISTANCE){
    v6d v1(1, 2, 3, 4, 5, 6);
    v6d v2(3, 4, 5, 6, 4, 5);

    EXPECT_EQ(distSq(v1, v2), 18);
    EXPECT_EQ(dist(v1, v2), sqrt(18));
}

TEST(VEC6, NORMALIZE){
    v6f v(3, 4, 5, 0, 6, 0);

    EXPECT_TRUE(Math::floatEqual(v.getNormalize(), v6f(3/sqrt(86), 4/sqrt(86), 5/sqrt(86), 0, 6/sqrt(86), 0)));
    EXPECT_TRUE(Math::floatEqual(v.normalize(), v6f(3/sqrt(86), 4/sqrt(86), 5/sqrt(86), 0, 6/sqrt(86), 0)));
}

TEST(VEC6, PER_ELEMENT_FUNC){
    v6f v(1.3, 1.6, 1.5, 1.2, 1.4, 1.5);
    v6f vn(1.3, -1.6, 1.5, -1.2, -1.4, 1.5);

    EXPECT_TRUE(Math::floatEqual(v.frac(), v6f(0.3, 0.6, 0.5, 0.2, 0.4, 0.5)));
    EXPECT_TRUE(Math::floatEqual(Math::frac(v), v6f(0.3, 0.6, 0.5, 0.2, 0.4, 0.5)));
    EXPECT_EQ(v.round(), v6f(1, 2, 2, 1, 1, 2));
    EXPECT_EQ(Math::round(v), v6f(1, 2, 2, 1, 1, 2));
    EXPECT_EQ(v.ceil(), v6f(2, 2, 2, 2, 2, 2));
    EXPECT_EQ(Math::ceil(v), v6f(2, 2, 2, 2, 2, 2));
    EXPECT_EQ(v.floor(), v6f(1, 1, 1, 1, 1, 1));
    EXPECT_EQ(Math::floor(v), v6f(1, 1, 1, 1, 1, 1));
    EXPECT_EQ(vn.abs(), v6f(1.3, 1.6, 1.5, 1.2, 1.4, 1.5));
    EXPECT_EQ(Math::abs(vn), v6f(1.3, 1.6, 1.5, 1.2, 1.4, 1.5));

}

TEST(VEC6, STATISTICS_FUNC){
    v6f v(1, 2, 3, 4, 5, 9);
    
    EXPECT_EQ(v.sum(), 24);
    EXPECT_EQ(Math::sum(v), 24);
    EXPECT_EQ(v.mean(), 4);
    EXPECT_EQ(Math::mean(v), 4);
    EXPECT_EQ(v.var(), 6.666666666666667);
    EXPECT_EQ(Math::var(v), 6.666666666666667);
}

TEST(VEC6, IN_OUT){
    v6f v;
    std::cout << "Input vec6 : ";
    std::cin >> v;
    std::cout << v << std::endl;
}

TEST(VEC6, MIN_MAX){
    v6f v(1, 3, 5, 7, 8, 9);

    EXPECT_EQ(Math::max(v, 5.5f), v6f(5.5, 5.5, 5.5, 7, 8, 9));
    EXPECT_EQ(Math::max(v, v6f(2, 2, 7, 5, 4, 5)), v6f(2, 3, 7, 7, 8, 9));
    EXPECT_EQ(Math::min(v, 5.5f), v6f(1, 3, 5, 5.5, 5.5, 5.5));
    EXPECT_EQ(Math::min(v, v6f(2, 2, 1, 7, 4, 5)), v6f(1, 2, 1, 7, 4, 5));
}

TEST(VEC6, GET_SET){
    v6f v;

    v.sett(vec3<float>(1, 2, 3));
    v.setRot(vec3<float>(4, 5, 6));
    EXPECT_EQ(v.gett(), vec3<float>(1, 2, 3));
    EXPECT_EQ(v.getRot(), vec3<float>(4, 5, 6));

}

