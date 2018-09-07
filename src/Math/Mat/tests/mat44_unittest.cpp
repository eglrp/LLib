#include <gtest/gtest.h>

#include <type_traits>

#include "../mat44.h"

using namespace LLib;

using m4d = mat44<double>;
using m4f = mat44<float>;
using m4i = mat44<int>;

TEST(MAT44, DATA){
    m4d m(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

    EXPECT_TRUE((std::is_same<m4d::ValueType, double>::value));

    EXPECT_EQ(m._m00, 1);
    EXPECT_EQ(m._m01, 2);
    EXPECT_EQ(m._m02, 3);
    EXPECT_EQ(m.mat[0], 1);
    EXPECT_EQ(m.mat[1], 2);
    EXPECT_EQ(m.mat[2], 3);
    EXPECT_EQ(m.mat2[0][0], 1);
    EXPECT_EQ(m.mat2[0][1], 2);
    EXPECT_EQ(m.mat2[0][2], 3);

}

TEST(MAT44, DIMENSION){
    m4d m;

    EXPECT_EQ(m.Cols, 4);
    EXPECT_EQ(m.Rows, 4);
    EXPECT_EQ(m.Num, 16);
    EXPECT_TRUE(m.isSquare());
    EXPECT_EQ(m4d::Cols, 4);
    EXPECT_EQ(m4d::Rows, 4);
    EXPECT_EQ(m4d::Num, 16);
    EXPECT_TRUE(m4d::isSquare());
}

TEST(MAT44, STATIC_FUNC){
    EXPECT_EQ(m4d::zeros(), m4d(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
    EXPECT_EQ(m4d::identity(), m4d(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
    EXPECT_EQ(m4d::full(2), m4d(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2));
    EXPECT_EQ(m4d::diag(1), m4d(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
    EXPECT_EQ(m4d::diag(1, 2, 3, 4), m4d(1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4));
    EXPECT_EQ(m4d::diag(vec4<int>(3)), m4d(3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3));
}

TEST(MAT44, SET_FUNC){
    m4d m;
    m.setZeros();
    EXPECT_EQ(m, m4d(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
    m.setIdentity();
    EXPECT_EQ(m, m4d(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
    m.setFull(2);
    EXPECT_EQ(m, m4d(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2));
    m.setDiag(1);
    EXPECT_EQ(m, m4d(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
    m.setDiag(1, 2, 3, 4);
    EXPECT_EQ(m, m4d(1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4));
    m.setDiag(vec4<int>(3));
    EXPECT_EQ(m, m4d(3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3));
}

TEST(MAT44, CONSTRUCTOR){
    m4d m1;
    m4d m2(1);
    float fa[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    m4d m3(fa);
    m4d m4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    m4f m5(m3.toType<int>().getData());

    EXPECT_EQ(m1, m4d(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
    EXPECT_EQ(m2, m4d(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1));
    EXPECT_EQ(m3, m4d(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
    EXPECT_EQ(m4, m4d(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
    EXPECT_EQ(m5, m4d(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
}

TEST(MAT44, ACCESS){
    m4d m(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

    EXPECT_EQ(m[0], 1);
    EXPECT_EQ(m[1], 2);
    EXPECT_EQ(m[2], 3);
    ASSERT_DEATH(m[16], "Assert");

    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(0, 1), 2);
    EXPECT_EQ(m(0, 2), 3);
    ASSERT_DEATH(m(4, 0), "Assert");
    ASSERT_DEATH(m(0, 4), "Assert");

    EXPECT_EQ(m.at(0), 1);
    EXPECT_EQ(m.at(1), 2);
    EXPECT_EQ(m.at(2), 3);
    ASSERT_DEATH(m.at(16), "Assert");

    EXPECT_EQ(m.at(0, 0), 1);
    EXPECT_EQ(m.at(0, 1), 2);
    EXPECT_EQ(m.at(0, 2), 3);
    ASSERT_DEATH(m.at(4, 0), "Assert");
    ASSERT_DEATH(m.at(0, 4), "Assert");
}

TEST(MAT44, BOOL){
    EXPECT_TRUE(m4d(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16) == m4d(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
    EXPECT_TRUE(m4d(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16) != m4d(1, 2, 3, 4, 5, 0, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
}

TEST(MAT44, NEGATIVE){
    EXPECT_EQ(-m4d(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16), m4d(-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16));
}

TEST(MAT44, ADD){
    m4d m1(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4);
    m4d m2 = m1;

    m1 += 1;
    EXPECT_EQ(m1, m4d(2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5));
    m2 += m1;
    EXPECT_EQ(m2, m4d(3, 3, 3, 3, 5, 5, 5, 5, 7, 7, 7, 7, 9, 9, 9, 9));
    m4d m3 = m1 + 1;
    EXPECT_EQ(m3, m4d(3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6));
    m4d m4 = 1 + m1;
    EXPECT_EQ(m4, m4d(3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6));
    m4d m5 = m1 + m2;
    EXPECT_EQ(m5, m4d(5, 5, 5, 5, 8, 8, 8, 8, 11, 11, 11, 11, 14, 14, 14, 14));
}

TEST(MAT44, SUB){
    m4d m1(2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5);
    m4d m2(1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2);

    m1 -= 1;
    EXPECT_EQ(m1, m4d(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4));
    m2 -= m1;
    EXPECT_EQ(m2, m4d(0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2, -2, -2));
    m4d m3 = m1 - 1;
    EXPECT_EQ(m3, m4d(0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3));
    m4d m4 =  4 - m1;
    EXPECT_EQ(m4, m4d(3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0));
    m4d m5 = m1 - m2;
    EXPECT_EQ(m5, m4d(1, 1, 1, 1, 3, 3, 3, 3, 4, 4, 4, 4, 6, 6, 6, 6));
}

TEST(MAT44, MUL){
    m4d m1(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4);
    m4d m2(4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1);

    m1 *= 2;
    EXPECT_EQ(m1, m4d(2, 2, 2, 2, 4, 4, 4, 4, 6, 6, 6, 6, 8, 8, 8, 8));
    m2 *= m1;
    EXPECT_EQ(m2, m4d(8, 8, 8, 8, 12, 12, 12, 12, 12, 12, 12, 12, 8, 8, 8, 8));
    m4d m3 = m1 * 2;
    EXPECT_EQ(m3, m4d(4, 4, 4, 4, 8, 8, 8, 8, 12, 12, 12, 12, 16, 16, 16, 16));
    m4d m4 = 2 * m1;
    EXPECT_EQ(m4, m4d(4, 4, 4, 4, 8, 8, 8, 8, 12, 12, 12, 12, 16, 16, 16, 16));
    m4d m5 = m1 * m2;
    EXPECT_EQ(m5, m4d(16, 16, 16, 16, 48, 48, 48, 48, 72, 72, 72, 72, 64, 64, 64, 64));

    vec4<double> v1 = m4d(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4)*vec4<double>(1, 2, 3, 4);
    vec4<double> v2 = vec4<double>(1, 2, 3, 4)*m4d(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4);
    EXPECT_EQ(v1, vec4<double>(10, 20, 30, 40));
    EXPECT_EQ(v2, vec4<double>(30, 30, 30, 30));
    m4d m6 = matmul(m4d(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4), m4d(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4));
    EXPECT_EQ(m6, m4d(10, 10, 10, 10, 20, 20, 20, 20, 30, 30, 30, 30, 40, 40, 40, 40));
}

TEST(MAT44, DIV){
    m4d m1(1, 1, 1, 1, 2, 2, 2, 2, 4, 4, 4, 4, 8, 8, 8, 8);
    m4d m2(1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2);

    m1 /= 2;
    EXPECT_EQ(m1, m4d(0.5, 0.5, 0.5, 0.5, 1, 1, 1, 1, 2, 2, 2, 2, 4, 4, 4, 4));
    m2 /= m1;
    EXPECT_EQ(m2, m4d(2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0.5, 0.5, 0.5, 0.5));
    m4d m3 = m1 / 2;
    EXPECT_EQ(m3, m4d(0.25, 0.25, 0.25, 0.25, 0.5, 0.5, 0.5, 0.5, 1, 1, 1, 1, 2, 2, 2, 2));
    m4d m4 = 2 / m1;
    EXPECT_EQ(m4, m4d(4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 0.5, 0.5, 0.5, 0.5));
    m4d m5 = m1 / m2;
    EXPECT_EQ(m5, m4d(0.25, 0.25, 0.25, 0.25, 1, 1, 1, 1, 2, 2, 2, 2, 8, 8, 8, 8));

    ASSERT_DEATH(m1/0, "Assert");
    ASSERT_DEATH(m1/m4d(0.5, 0.5, 0, 0.5, 1, 1, 1, 1, 2, 2, 2, 2, 4, 4, 4, 40), "Assert");
}

TEST(MAT44, TRACE){
    m4d m(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4);
    EXPECT_EQ(m.trace(), 10);
}

TEST(MAT44, DETERMINANT){
    m4d m(1, 3, 2, 5, 3, 1, 5, 2, 4, 6, 6, 3, 2, 5, 7, 4);
    EXPECT_EQ(m.det(), -225);
}

TEST(MAT44, INVERSE){
    m4d m(1, 2, 0, 2, 0, 1, 2, 0, 0, 0, 1, 0, 0, 0, 2, 1);
    EXPECT_EQ(m.getInv(), m4d(1, -2, 8, -2, 0, 1, -2, 0, 0, 0, 1, 0, 0, 0, -2, 1));
    EXPECT_EQ(m.inv(), m4d(1, -2, 8, -2, 0, 1, -2, 0, 0, 0, 1, 0, 0, 0, -2, 1));
}

TEST(MAT44, TRANSPOSE){
    m4d m(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    EXPECT_EQ(m.getTranspose(), m4d(1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16));
    EXPECT_EQ(m.transpose(), m4d(1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16));
}

TEST(MAT44, ROW_COL){
    m4d m(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4);

    EXPECT_EQ(m.row(0), vec4<double>(1, 1, 1, 1));
    EXPECT_EQ(m.row(1), vec4<double>(2, 2, 2, 2));
    EXPECT_EQ(m.row(2), vec4<double>(3, 3, 3, 3));
    EXPECT_EQ(m.col(0), vec4<double>(1, 2, 3, 4));
    EXPECT_EQ(m.col(1), vec4<double>(1, 2, 3, 4));
    EXPECT_EQ(m.col(2), vec4<double>(1, 2, 3, 4));

    ASSERT_DEATH(m.row(4), "Assert");
    ASSERT_DEATH(m.col(4), "Assert");
}

TEST(MAT44, PER_ELEMENT_FUNC){
    m4d m(1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8);

    EXPECT_TRUE(Math::floatEqual(m.frac(), m4f(0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8)));
    EXPECT_TRUE(Math::floatEqual(Math::frac(m), m4f(0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8)));
    EXPECT_EQ(m.round(), m4d(1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2));
    EXPECT_EQ(Math::round(m), m4d(1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2));
    EXPECT_EQ(m.ceil(), m4d(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2));
    EXPECT_EQ(Math::ceil(m), m4d(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2));
    EXPECT_EQ(m.floor(), m4d(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1));
    EXPECT_EQ(Math::floor(m), m4d(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1));
    EXPECT_EQ((-m).abs(), m4d(1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8));
    EXPECT_EQ(Math::abs(-m), m4d(1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8));
}

// TEST(MAT44, IN_OUT){
//     m4d m;
//     std::cout << "Input mat44 : ";
//     std::cin >> m;
//     std::cout << m << std::endl;
// }

TEST(MAT44, MIN_MAX){
    m4d m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

    EXPECT_EQ(Math::max(m1, 9.0), m4d(9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 11, 12, 13, 14, 15, 16));
    EXPECT_EQ(Math::max(m1, m4d(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)), m4d(16, 15, 14, 13, 12, 11, 10, 9, 9, 10, 11, 12, 13, 14, 15, 16));
    EXPECT_EQ(Math::min(m1, 9.0), m4d(1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9));
    EXPECT_EQ(Math::min(m1, m4d(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)), m4d(1, 2, 3, 4, 5, 6 ,7, 8, 8, 7, 6, 5, 4, 3, 2, 1));
}