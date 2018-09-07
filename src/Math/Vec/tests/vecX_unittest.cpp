#include <gtest/gtest.h>

#include "../vecX.h"

#include <type_traits>

using namespace LLib;

using v7d = vecX<double, 7>;
using v7f = vecX<float, 7>;
using v7i = vecX<int, 7>;

TEST(VECX, DATA){
    double fd[7] = {1, 2, 3, 4, 5, 6, 7};
    v7d v(fd);

    EXPECT_TRUE((std::is_same<v7f::ValueType, float>::value));

    EXPECT_EQ(v.Dim, 7);
    EXPECT_EQ(v7f::Dim, 7);

    EXPECT_EQ(v.array[0], 1);
    EXPECT_EQ(v.array[1], 2);
    EXPECT_EQ(v.array[2], 3);
    EXPECT_EQ(v.array[3], 4);
    EXPECT_EQ(v.array[4], 5);
    EXPECT_EQ(v.array[5], 6);
    EXPECT_EQ(v.array[6], 7);
}

TEST(VECX, STATIC_FUNC){
    double fd[7] = {1, 1, 1, 1, 1, 1, 1};
    EXPECT_EQ(v7d::zeros(), 0*v7d(fd));
    EXPECT_EQ(v7d::ones(), v7d(fd));
    EXPECT_EQ(v7d::full(2), 2*v7d(fd));
}

TEST(VECX, CONSTRUCTOR){
    double fd[7] = {1, 1, 1, 1, 1, 1, 1};
    double fi[7] = {1, 1, 1, 1, 1, 1, 1};
    v7d v1;
    v7d v2(1);
    float ff[7] = {1, 2, 3, 4, 5, 6, 7};
    v7i v3(ff);
    v7i v4(v2);
    v7i v5(v2.getData());
    EXPECT_EQ(v1, 0*v7d(fd));
    EXPECT_EQ(v2, v7d(fd));
    EXPECT_EQ(v3, v7i(ff));
    EXPECT_EQ(v4, v7i(fi));
    EXPECT_EQ(v5, v7i(fi));
}

TEST(VECX, CONVERT_TYPE){
    double fi[7] = {1, 1, 1, 1, 1, 1, 1};
    v7d v1 = v7i(fi).toType<double>();

    EXPECT_EQ(v1, v7d(fi));
}

TEST(VECX, ACCESS){
    float ff[7] = {1, 2, 3, 4, 5, 6, 7};
    v7d v(ff);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
    EXPECT_EQ(v[4], 5);
    EXPECT_EQ(v[5], 6);
    EXPECT_EQ(v[6], 7);
    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(1), 2);
    EXPECT_EQ(v.at(2), 3);
    EXPECT_EQ(v.at(3), 4);
    EXPECT_EQ(v.at(4), 5);
    EXPECT_EQ(v.at(5), 6);
    EXPECT_EQ(v.at(6), 7);

    ASSERT_DEATH(v.at(7), "Assert");
    ASSERT_DEATH(v[7], "Assert");
}

TEST(VECX, ASSIGN){
    float ff[7] = {1, 2, 3, 4, 5, 6, 7};
    v7d v = v7d(ff);

    EXPECT_EQ(v, v7d(ff));
}

TEST(VECX, NEGATIVE){
    float ff[7] = {1, 2, 3, 4, 5, 6, 7};
    float ffn[7] = {-1, -2, -3, -4, -5, -6, -7};
    v7d v = -v7d(ff);

    EXPECT_EQ(v, v7d(ffn));
}

TEST(VECX, ADD){
    double fd[7] = {1, 1, 1, 1, 1, 1, 1};
    v7d v1 = v7d(fd);
    v7d v2 = 2*v7d(fd);

    v1 += 1;
    EXPECT_EQ(v1, 2*v7d(fd));
    v2 += v1;
    EXPECT_EQ(v2, 4*v7d(fd));
    v7d v3 = v1 + v2;
    EXPECT_EQ(v3, 6*v7d(fd));
    v7d v4 = v1 + 1;
    EXPECT_EQ(v4, 3*v7d(fd));
    v7d v5 = 1 + v1;
    EXPECT_EQ(v5, 3*v7d(fd));
}

TEST(VECX, SUB){
    double fd[7] = {1, 1, 1, 1, 1, 1, 1};
    v7d v1 = v7d(fd);
    v7d v2 = 2*v7d(fd);

    v1 -= 1;
    EXPECT_EQ(v1, 0*v7d(fd));
    v2 -= v1;
    EXPECT_EQ(v2, 2*v7d(fd));
    v7d v3 = v1 - v2;
    EXPECT_EQ(v3, -2*v7d(fd));
    v7d v4 = v1 - 1;
    EXPECT_EQ(v4, -v7d(fd));
    v7d v5 = 1 - v1;
    EXPECT_EQ(v5, v7d(fd));
}

TEST(VECX, MUL){
    double fd[7] = {1, 1, 1, 1, 1, 1, 1};
    v7d v1 = v7d(fd);
    v7d v2 = 2*v7d(fd);

    v1 *= 2;
    EXPECT_EQ(v1, 2*v7d(fd));
    v2 *= v1;
    EXPECT_EQ(v2, 4*v7d(fd));
    v7d v3 = v1 * v2;
    EXPECT_EQ(v3, 8*v7d(fd));
    v7d v4 = v1 * 2;
    EXPECT_EQ(v4, 4*v7d(fd));
    v7d v5 = 2 * v1;
    EXPECT_EQ(v5, 4*v7d(fd));
}

