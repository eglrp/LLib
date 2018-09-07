#ifndef _LL_ROTATION3_H
#define _LL_ROTATION3_H

#include "../Helper/Eigen/Geometry"

namespace LLib
{
    template <typename T>
    class EulerAngle
    {

    };

    template <typename T>
    class AngleAxis
    {

    };

    // q = w + xi + yj + zk
    // Advantages:
    // - compact storage (4 scalars)
    // - efficient to compose (28 flops),
    // - stable spherical interpolation
    template <typename T>
    class Quaternion
    {
        public:
            Quaternion(T w_, T x_, T y_, T z_)
            Quaternion(T *data_)
            Quaternion(const Quaternion<T> &q)
            Quaternion(const AngleAxis<T> &aa)
            Quaternion(const Vec4<T> &coeff)
            Quaternion(const Mat44<T> &m)

            template <typename U>
            Quaternion(const Quaternion<U> &q)

            // 4x1 vector, 3x3 matrix, angle-axis
            operator=()

            Quaternion<T> normalize() const { return Quaternion<T>(q_.normalized()); }

            void normalize_inplace() { q_.normalize(); }

            T squaredNorm() const { return q.squaredNorm(); }

            T norm() const { return q.norm(); }

            conjugate()


            bool isApprox(const Quaternion<T> &other) const { return q_.isApprox(other.q()); }

            static Quaternion<T> Identity() { return Eigen::Quaternion<T>::Identity(); }


            Quaternion<T> inverse() { q_.inverse(); return *this; }

            toRotationMatrix()

            angularDistance()

            _transformVector()

            cast()

            coeffs()
            cast()

            conjugate()

            Mat33<T> toRotationMatrix() const { return Mat33<T>(q.toRotationMatrix()); }


            Quaternion<T> slerp(const Quaternion<T> &other, T t) const { return q_.slerp(other.q()); }

            void setIdentity() { q_.setIdentity(); }

            T &w() { return data[0]; }
            T &x() { return data[1]; }
            T &y() { return data[2]; }
            T &z() { return data[3]; }

            Eigen::Quaternion<T> q() { return q_; }

            // imaginary part
            Vec3<T> { return Vec3<T>(&data[1]); }


        private:
            Eigen::Quaternion<T> q_;
            T *data;
    };

    template <typename T>
    Quaternion<T> slerp(const Quaternion<T> &q1, const Quaternion<T> &q2, T t)
    {
        return q1.slerp(q2, t);
    }

    template <typename T>
    Quaternion<T> setFromTwoVectors(cVec3 &v1, cVec3 &v2)
    {
        Quaternion<T> q;
        // TODO:
        // q.setFromTwoVectors(Map<>)
        return std::move(q);
    }

    dot()

    angularDistance()


    // scale, quaternion, transformation, translation
    operator*

    // Declaration

    using EulerAngled = EulerAngle<double>;
    using EulerAnglef = EulerAngle<float>;

    using cEulerAngled = const EulerAngle<double>;
    using cEulerAnglef = const EulerAngle<float>;

    using AngleAxisd = AngleAxis<double>;
    using AngleAxisf = AngleAxis<float>;

    using cAngleAxisd = const AngleAxis<double>;
    using cAngleAxisf = const AngleAxis<float>;

    using Quaterniond = Quaternion<double>;
    using Quaternionf = Quaternion<float>;

    using cQuaterniond = const Quaternion<double>;
    using cQuaternionf = const Quaternion<float>;

}   // namespace LLib

#endif  // _LL_ROTATION3_H