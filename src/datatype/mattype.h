#ifndef _LL_MATTYPE_H_
#define _LL_MATTYPE_H_

#include "Eigen/Dense"

namespace LLib
{
    using mat22f = Eigen::Matrix<float, 2, 2>;
    using mat33f = Eigen::Matrix<float, 3, 3>;
    using mat44f = Eigen::Matrix<float, 4, 4>;
    using mat66f = Eigen::Matrix<float, 6, 6>;

    using matXf = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>;

    using mat22d = Eigen::Matrix<double, 2, 2>;
    using mat33d = Eigen::Matrix<double, 3, 3>;
    using mat44d = Eigen::Matrix<double, 4, 4>;
    using mat66d = Eigen::Matrix<double, 6, 6>;    

    using matXd = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
}   // namespace LLib

#endif  // _LL_MATTYPE_H_