#ifndef _LL_LINESEGMENT3_H_H 
#define _LL_LINESEGMENT3_H_H

#include "../Math/Vec/vec2.h"

namespace LLib
{
    template <typename T>
    class LineSegment2
    {
    private:
        vec3<T> _p0;
        vec3<T> _p1;
        vec3<T> _dir;

    public:
        LineSegment3(const vec3<T> &p0_, const vec3<T> &p1_){
            _p0 = p0_;
            _p1 = p1_;
            _dir = _p0 - _p1;
        }

        const vec3<T> &p0() const {
            return _p0;
        }

        const vec3<T> &p1() const {
            return _p1;
        }

        const vec3<T> &dir() const {
            return _dir;
        }

    }  // class LineSegment

    typedef LineSegment3<double> LineSegment3f;
    typedef LineSegment3<float> LineSegment3f;

}  // namespace LLib

#endif  // _LL_LINESEGMENT3_H_H 