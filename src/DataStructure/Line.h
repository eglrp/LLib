#ifndef _LL_LINE_H_
#define _LL_LINE_H_

#include <iostream>

namespace LLib
{
    // 2D line: ax + by + c = 0
    template <typename T>
    class Line2
    {
        public:
            Line2(T a_, T b_, T c_): a(a_), b(b_), c(c_) {}
            T a;
            T b;
            T c
    };  // class Line2

    // 3D Line
    template <typename T>
    class Line3
    {
        public:
            Line3(cPoint<T> &p_, cVec<T> &dir_): p(p_), dir(dir_) {}
            
            Point3<T> p;
            Vec3<T> dir;
    };  // class Line3

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Line2<T> &l)
    {
        os << l.a << "x + " << l.b << "y + " << l.c << " = 0" ;
        return os;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Line3<T> &l)
    {
        os << "point: " << l.p << "; direction: " << l.dir;;
        return os;
    }

    using cLine2 = const Line2;

    using Line2d = Line2<double>;
    using Line2f = Line2<float>;
    using Line2i = Line2<int>;

    using cLine2d = const Line2<double>;
    using cLine2f = const Line2<float>;
    using cLine2i = const Line2<int>;

    using cLine3 = const Line3;

    using Line3d = Line3<double>;
    using Line3f = Line3<float>;
    using Line3i = Line3<int>;

    using cLine3d = const Line3<double>;
    using cLine3f = const Line3<float>;
    using cLine3i = const Line3<int>;

}   // namespace LLib

#endif  // _LL_LINE_H_