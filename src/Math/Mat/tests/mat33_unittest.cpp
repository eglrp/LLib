#include <gtest/gtest.h>

#include <type_traits>

#include "../mat33.h"

using namespace LLib;

using m3d = mat33<double>;
using m3f = mat33<float>;
using m3i = mat33<int>;

TEST(MAT33, DATA){
    m3d m(1, 2, 3, 4, 5, 6, 7, 8, 9);

    EXPECT_TRUE((std::is_same<m3d::ValueType, double>::value));

    EXPECT_EQ(m._m00, 1);
    EXPECT_EQ(m._m01, 2);
    EXPECT_EQ(m._m02, 3);
    EXPECT_EQ(m._m10, 4);
    EXPECT_EQ(m._m11, 5);
    EXPECT_EQ(m._m12, 6);
    EXPECT_EQ(m._m20, 7);
    EXPECT_EQ(m._m21, 8);
    EXPECT_EQ(m._m22, 9);
    EXPECT_EQ(m.mat[0], 1);
    EXPECT_EQ(m.mat[1], 2);
    EXPECT_EQ(m.mat[2], 3);
    EXPECT_EQ(m.mat[3], 4);
    EXPECT_EQ(m.mat[4], 5);
    EXPECT_EQ(m.mat[5], 6);
    EXPECT_EQ(m.mat[6], 7);
    EXPECT_EQ(m.mat[7], 8);
    EXPECT_EQ(m.mat[8], 9);
    EXPECT_EQ(m.mat2[0][0], 1);
    EXPECT_EQ(m.mat2[0][1], 2);
    EXPECT_EQ(m.mat2[0][2], 3);
    EXPECT_EQ(m.mat2[1][0], 4);
    EXPECT_EQ(m.mat2[1][1], 5);
    EXPECT_EQ(m.mat2[1][2], 6);
    EXPECT_EQ(m.mat2[2][0], 7);
    EXPECT_EQ(m.mat2[2][1], 8);
    EXPECT_EQ(m.mat2[2][2], 9);
}

TEST(MAT33, DIMENSION){
    m3d m;

    EXPECT_EQ(m.Cols, 3);
    EXPECT_EQ(m.Rows, 3);
    EXPECT_EQ(m.Num, 9);
    EXPECT_TRUE(m.isSquare());
    EXPECT_EQ(m3d::Cols, 3);
    EXPECT_EQ(m3d::Rows, 3);
    EXPECT_EQ(m3d::Num, 9);
    EXPECT_TRUE(m3d::isSquare());
}

TEST(MAT33, STATIC_FUNC){
    EXPECT_EQ(m3d::zeros(), m3d(0, 0, 0, 0, 0, 0, 0, 0, 0));
    EXPECT_EQ(m3d::identity(), m3d(1, 0, 0, 0, 1, 0, 0, 0, 1));
    EXPECT_EQ(m3d::full(2), m3d(2, 2, 2, 2, 2, 2, 2, 2, 2));
    EXPECT_EQ(m3d::diag(1), m3d(1, 0, 0, 0, 1, 0, 0, 0, 1));
    EXPECT_EQ(m3d::diag(1, 2, 3), m3d(1, 0, 0, 0, 2, 0, 0, 0, 3));
    EXPECT_EQ(m3d::diag(vec3<int>(3)), m3d(3, 0, 0, 0, 3, 0, 0, 0, 3));
}

TEST(MAT33, SET_FUNC){
    m3d m;
    m.setZeros();
    EXPECT_EQ(m, m3d(0, 0, 0, 0, 0, 0, 0, 0, 0));
    m.setIdentity();
    EXPECT_EQ(m, m3d(1, 0, 0, 0, 1, 0, 0, 0, 1));
    m.setFull(2);
    EXPECT_EQ(m, m3d(2, 2, 2, 2, 2, 2, 2, 2, 2));
    m.setDiag(1);
    EXPECT_EQ(m, m3d(1, 0, 0, 0, 1, 0, 0, 0, 1));
    m.setDiag(1, 2, 3);
    EXPECT_EQ(m, m3d(1, 0, 0, 0, 2, 0, 0, 0, 3));
    m.setDiag(vec3<int>(3));
    EXPECT_EQ(m, m3d(3, 0, 0, 0, 3, 0, 0, 0, 3));
}

