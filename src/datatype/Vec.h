#ifndef _LL_VEC_H_
#define _LL_VEC_H_

#include <iostream>

namespace LLib
{
    // TODO: union

    // 2D vector
    template <typename T>
    class Vec2
    {
        public:
            Vec2(T x_ = 0, T y_ = 0): x(x_), y(y_) {}
            T x;
            T y;
    };  // class Vec2

    // 3D vector
    template <typename T>
    class Vec3
    {
        public:
            Vec3(T x_ = 0, T y_ = 0, T z_ = 0): x(x_), y(y_), z(z_) {}
            T x;
            T y;
            T z;
    };  // class Vec3

    // 4D vector
    template <typename T>
    class Vec4
    {
        public:
            Vec4(T x_ = 0, T y_ = 0, T z_ = 0, T w_ = 0): x(x_), y(y_), z(z_), w(w_) {}
            T x;
            T y;
            T z;
            T w;
    };  // class Vec4

    // TODO:
    // // 6D vector
    // template <typename T>
    // class Vec6
    // {
    //     public:
    //         Vec6(T x_ = 0, T y_ = 0, T z_ = 0): x(x_), y(y_), z(z_) {}
    //         T x;
    //         T y;
    //         T z;
    // };  // class Vec6

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Vec2<T> &p)
    {
        os << "(" << p.x << "," << p.y << ")";
        return os;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Vec3<T> &p)
    {
        os << "(" << p.x << "," << p.y << "," << p.z << ")";
        return os;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Vec4<T> &p)
    {
        os << "(" << p.x << "," << p.y << "," << p.z << "," << p.w << ")";
        return os;
    }

    // TODO:
    // template <typename T>
    // std::ostream &operator<<(std::ostream &os, const Vec6<T> &p)
    // {
    //     os << "(" << p.x << "," << p.y << "," << p.z << ")";
    //     return os;
    // }

    using cVec2 = const Vec2;

    using Vec2d = Vec2<double>;
    using Vec2f = Vec2<float>;
    using Vec2i = Vec2<int>;

    using cVec2d = const Vec2<double>;
    using cVec2f = const Vec2<float>;
    using cVec2i = const Vec2<int>;

    using cVec3 = const Vec3;

    using Vec3d = Vec3<double>;
    using Vec3f = Vec3<float>;
    using Vec3i = Vec3<int>;

    using cVec3d = const Vec3<double>;
    using cVec3f = const Vec3<float>;
    using cVec3i = const Vec3<int>;

    using cVec4 = const Vec4;

    using Vec4d = Vec4<double>;
    using Vec4f = Vec4<float>;
    using Vec4i = Vec4<int>;

    using cVec4d = const Vec4<double>;
    using cVec4f = const Vec4<float>;
    using cVec4i = const Vec4<int>;

    // TODO:

    // using cVec6 = const Vec6;

    // using Vec6d = Vec6<double>;
    // using Vec6f = Vec6<float>;
    // using Vec6i = Vec6<int>;

    // using cVec6d = const Vec6<double>;
    // using cVec6f = const Vec6<float>;
    // using cVec6i = const Vec6<int>;

}

#endif  // _LL_VEC_H_