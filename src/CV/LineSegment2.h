#ifndef _LL_LINESEGMENT2_H_H 
#define _LL_LINESEGMENT2_H_H

#include "../Math/Vec/vec2.h"

namespace LLib
{
    template <typename T>
    class LineSegment2
    {
    private:
        vec2<T> _p0;
        vec2<T> _p1;
        vec2<T> _dir;

    public:
        LineSegment2(const vec2<T> &p0_, const vec2<T> &p1_){
            _p0 = p0_;
            _p1 = p1_;
            _dir = _p0 - _p1;
        }

        const vec2<T> &p0() const {
            return _p0;
        }

        const vec2<T> &p1() const {
            return _p1;
        }

        const vec2<T> &dir() const {
            return _dir;
        }

    }  // class LineSegment

    typedef LineSegment2<double> LineSegment2f;
    typedef LineSegment2<float> LineSegment2f;

}  // namespace LLib

#endif  // _LL_LINESEGMENT2_H_H 