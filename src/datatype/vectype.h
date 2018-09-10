#ifndef _LL_VEC_H_
#define _LL_VEC_H_

#include "Eigen/Dense"

namespace LLib
{
    using vec2f = Eigen::Matrix<float, 2, 1>;
    using vec3f = Eigen::Matrix<float, 3, 1>;
    using vec4f = Eigen::Matrix<float, 4, 1>;
    using vec6f = Eigen::Matrix<float, 6, 1>;

    using cvec2f = const vec2f;
    using cvec3f = const vec3f;
    using cvec4f = const vec4f;
    using cvec6f = const vec6f;    

    using vecXf = Eigen::Matrix<float, Eigen::Dynamic, 1>;

    using vec2d = Eigen::Matrix<double, 2, 1>;
    using vec3d = Eigen::Matrix<double, 3, 1>;
    using vec4d = Eigen::Matrix<double, 4, 1>;
    using vec6d = Eigen::Matrix<double, 6, 1>;    

    using cvec2d = const vec2d;
    using cvec3d = const vec3d;
    using cvec4d = const vec4d;
    using cvec6d = const vec6d;

    using vecXd = Eigen::Matrix<double, Eigen::Dynamic, 1>;
}   // namespace LLib

#endif  // _LL_VEC_H_