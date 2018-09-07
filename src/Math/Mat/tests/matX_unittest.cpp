#include <gtest/gtest.h>

#include <type_traits>

#include "../matX.h"

using namespace LLib;

using m23d = matX<double, 2, 3>;
using m23f = matX<float, 2, 3>;
using m23i = matX<int, 2, 3>;

using m33d = matX<double, 3, 3>;
using m33f = matX<float, 3, 3>;
using m33i = matX<int, 3, 3>;

TEST(MATX, DATA){
    m33d m;

    EXPECT_TRUE((std::is_same<m33d::ValueType, double>::value));

    EXPECT_EQ(m.mat[0], 0);
    EXPECT_EQ(m.mat[1], 0);
    EXPECT_EQ(m.mat[2], 0);
    EXPECT_EQ(m.mat2[0][0], 0);
    EXPECT_EQ(m.mat2[0][1], 0);
    EXPECT_EQ(m.mat2[0][2], 0);
}

TEST(MATX, DIMENSION){
    m33d m1;
    m23d m2;

    EXPECT_TRUE(m1.isSquare());
    EXPECT_TRUE(m33d::isSquare());

    EXPECT_FALSE(m2.isSquare());
    EXPECT_FALSE(m23d::isSquare());
}

TEST(MATX, STATIC_FUNC){
    m33d m;
    std::cout << m << std::endl;
    std::cout << m33d::zeros() << std::endl;
    std::cout << m33d::identity() << std::endl;
    std::cout << m33d::full(2) << std::endl;
    std::cout << m33d::diag(1) << std::endl;
}

TEST(MATX, SET_FUNC){
    m33d m;
    m.setZeros();
    std::cout << m << std::endl;
    m.setIdentity();
    std::cout << m << std::endl;
    m.setFull(2);
    std::cout << m << std::endl;
    m.setDiag(1);
    std::cout << m << std::endl;

}

