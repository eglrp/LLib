#ifndef _LL_LINE2_H_
#define _LL_LINE2_H_

namespace LLib
{
    template <typename T>
    class Line2
    {
    private:
        vec2<T> _p;
        vec2<T> _dir;

    public:
        Line2(const vec2<T> &p0, const vec2<T> &p1){
            _p = p0;
            _dir = p1 - p0;
        }

        Line2(const LineSegment2<T> &ls){
            _p = ls.p0();
            _dir = ls.dir();
        }

        const vec2<T> &p() const {
            return _p;
        }

        const vec2<T> &dir() const {
            return _dir;
        }

    }; // class Line

    typedef Line2<double> Line2d;
    typedef Line2<float> Line2f;
}

#endif  // _LL_LINE2_H_