TEST(VECX, DIV){
    double fd[7] = {1, 1, 1, 1, 1, 1, 1};
    double fd0[7] = {1, 1, 0, 1, 1, 1, 1};
    v7d v1 = v7d(fd);
    v7d v2 = 2*v7d(fd);

    v1 /= 2;
    EXPECT_EQ(v1, 0.5*v7d(fd));
    v2 /= v1;
    EXPECT_EQ(v2, 4*v7d(fd));
    v7d v3 = v1 / v2;
    EXPECT_EQ(v3, 0.125*v7d(fd));
    v7d v4 = v1 / 2;
    EXPECT_EQ(v4, 0.25*v7d(fd));
    v7d v5 = 2 / v1;
    EXPECT_EQ(v5, 4*v7d(fd));

    // ASSERT_DEATH(v1/0, "Assert");
    // ASSERT_DEATH(v1/v7d(fd0), "Assert");
}

TEST(VECX, BOOL){
    double fd[7] = {1, 1, 1, 1, 1, 1, 1};
    double fd0[7] = {1, 1, 0, 1, 1, 1, 1};
    EXPECT_TRUE(v7d(fd) == v7d(fd));
    EXPECT_TRUE(v7d(fd) != v7d(fd0));
}

TEST(VECX, DOT){
    double fd[7] = {1, 1, 1, 1, 1, 1, 1};
    v7d v1(fd);

    EXPECT_EQ(v1.dot(2*v1), 14);
    EXPECT_EQ(dot(v1, 2*v1), 14);
}

TEST(VECX, LENGTH){
    double fd[7] = {1, 1, 1, 1, 1, 1, 1};
    v7d v(fd);
    EXPECT_EQ(v.lengthSq(), 7);
    EXPECT_EQ(v.length(), sqrt(7));
}

TEST(VECX, DISTANCE){
    double fd[7] = {1, 1, 1, 1, 1, 1, 1};
    v7d v1(fd);

    EXPECT_EQ(distSq(v1, 2*v1), 7);
    EXPECT_EQ(dist(v1, 2*v1), sqrt(7));
}

TEST(VECX, NORMALIZE){
    double fd[7] = {1, 1, 1, 1, 1, 1, 1};
    v7d v1(fd);

    EXPECT_TRUE(Math::floatEqual(v1.getNormalize(), 1/sqrt(7) * v7d(fd)));
    EXPECT_TRUE(Math::floatEqual(v1.normalize(), 1/sqrt(7) * v7d(fd)));
}

TEST(VECX, PER_ELEMENT_FUNC){
    float ff1[7] = {1.3, 1.6, 1.5, 1.2, 1.4, 1.5, 1.4};
    float ff2[7] = {0.3, 0.6, 0.5, 0.2, 0.4, 0.5, 0.4};
    float ff3[7] = {1, 1, 1, 1, 1, 1, 1};
    float ff4[7] = {2, 2, 2, 2, 2, 2, 2};
    float ff5[7] = {1, 2, 2, 1, 1, 2, 1};
    v7f v(ff1);

    EXPECT_TRUE(Math::floatEqual(v.frac(), v7f(ff2)));
    EXPECT_TRUE(Math::floatEqual(Math::frac(v), v7f(ff2)));
    EXPECT_EQ(v.round(), v7f(ff5));
    EXPECT_EQ(Math::round(v), v7f(ff5));
    EXPECT_EQ(v.ceil(), v7f(ff4));
    EXPECT_EQ(Math::ceil(v), v7f(ff4));
    EXPECT_EQ(v.floor(), v7f(ff3));
    EXPECT_EQ(Math::floor(v), v7f(ff3));
    EXPECT_EQ((-v).abs(), v7f(ff1));
    EXPECT_EQ(Math::abs(-v), v7f(ff1));

}

TEST(VECX, STATISTICS_FUNC){
    double fd[7] = {1, 1, 1, 2, 2, 2, 1};
    v7d v1(fd);
    
    EXPECT_EQ(v1.sum(), 10);
    EXPECT_EQ(Math::sum(v1), 10);
    EXPECT_EQ(v1.mean(), 1.4285714285714286);
    EXPECT_EQ(Math::mean(v1), 1.4285714285714286);
    EXPECT_EQ(v1.var(), 0.24489795918367346);
    EXPECT_EQ(Math::var(v1), 0.24489795918367346);
}

TEST(VECX, IN_OUT){
    // std::cout << "Input vec4 : ";
    // std::cin >> v;

    double fd[7] = {1, 1, 1, 2, 2, 2, 1};
    v7d v(fd);
    std::cout << v << std::endl;
}

TEST(VECX, MIN_MAX){
    float ff[7] = {1, 1, 1, 2, 2, 2, 1};
    float ff2[7] = {1, 1, 1, 1, 1, 1, 1};
    float ff3[7] = {1.5, 1.5, 1.5, 2, 2, 2, 1.5};
    float ff4[7] = {1, 1, 1, 1.5, 1.5, 1.5, 1};
    v7f v1(ff);

    EXPECT_EQ(Math::max(v1, 1.5f), v7f(ff3));
    EXPECT_EQ(Math::max(v1, v7f(ff2)), v7f(ff));
    EXPECT_EQ(Math::min(v1, 1.5f), v7f(ff4));
    EXPECT_EQ(Math::min(v1, v7f(ff2)), v7f(ff2));
}

// TEST(VECX, GET_SET){
//     v7f v;

//     v.sett(vec3<float>(1, 2, 3));
//     v.setRot(vec3<float>(4, 5, 6));
//     EXPECT_EQ(v.gett(), vec3<float>(1, 2, 3));
//     EXPECT_EQ(v.getRot(), vec3<float>(4, 5, 6));

// }

