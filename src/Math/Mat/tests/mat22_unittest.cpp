#include <gtest/gtest.h>

#include <type_traits>

#include "../mat22.h"

using namespace LLib;

using m2d = mat22<double>;
using m2f = mat22<float>;
using m2i = mat22<int>;

TEST(MAT22, DATA){
    m2d m(1, 2, 3, 4);

    EXPECT_TRUE((std::is_same<m2d::ValueType, double>::value));

    EXPECT_EQ(m._m00, 1);
    EXPECT_EQ(m._m01, 2);
    EXPECT_EQ(m._m10, 3);
    EXPECT_EQ(m._m11, 4);
    EXPECT_EQ(m.mat[0], 1);
    EXPECT_EQ(m.mat[1], 2);
    EXPECT_EQ(m.mat[2], 3);
    EXPECT_EQ(m.mat[3], 4);
    EXPECT_EQ(m.mat2[0][0], 1);
    EXPECT_EQ(m.mat2[0][1], 2);
    EXPECT_EQ(m.mat2[1][0], 3);
    EXPECT_EQ(m.mat2[1][1], 4);
}

TEST(MAT22, DIMENSION){
    m2d m;

    EXPECT_EQ(m.Cols, 2);
    EXPECT_EQ(m.Rows, 2);
    EXPECT_EQ(m.Num, 4);
    EXPECT_TRUE(m.isSquare());
    EXPECT_EQ(m2d::Cols, 2);
    EXPECT_EQ(m2d::Rows, 2);
    EXPECT_EQ(m2d::Num, 4);
    EXPECT_TRUE(m2d::isSquare());
}

TEST(MAT22, STATIC_FUNC){
    EXPECT_EQ(m2d::zeros(), m2d(0, 0, 0, 0));
    EXPECT_EQ(m2d::identity(), m2d(1, 0, 0, 1));
    EXPECT_EQ(m2d::full(2), m2d(2, 2, 2, 2));
    EXPECT_EQ(m2d::diag(1), m2d(1, 0, 0, 1));
    EXPECT_EQ(m2d::diag(1, 2), m2d(1, 0, 0, 2));
    EXPECT_EQ(m2d::diag(vec2<int>(3)), m2d(3, 0, 0, 3));
}

TEST(MAT22, SET_FUNC){
    m2d m;
    m.setZeros();
    EXPECT_EQ(m, m2d(0, 0, 0, 0));
    m.setIdentity();
    EXPECT_EQ(m, m2d(1, 0, 0, 1));
    m.setFull(2);
    EXPECT_EQ(m, m2d(2, 2, 2, 2));
    m.setDiag(1);
    EXPECT_EQ(m, m2d(1, 0, 0, 1));
    m.setDiag(1, 2);
    EXPECT_EQ(m, m2d(1, 0, 0, 2));
    m.setDiag(vec2<int>(3));
    EXPECT_EQ(m, m2d(3, 0, 0, 3));
}

TEST(MAT22, CONSTRUCTOR){
    m2d m1;
    m2d m2(1);
    float fa[4] = {1, 2, 3, 4};
    m2d m3(fa);
    m2d m4(1, 2, 3, 4);
    m2f m5(m3.toType<int>().getData());

    EXPECT_EQ(m1, m2d(0, 0, 0, 0));
    EXPECT_EQ(m2, m2d(1, 1, 1, 1));
    EXPECT_EQ(m3, m2d(1, 2, 3, 4));
    EXPECT_EQ(m4, m2d(1, 2, 3, 4));
    EXPECT_EQ(m5, m2d(1, 2, 3, 4));
}