TEST(MATX, CONSTRUCTOR){
    m33i m1;
    m33d m2(1);
    float fa[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    m33d m3(fa);
    m33d m4(m3.toType<float>());

    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;
    std::cout << m3 << std::endl;
    std::cout << m4 << std::endl;
}

TEST(MATX, ACCESS){
    float fa[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    m33d m(fa);

    EXPECT_EQ(m[0], 1);
    EXPECT_EQ(m[1], 2);
    EXPECT_EQ(m[2], 3);
    EXPECT_EQ(m[3], 4);
    EXPECT_EQ(m[4], 5);
    EXPECT_EQ(m[5], 6);
    EXPECT_EQ(m[6], 7);
    EXPECT_EQ(m[7], 8);
    EXPECT_EQ(m[8], 9);
    ASSERT_DEATH(m[9], "Assert");

    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(0, 1), 2);
    EXPECT_EQ(m(0, 2), 3);
    EXPECT_EQ(m(1, 0), 4);
    EXPECT_EQ(m(1, 1), 5);
    EXPECT_EQ(m(1, 2), 6);
    EXPECT_EQ(m(2, 0), 7);
    EXPECT_EQ(m(2, 1), 8);
    EXPECT_EQ(m(2, 2), 9);
    ASSERT_DEATH(m(3, 0), "Assert");
    ASSERT_DEATH(m(0, 3), "Assert");

    EXPECT_EQ(m.at(0), 1);
    EXPECT_EQ(m.at(1), 2);
    EXPECT_EQ(m.at(2), 3);
    EXPECT_EQ(m.at(3), 4);
    EXPECT_EQ(m.at(4), 5);
    EXPECT_EQ(m.at(5), 6);
    EXPECT_EQ(m.at(6), 7);
    EXPECT_EQ(m.at(7), 8);
    EXPECT_EQ(m.at(8), 9);
    ASSERT_DEATH(m.at(9), "Assert");

    EXPECT_EQ(m.at(0, 0), 1);
    EXPECT_EQ(m.at(0, 1), 2);
    EXPECT_EQ(m.at(0, 2), 3);
    EXPECT_EQ(m.at(1, 0), 4);
    EXPECT_EQ(m.at(1, 1), 5);
    EXPECT_EQ(m.at(1, 2), 6);
    EXPECT_EQ(m.at(2, 0), 7);
    EXPECT_EQ(m.at(2, 1), 8);
    EXPECT_EQ(m.at(2, 2), 9);
    ASSERT_DEATH(m.at(3, 0), "Assert");
    ASSERT_DEATH(m.at(0, 3), "Assert");
}

TEST(MATX, BOOL){
    float fa1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    m33d m1(fa1);
    float fa2[9] = {1, 2, 3, 4, 5, 6, 7, 0, 9};
    m33d m2(fa2);
    EXPECT_TRUE(m1 == m1);
    EXPECT_TRUE(m1 != m2);
}

TEST(MATX, NEGATIVE){
    float fa[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    float fan[9] = {-1, -2, -3, -4, -5, -6, -7, -8, -9};
    m33d m(fa);
    EXPECT_EQ(-m33d(fa), m33d(fan));
}

TEST(MATX, ADD){
    double f1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double f2[9] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
    double f3[9] = {3, 5, 7, 9, 11, 13, 15, 17, 19};
    double f4[9] = {3, 4, 5, 6, 7, 8, 9, 10, 11};
    double f5[9] = {3, 4, 5, 6, 7, 8, 9, 10, 11};
    double f6[9] = {5, 8, 11, 14, 17, 20, 23, 26, 29};

    m33d m1(f1);
    m33d m2 = m1;

    m1 += 1;
    EXPECT_EQ(m1, m33d(f2));
    m2 += m1;
    EXPECT_EQ(m2, m33d(f3));
    m33d m3 = m1 + 1;
    EXPECT_EQ(m3, m33d(f4));
    m33d m4 = 1 + m1;
    EXPECT_EQ(m4, m33d(f5));
    m33d m5 = m1 + m2;
    EXPECT_EQ(m5, m33d(f6));
}

TEST(MATX, SUB){
    double f1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double f2[9] = {1, 1, 1, 2, 2, 2, 3, 3, 3};
    double f3[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    double f4[9] = {1, 0, -1, -1, -2, -3, -3, -4, -5};
    double f5[9] = {-1, 0, 1, 2, 3, 4, 5, 6, 7};
    double f6[9] = {8, 7, 6, 5, 4, 3, 2, 1, 0};
    double f7[9] = {-1, 1, 3, 4, 6, 8, 9, 11, 13};

    m33d m1(f1);
    m33d m2(f2);

    m1 -= 1;
    EXPECT_EQ(m1, m33d(f3));
    m2 -= m1;
    EXPECT_EQ(m2, m33d(f4));
    m33d m3 = m1 - 1;
    EXPECT_EQ(m3, m33d(f5));
    m33d m4 = 8 - m1;
    EXPECT_EQ(m4, m33d(f6));
    m33d m5 = m1 - m2;
    EXPECT_EQ(m5, m33d(f7));
}

// TEST(MATX, MUL){
//     m33d m1(1, 1, 1, 2, 2, 2, 3, 3, 3);
//     m33d m2(3, 3, 3, 2, 2, 2, 1, 1, 1);

//     m1 *= 2;
//     EXPECT_EQ(m1, m33d(2, 2, 2, 4, 4, 4, 6, 6, 6));
//     m2 *= m1;
//     EXPECT_EQ(m2, m33d(6, 6, 6, 8, 8, 8, 6, 6, 6));
//     m33d m3 = m1 * 2;
//     EXPECT_EQ(m3, m33d(4, 4, 4, 8, 8, 8, 12, 12, 12));
//     m33d m4 = 2 * m1;
//     EXPECT_EQ(m4, m33d(4, 4, 4, 8, 8, 8, 12, 12, 12));
//     m33d m5 = m1 * m2;
//     EXPECT_EQ(m5, m33d(12, 12, 12, 32, 32, 32, 36, 36, 36));

//     vec3<double> v1 = m33d(1, 1, 1, 2, 2, 2, 3, 3, 3)*vec3<double>(1, 2, 3);
//     vec3<double> v2 = vec3<double>(1, 2, 3)*m33d(1, 1, 1, 2, 2, 2, 3, 3, 3);
//     EXPECT_EQ(v1, vec3<double>(6, 12, 18));
//     EXPECT_EQ(v2, vec3<double>(14, 14, 14));
//     m33d m6 = matmul(m33d(1, 2, 3, 4, 5, 6, 7, 8, 9), m33d(2, 3, 4, 5, 6, 7, 8, 9, 10));
//     EXPECT_EQ(m6, m33d(36, 42, 48, 81, 96, 111, 126, 150, 174));
// }

TEST(MATX, DIV){
    double f1[9] = {1, 1, 1, 2, 2, 2, 4, 4, 4};
    double f2[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
    double f3[9] = {0.5, 0.5, 0.5, 1, 1, 1, 2, 2, 2};
    double f4[9] = {4, 4, 4, 2, 2, 2, 1, 1, 1};
    double f5[9] = {0.25, 0.25, 0.25, 0.5, 0.5, 0.5, 1, 1, 1};
    double f6[9] = {4, 4, 4, 2, 2, 2, 1, 1, 1};
    double f7[9] = {0.125, 0.125, 0.125, 0.5, 0.5, 0.5, 2, 2, 2};
    double f8[9] = {1, 2, 0, 1, 1, 1, 1, 1, 1};

    m33d m1(f1);
    m33d m2(f2);

    m1 /= 2;
    EXPECT_EQ(m1, m33d(f3));
    m2 /= m1;
    EXPECT_EQ(m2, m33d(f4));
    m33d m3 = m1 / 2;
    EXPECT_EQ(m3, m33d(f5));
    m33d m4 = 2 / m1;
    EXPECT_EQ(m4, m33d(f6));
    m33d m5 = m1 / m2;
    EXPECT_EQ(m5, m33d(f7));

    // ASSERT_DEATH(m1/0, "Assert");
    // ASSERT_DEATH(m1/m33d(f8), "Assert");
}

TEST(MATX, TRACE){
    double f[9] = {1, 1, 1, 2, 2, 2, 3, 3, 4};
    m33d m(f);
    EXPECT_EQ(m.trace(), 7);
}

TEST(MATX, DETERMINANT){
    m33d m;
    ASSERT_DEATH(m.det(), "Assert");
}

TEST(MATX, INVERSE){
    m33d m;
    ASSERT_DEATH(m.getInv(), "Assert");
    ASSERT_DEATH(m.inv(), "Assert");
}

// TEST(MATX, TRANSPOSE){
//     double f1[9] = {1, 1, 1, 2, 2, 2, 3, 3, 3};
//     double f2[9] = {1, 2, 3, 1, 2, 3, 1, 2, 3};

//     m33d m(f1);

//     EXPECT_EQ(m.getTranspose(), m33d(f2));
//     EXPECT_EQ(m.transpose(), m33d(f2));
// }

TEST(MATX, ROW_COL){
    double f1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double f2[3] = {1, 2, 3};
    double f3[3] = {4, 5, 6};
    double f4[3] = {7, 8, 9};
    double f5[3] = {1, 4, 7};
    double f6[3] = {2, 5, 8};
    double f7[3] = {3, 6, 9};

    m33d m(f1);

    EXPECT_EQ(m.row(0), (vecX<double,3>(f2)));
    EXPECT_EQ(m.row(1), (vecX<double,3>(f3)));
    EXPECT_EQ(m.row(2), (vecX<double,3>(f4)));
    EXPECT_EQ(m.col(0), (vecX<double,3>(f5)));
    EXPECT_EQ(m.col(1), (vecX<double,3>(f6)));
    EXPECT_EQ(m.col(2), (vecX<double,3>(f7)));

    ASSERT_DEATH(m.row(3), "Assert");
    ASSERT_DEATH(m.col(3), "Assert");
}

TEST(MATX, PER_ELEMENT_FUNC){
    double f1[9] = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9};
    double f2[9] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    double f3[9] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    double f4[9] = {1, 1, 1, 1, 2, 2, 2, 2, 2};
    double f5[9] = {1, 1, 1, 1, 2, 2, 2, 2, 2};
    double f6[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
    double f7[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
    double f8[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    double f9[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    double f10[9] = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9};
    double f11[9] = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9};
        

    m33d m(f1);

    EXPECT_TRUE(Math::floatEqual(m.frac(), m33f(f2)));
    EXPECT_TRUE(Math::floatEqual(Math::frac(m), m33f(f3)));
    EXPECT_EQ(m.round(), m33d(f4));
    EXPECT_EQ(Math::round(m), m33d(f5));
    EXPECT_EQ(m.ceil(), m33d(f6));
    EXPECT_EQ(Math::ceil(m), m33d(f7));
    EXPECT_EQ(m.floor(), m33d(f8));
    EXPECT_EQ(Math::floor(m), m33d(f9));
    EXPECT_EQ((-m).abs(), m33d(f10));
    EXPECT_EQ(Math::abs(-m), m33d(f11));
}

TEST(MATX, IN_OUT){
    m33d m;
    // std::cout << "Input mat33 : ";
    // std::cin >> m;
    std::cout << m << std::endl;
}

TEST(MATX, MIN_MAX){
    double f1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double f2[9] = {6, 6, 6, 6, 6, 6, 7, 8, 9};
    double f3[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    double f4[9] = {9, 8, 7, 6, 5, 6, 7, 8, 9};
    double f5[9] = {1, 2, 3, 4, 5, 6, 6, 6, 6};
    double f6[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    double f7[9] = {1, 2, 3, 4, 5, 4, 3, 2, 1};

    m33d m1(f1);

    EXPECT_EQ(Math::max(m1, 6.0), m33d(f2));
    EXPECT_EQ(Math::max(m1, m33d(f3)), m33d(f4));
    EXPECT_EQ(Math::min(m1, 6.0), m33d(f5));
    EXPECT_EQ(Math::min(m1, m33d(f6)), m33d(f7));
}