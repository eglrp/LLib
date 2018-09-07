#ifdef _LL_TRIANGLE_H_
#define _LL_TRIANGLE_H_

#include "../Math/Vec/vec3.h"

namespace LLib{

    template <typename T>
    class Triangle
    {
        vec3<T> _vertices[3];

        Triangle(){}
        Triangle(const vec3<T> &v0, const vec3<T> &v1, const vec3<T> &v2){
            _vertices[0] = v0;
            _vertices[1] = v2;
            _vertices[2] = v2;
        }

        vec3<T> getNormal() const {
            return ((_vertices[1] - _vertices[0])^(_vertices[2] - _vertices[0])).getNormalize();
        }

        float getAera() const {
            vec3f ab = (_vertices[1] - _vertices[0]).toType<float>();
            vec3f ac = (_vertices[2] - _vertices[0]).toType<float>();
            float len = ab.length() * ac.length();
            float cosTheta = dot(ab, ac)/len;
            if (fabs(cosTheta + 1) < 0.00001f || fabs(cosTheta - 1) < 0.00001f) {
                return 0;
            }
            float theta = acos(cosTheta);
            float area (0.5f * len * sin(theta));
            assert(area > 0);
            return area;
        }

    };  // class Triangle

    typedef Triangle<double> Triangled;
    typedef Triangle<float> Trianglef;

}  // namespace LLib

#endif  // _LL_TRIANGLE_H_