TEST(MAT22, ACCESS){
    m2d m(1, 2, 3, 4);

    EXPECT_EQ(m[0], 1);
    EXPECT_EQ(m[1], 2);
    EXPECT_EQ(m[2], 3);
    EXPECT_EQ(m[3], 4);
    ASSERT_DEATH(m[4], "Assert");

    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(0, 1), 2);
    EXPECT_EQ(m(1, 0), 3);
    EXPECT_EQ(m(1, 1), 4);
    ASSERT_DEATH(m(2, 0), "Assert");
    ASSERT_DEATH(m(0, 2), "Assert");

    EXPECT_EQ(m.at(0), 1);
    EXPECT_EQ(m.at(1), 2);
    EXPECT_EQ(m.at(2), 3);
    EXPECT_EQ(m.at(3), 4);
    ASSERT_DEATH(m.at(4), "Assert");

    EXPECT_EQ(m.at(0, 0), 1);
    EXPECT_EQ(m.at(0, 1), 2);
    EXPECT_EQ(m.at(1, 0), 3);
    EXPECT_EQ(m.at(1, 1), 4);
    ASSERT_DEATH(m.at(2, 0), "Assert");
    ASSERT_DEATH(m.at(0, 2), "Assert");
}

TEST(MAT22, BOOL){
    EXPECT_TRUE(m2d(1, 2, 3, 4) == m2d(1, 2, 3, 4));
    EXPECT_TRUE(m2d(1, 2, 3, 4) != m2d(1, 2, 0, 4));
}

TEST(MAT22, NEGATIVE){
    EXPECT_EQ(-m2d(1, 2, 3, 4), m2d(-1, -2, -3, -4));
}

TEST(MAT22, ADD){
    m2d m1(1, 2, 3, 4);
    m2d m2 = m1;

    m1 += 1;
    EXPECT_EQ(m1, m2d(2, 3, 4, 5));
    m2 += m1;
    EXPECT_EQ(m2, m2d(3, 5, 7, 9));
    m2d m3 = m1 + 1;
    EXPECT_EQ(m3, m2d(3, 4, 5, 6));
    m2d m4 = 1 + m1;
    EXPECT_EQ(m4, m2d(3, 4, 5, 6));
    m2d m5 = m1 + m2;
    EXPECT_EQ(m5, m2d(5, 8, 11, 14));
}

TEST(MAT22, SUB){
    m2d m1(1, 2, 3, 4);
    m2d m2(1, 1, 1, 1);

    m1 -= 1;
    EXPECT_EQ(m1, m2d(0, 1, 2, 3));
    m2 -= m1;
    EXPECT_EQ(m2, m2d(1, 0, -1, -2));
    m2d m3 = m1 - 1;
    EXPECT_EQ(m3, m2d(-1, 0, 1, 2));
    m2d m4 = 1 - m1;
    EXPECT_EQ(m4, m2d(1, 0, -1, -2));
    m2d m5 = m1 - m2;
    EXPECT_EQ(m5, m2d(-1, 1, 3, 5));
}

TEST(MAT22, MUL){
    m2d m1(1, 1, 1, 1);
    m2d m2(1, 2, 3, 4);

    m1 *= 2;
    EXPECT_EQ(m1, m2d(2, 2, 2, 2));
    m2 *= m1;
    EXPECT_EQ(m2, m2d(2, 4, 6, 8));
    m2d m3 = m1 * 2;
    EXPECT_EQ(m3, m2d(4, 4, 4, 4));
    m2d m4 = 2 * m1;
    EXPECT_EQ(m4, m2d(4, 4, 4, 4));
    m2d m5 = m1 * m2;
    EXPECT_EQ(m5, m2d(4, 8, 12, 16));

    vec2<double> v1 = m2d(1, 2, 3, 4)*vec2<double>(1, 2 );
    vec2<double> v2 = vec2<double>(1, 2)*m2d(1, 2, 3, 4);
    EXPECT_EQ(v1, vec2<double>(5, 11));
    EXPECT_EQ(v2, vec2<double>(7, 10));
    m2d m6 = matmul(m2d(1, 2, 3, 4), m2d(2, 3, 4, 5));
    EXPECT_EQ(m6, m2d(10, 13, 22, 29));
}

