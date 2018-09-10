#ifndef _LL_TRIANGLE_H_
#define _LL_TRIANGLE_H_

#include "vectype.h"

namespace LLib
{

    template<typename VecType>
    struct triangle
    {
        using FloatType = typename VecType::Scalar;

        VecType vertices[3];

        triangle() {}
        triangle(const VecType &v0, const VecType &v1, const VecType &v2) { vertices[0] = v0; vertices[1] = v1; vertices[2] = v2; }

        VecType getNormal() const;
    	FloatType getArea() const;
    };

    // TODO:
    // template<typename VecType>
    // inline VecType triangle<VecType>::getNormal() const
    // {
    //     auto normal = (vertices[1] - vertices[0]).cross(vertices[2] - vertices[0]);
    //     normal /= normal.norm();
    //     return normal; 
    // }
    
    // TODO:
    // template<typename VecType>
    // inline typename VecType::Scalar triangle<VecType>::getArea() const 
    // {
    // 	VecType ab = vertices[1] - vertices[0];
    // 	VecType ac = vertices[2] - vertices[0];
    // 	FloatType len = ab.norm() * ac.norm();
    // 	FloatType cosTheta = (ab | ac) / len;
    // 	if (fabs(cosTheta + 1) < 0.00001f || fabs(cosTheta - 1) < 0.00001f) {
    // 		return 0;
    // 	}
    // 	FloatType theta = std::acos(cosTheta);
    // 	FloatType area (0.5f * len * std::sin(theta));
    // 	assert(area > 0);
    // 	return area;
    // }

    using triangle2f = triangle<vec2f>;
    using triangle2d = triangle<vec2d>;
    using triangle3f = triangle<vec3f>;
    using triangle3d = triangle<vec3d>;


} //namespace LLib


#endif  // _LL_TRIANGLE_H_