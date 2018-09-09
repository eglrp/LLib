#ifndef _LL_POINT_H_
#define _LL_POINT_H_

#include "Point.h"

namespace LLib
{

    using Point2 = Vec2;
    using cPoint2 = const Vec2;

    using Point2d = Point2<double>;
    using Point2f = Point2<float>;
    using Point2i = Point2<int>;

    using cPoint2d = const Point2<double>;
    using cPoint2f = const Point2<float>;
    using cPoint2i = const Point2<int>;

    using Point3 = Vec3;
    using cPoint3 = const Vec3;

    using Point3d = Point3<double>;
    using Point3f = Point3<float>;
    using Point3i = Point3<int>;

    using cPoint3d = const Point3<double>;
    using cPoint3f = const Point3<float>;
    using cPoint3i = const Point3<int>;

}   // namespace LLib

#endif  // _LL_POINT_H_