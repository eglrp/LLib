#include "../mattype.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../utils/doctest.h"

using namespace LLib;

TEST_CASE("Inilization")
{
    matXd mx1(2, 2);
    mx1(0, 0) = 0;
    mx1(0, 1) = 1;
    mx1(1, 0) = 2;
    mx1(1, 1) = 3;

    matXd mx2(2, 2);
    mx2 << 0, 1, 2, 3;

    CHECK_EQ(mx1, mx2);

    mat22f m1;
    m1(0, 0) = 0;
    m1(0, 1) = 1;
    m1(1, 0) = 2;
    m1(1, 1) = 3;

    mat22f m2;
    m2 << 0, 1, 2, 3;

    CHECK_EQ(m1, m2);

    matXf mx(2, 2);
    mx << 0, 1, 2, 3;

    CHECK_EQ(m1, mx);


    CHECK_EQ(mat22f::Constant(1), (matXf(2,2) << 1, 1, 1, 1).finished());
    CHECK_EQ(matXf::Constant(2, 2, 4), (matXf(2,2) << 4, 4, 4, 4).finished());

    CHECK_EQ(mat22f::Zero(), (matXf(2,2) << 0, 0, 0, 0).finished());
    CHECK_EQ(matXf::Zero(2, 2), (matXf(2,2) << 0, 0, 0, 0).finished());

    CHECK_EQ(mat22f::Identity(), (matXf(2,2) << 1, 0, 0, 1).finished());
    CHECK_EQ(matXf::Identity(2, 2), (matXf(2,2) << 1, 0, 0, 1).finished());

    // Random()
    // setZero()
    // setIdentity()
    // setLinSpaced() 
}

TEST_CASE("Resizing")
{
    matXd mx(3, 3);
    CHECK_EQ(mx.rows(), 3);
    CHECK_EQ(mx.cols(), 3);
    CHECK_EQ(mx.size(), 9);

    mx.resize(2, 2);
    CHECK_EQ(mx.size(), 4);
}

// Block operation: Block of size (p,q), starting at (i,j)
// Blocks expressions can be used both as rvalues and as lvalues
TEST_CASE("Block")
{
    mat44f m;
    m << 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15;

    matXf mx(4, 4);
    mx = m;
    // dynamic-size block expression: matrix.block(i,j,p,q);
    auto mx1122 = mx.block(1, 1, 2, 2);
    auto mx_row2 = mx.row(2);
    auto mx_col2 = mx.col(2);

    // fixed-size block expression: matrix.block<p,q>(i,j);
    auto m1122 = m.block<2,2>(1,1);
    auto m_row2 = m.row(2);
    auto m_col2 = m.col(2);

    /* 
                                            Corner-related operations
        Top-left p by q block *	                 matrix.topLeftCorner(p,q);         matrix.topLeftCorner<p,q>();
        Bottom-left p by q block *	             matrix.bottomLeftCorner(p,q);      matrix.bottomLeftCorner<p,q>();
        Top-right p by q block *	             matrix.topRightCorner(p,q);        matrix.topRightCorner<p,q>();
        Bottom-right p by q block *	             matrix.bottomRightCorner(p,q);     matrix.bottomRightCorner<p,q>();
        Block containing the first q rows *	     matrix.topRows(q);                 matrix.topRows<q>();
        Block containing the last q rows *	     matrix.bottomRows(q);              matrix.bottomRows<q>();
        Block containing the first p columns *	 matrix.leftCols(p);                matrix.leftCols<p>();
        Block containing the last q columns *	 matrix.rightCols(q);               matrix.rightCols<q>();
    */


    CHECK_EQ(m, mx);
    CHECK_EQ(m1122, mx1122);
    CHECK_EQ(m_row2, mx_row2);
    CHECK_EQ(m_col2, mx_col2);
}

// TODO: For in-place transposition, as for instance in a = a.transpose(), simply use the transposeInPlace() function:
TEST_CASE("Operation")
{
    // mat.transpose()
    // mat.conjugate()
    // mat.adjoint()
    // mat.transposeInPlace()
    // mat.conjugateInPlace()
    // mat.adjointInPlace()

    // Reduction
    // mat.sum()
    // mat.prod()
    // mat.mean()
    // mat.minCoeff()
    // mat.minCoeff(&i,&j) return position in (i, j)
    // mat.maxCoeff()
    // mat.maxCoeff(&i,&j) return position in (i, j)
    // mat.trace()
}