TEST(MAT22, DIV){
    m2d m1(1, 2, 3, 4);
    m2d m2(2, 2, 2, 2);

    m1 /= 2;
    EXPECT_EQ(m1, m2d(0.5, 1, 1.5, 2));
    m2 /= m1;
    EXPECT_EQ(m2, m2d(4, 2, 4.0/3, 1));
    m2d m3 = m1 / 2;
    EXPECT_EQ(m3, m2d(0.25, 0.5, 0.75, 1));
    m2d m4 = 3 / m1;
    EXPECT_EQ(m4, m2d(6, 3, 2, 1.5));
    m2d m5 = m1 / m2;
    EXPECT_EQ(m5, m2d(0.125, 0.5, 1.125, 2));

    ASSERT_DEATH(m1/0, "Assert");
    ASSERT_DEATH(m1/m2d(1, 2, 0, 1), "Assert");
}

TEST(MAT22, TRACE){
    m2d m(1, 2, 3, 4);
    EXPECT_EQ(m.trace(), 5);
}

TEST(MAT22, DETERMINANT){
    m2d m(1, 2, 3, 4);
    EXPECT_EQ(m.det(), -2);
}

TEST(MAT22, INVERSE){
    m2d m(1, 2, 3, 4);
    EXPECT_EQ(m.getInv(), m2d(-2, 1, 1.5, -0.5));
    EXPECT_EQ(m.inv(), m2d(-2, 1, 1.5, -0.5));
}

TEST(MAT22, TRANSPOSE){
    m2d m(1, 2, 3, 4);
    EXPECT_EQ(m.getTranspose(), m2d(1, 3, 2, 4));
    EXPECT_EQ(m.transpose(), m2d(1, 3, 2, 4));
}

TEST(MAT22, ROW_COL){
    m2d m(1, 2, 3, 4);

    EXPECT_EQ(m.row(0), vec2<double>(1, 2));
    EXPECT_EQ(m.row(1), vec2<double>(3, 4));
    EXPECT_EQ(m.col(0), vec2<double>(1, 3));
    EXPECT_EQ(m.col(1), vec2<double>(2, 4));

    ASSERT_DEATH(m.row(2), "Assert");
    ASSERT_DEATH(m.col(2), "Assert");
}

TEST(MAT22, PER_ELEMENT_FUNC){
    m2d m(1.1, 1.2, 1.6, 1.7);

    EXPECT_TRUE(Math::floatEqual(m.frac(), m2f(0.1, 0.2, 0.6, 0.7)));
    EXPECT_TRUE(Math::floatEqual(Math::frac(m), m2f(0.1, 0.2, 0.6, 0.7)));
    EXPECT_EQ(m.round(), m2d(1, 1, 2, 2));
    EXPECT_EQ(Math::round(m), m2d(1, 1, 2, 2));
    EXPECT_EQ(m.ceil(), m2d(2, 2, 2, 2));
    EXPECT_EQ(Math::ceil(m), m2d(2, 2, 2, 2));
    EXPECT_EQ(m.floor(), m2d(1, 1, 1, 1));
    EXPECT_EQ(Math::floor(m), m2d(1, 1, 1, 1));
    EXPECT_EQ((-m).abs(), m2d(1.1, 1.2, 1.6, 1.7));
    EXPECT_EQ(Math::abs(-m), m2d(1.1, 1.2, 1.6, 1.7));
}

// TEST(MAT22, IN_OUT){
//     m2d m;
//     std::cout << "Input mat22 : ";
//     std::cin >> m;
//     std::cout << m << std::endl;
// }

TEST(MAT22, MIN_MAX){
    m2d m1(1, 2, 3, 4);

    EXPECT_EQ(Math::max(m1, 2.5), m2d(2.5, 2.5, 3, 4));
    EXPECT_EQ(Math::max(m1, m2d(4, 3, 2, 1)), m2d(4, 3, 3, 4));
    EXPECT_EQ(Math::min(m1, 2.5), m2d(1, 2, 2.5, 2.5));
    EXPECT_EQ(Math::min(m1, m2d(4, 3, 2, 1)), m2d(1, 2, 2, 1));
}