TEST(MAT33, CONSTRUCTOR){
    m3d m1;
    m3d m2(1);
    float fa[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    m3d m3(fa);
    m3d m4(1, 2, 3, 4, 5, 6, 7, 8, 9);
    m3f m5(m3.toType<int>().getData());

    EXPECT_EQ(m1, m3d(0, 0, 0, 0, 0, 0, 0, 0, 0));
    EXPECT_EQ(m2, m3d(1, 1, 1, 1, 1, 1, 1, 1, 1));
    EXPECT_EQ(m3, m3d(1, 2, 3, 4, 5, 6, 7, 8, 9));
    EXPECT_EQ(m4, m3d(1, 2, 3, 4, 5, 6, 7, 8, 9));
    EXPECT_EQ(m5, m3d(1, 2, 3, 4, 5, 6, 7, 8, 9));
}

TEST(MAT33, ACCESS){
    m3d m(1, 2, 3, 4, 5, 6, 7, 8, 9);

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

TEST(MAT33, BOOL){
    EXPECT_TRUE(m3d(1, 2, 3, 4, 5, 6, 7, 8, 9) == m3d(1, 2, 3, 4, 5, 6, 7, 8, 9));
    EXPECT_TRUE(m3d(1, 2, 3, 4, 5, 6, 7, 8, 9) != m3d(1, 2, 0, 4, 5, 6, 7, 8, 9));
}

TEST(MAT33, NEGATIVE){
    EXPECT_EQ(-m3d(1, 2, 3, 4, 5, 6, 7, 8, 9), m3d(-1, -2, -3, -4, -5, -6, -7, -8, -9));
}

TEST(MAT33, ADD){
    m3d m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
    m3d m2 = m1;

    m1 += 1;
    EXPECT_EQ(m1, m3d(2, 3, 4, 5, 6, 7, 8, 9, 10));
    m2 += m1;
    EXPECT_EQ(m2, m3d(3, 5, 7, 9, 11, 13, 15, 17, 19));
    m3d m3 = m1 + 1;
    EXPECT_EQ(m3, m3d(3, 4, 5, 6, 7, 8, 9, 10, 11));
    m3d m4 = 1 + m1;
    EXPECT_EQ(m4, m3d(3, 4, 5, 6, 7, 8, 9, 10, 11));
    m3d m5 = m1 + m2;
    EXPECT_EQ(m5, m3d(5, 8, 11, 14, 17, 20, 23, 26, 29));
}

TEST(MAT33, SUB){
    m3d m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
    m3d m2(1, 1, 1, 2, 2, 2, 3, 3, 3);

    m1 -= 1;
    EXPECT_EQ(m1, m3d(0, 1, 2, 3, 4, 5, 6, 7, 8));
    m2 -= m1;
    EXPECT_EQ(m2, m3d(1, 0, -1, -1, -2, -3, -3, -4, -5));
    m3d m3 = m1 - 1;
    EXPECT_EQ(m3, m3d(-1, 0, 1, 2, 3, 4, 5, 6, 7));
    m3d m4 = 8 - m1;
    EXPECT_EQ(m4, m3d(8, 7, 6, 5, 4, 3, 2, 1, 0));
    m3d m5 = m1 - m2;
    EXPECT_EQ(m5, m3d(-1, 1, 3, 4, 6, 8, 9, 11, 13));
}

TEST(MAT33, MUL){
    m3d m1(1, 1, 1, 2, 2, 2, 3, 3, 3);
    m3d m2(3, 3, 3, 2, 2, 2, 1, 1, 1);

    m1 *= 2;
    EXPECT_EQ(m1, m3d(2, 2, 2, 4, 4, 4, 6, 6, 6));
    m2 *= m1;
    EXPECT_EQ(m2, m3d(6, 6, 6, 8, 8, 8, 6, 6, 6));
    m3d m3 = m1 * 2;
    EXPECT_EQ(m3, m3d(4, 4, 4, 8, 8, 8, 12, 12, 12));
    m3d m4 = 2 * m1;
    EXPECT_EQ(m4, m3d(4, 4, 4, 8, 8, 8, 12, 12, 12));
    m3d m5 = m1 * m2;
    EXPECT_EQ(m5, m3d(12, 12, 12, 32, 32, 32, 36, 36, 36));

    vec3<double> v1 = m3d(1, 1, 1, 2, 2, 2, 3, 3, 3)*vec3<double>(1, 2, 3);
    vec3<double> v2 = vec3<double>(1, 2, 3)*m3d(1, 1, 1, 2, 2, 2, 3, 3, 3);
    EXPECT_EQ(v1, vec3<double>(6, 12, 18));
    EXPECT_EQ(v2, vec3<double>(14, 14, 14));
    m3d m6 = matmul(m3d(1, 2, 3, 4, 5, 6, 7, 8, 9), m3d(2, 3, 4, 5, 6, 7, 8, 9, 10));
    EXPECT_EQ(m6, m3d(36, 42, 48, 81, 96, 111, 126, 150, 174));
}

TEST(MAT33, DIV){
    m3d m1(1, 1, 1, 2, 2, 2, 4, 4, 4);
    m3d m2(2, 2, 2, 2, 2, 2, 2, 2, 2);

    m1 /= 2;
    EXPECT_EQ(m1, m3d(0.5, 0.5, 0.5, 1, 1, 1, 2, 2, 2));
    m2 /= m1;
    EXPECT_EQ(m2, m3d(4, 4, 4, 2, 2, 2, 1, 1, 1));
    m3d m3 = m1 / 2;
    EXPECT_EQ(m3, m3d(0.25, 0.25, 0.25, 0.5, 0.5, 0.5, 1, 1, 1));
    m3d m4 = 2 / m1;
    EXPECT_EQ(m4, m3d(4, 4, 4, 2, 2, 2, 1, 1, 1));
    m3d m5 = m1 / m2;
    EXPECT_EQ(m5, m3d(0.125, 0.125, 0.125, 0.5, 0.5, 0.5, 2, 2, 2));

    ASSERT_DEATH(m1/0, "Assert");
    ASSERT_DEATH(m1/m3d(1, 2, 0, 1, 1, 1, 1, 1, 1), "Assert");
}

TEST(MAT33, TRACE){
    m3d m(1, 1, 1, 2, 2, 2, 3, 3, 4);
    EXPECT_EQ(m.trace(), 7);
}

TEST(MAT33, DETERMINANT){
    m3d m(1, 1, 1, 1, 2, 3, 1, 5, 1);
    EXPECT_EQ(m.det(), -8);
}

TEST(MAT33, INVERSE){
    m3d m(1, 1, 1, 1, 2, 3, 1, 5, 1);
    EXPECT_EQ(m.getInv(), m3d(1.625, -0.5, -0.125, -0.25, 0, 0.25, -0.375, 0.5, -0.125));
    EXPECT_EQ(m.inv(), m3d(1.625, -0.5, -0.125, -0.25, 0, 0.25, -0.375, 0.5, -0.125));
}

TEST(MAT33, TRANSPOSE){
    m3d m(1, 1, 1, 2, 2, 2, 3, 3, 3);
    EXPECT_EQ(m.getTranspose(), m3d(1, 2, 3, 1, 2, 3, 1, 2, 3));
    EXPECT_EQ(m.transpose(), m3d(1, 2, 3, 1, 2, 3, 1, 2, 3));
}

TEST(MAT33, ROW_COL){
    m3d m(1, 2, 3, 4, 5, 6, 7, 8, 9);

    EXPECT_EQ(m.row(0), vec3<double>(1, 2, 3));
    EXPECT_EQ(m.row(1), vec3<double>(4, 5, 6));
    EXPECT_EQ(m.row(2), vec3<double>(7, 8, 9));
    EXPECT_EQ(m.col(0), vec3<double>(1, 4, 7));
    EXPECT_EQ(m.col(1), vec3<double>(2, 5, 8));
    EXPECT_EQ(m.col(2), vec3<double>(3, 6, 9));

    ASSERT_DEATH(m.row(3), "Assert");
    ASSERT_DEATH(m.col(3), "Assert");
}

TEST(MAT33, PER_ELEMENT_FUNC){
    m3d m(1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9);

    EXPECT_TRUE(Math::floatEqual(m.frac(), m3f(0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9)));
    EXPECT_TRUE(Math::floatEqual(Math::frac(m), m3f(0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9)));
    EXPECT_EQ(m.round(), m3d(1, 1, 1, 1, 2, 2, 2, 2, 2));
    EXPECT_EQ(Math::round(m), m3d(1, 1, 1, 1, 2, 2, 2, 2, 2));
    EXPECT_EQ(m.ceil(), m3d(2, 2, 2, 2, 2, 2, 2, 2, 2));
    EXPECT_EQ(Math::ceil(m), m3d(2, 2, 2, 2, 2, 2, 2, 2, 2));
    EXPECT_EQ(m.floor(), m3d(1, 1, 1, 1, 1, 1, 1, 1, 1));
    EXPECT_EQ(Math::floor(m), m3d(1, 1, 1, 1, 1, 1, 1, 1, 1));
    EXPECT_EQ((-m).abs(), m3d(1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9));
    EXPECT_EQ(Math::abs(-m), m3d(1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9));
}

// TEST(MAT33, IN_OUT){
//     m3d m;
//     std::cout << "Input mat33 : ";
//     std::cin >> m;
//     std::cout << m << std::endl;
// }

TEST(MAT33, MIN_MAX){
    m3d m1(1, 2, 3, 4, 5, 6, 7, 8, 9);

    EXPECT_EQ(Math::max(m1, 6.0), m3d(6, 6, 6, 6, 6, 6, 7, 8, 9));
    EXPECT_EQ(Math::max(m1, m3d(9, 8, 7, 6, 5, 4, 3, 2, 1)), m3d(9, 8, 7, 6, 5, 6, 7, 8, 9));
    EXPECT_EQ(Math::min(m1, 6.0), m3d(1, 2, 3, 4, 5, 6, 6, 6, 6));
    EXPECT_EQ(Math::min(m1, m3d(9, 8, 7, 6, 5, 4, 3, 2, 1)), m3d(1, 2, 3, 4, 5, 4, 3, 2, 1));
}