#ifndef _LL_AXISANGLE_H_
#define _LL_AXISANGLE_H_

#include "../Vec/vec_header.h"

namespace LLib
{
    // http://www.euclideanspace.com/maths/geometry/rotations/axisAngle/index.htm
    // singularity: 0, PI
    // Right hand rule
    template <typename T>
    class AxisAngle
    {
    public:
        typedef T ValueType;

    private:

        // data 
        union{

            struct{
                vec3<T> _axis;
                T _angle;
            };

            struct{
                T _x, _y, _z;
                T _theta;
            };
        };

    public:

        // Constructor
        AxisAngle(){};

        AxisAngle(const vec3<T> &axis, T angle) : _axis(axis), _angle(angle) {}

        AxisAngle(T x_, T y_, T z_, T theta_ = 0) : _x(x_), _y(y_), _z(z_), _theta(theta_) {}

        AxisAngle(const AxisAngle<T> &other) : _axis(other.axis()), _angle(other.angle()) {}

        template <typename U>
        AxisAngle<U> toType() const {
            return AxisAngle<U>(_axis.toType<U>, static_cast<U>(_angle));
        }

        // Access
        vec3<T> axis() const {
            return _axis;
        }

        T angle() const {
            return _angle;
        }

        T x() const {
            return _axis.x;
        }

        T y() const {
            return _axis.y;
        }

        T z() const {
            return _axis.z;
        }

        // Set
        void setAxis(const vec3<T> &axis){
            _axis = axis;
        }

        void setAxis(T x_, T y_, T z_){
            _x = x_;
            _y = y_;
            _z = z_;
        }

        void setAngle(T angle){
            _angle = angle;
        }

        // Assign
        AxisAngle<T> &operator=(const AxisAngle<T> &other){
            _axis = other.axis();
            _angle = other.angle();
            return *this;
        }

        // Equal
        bool operator==(const AxisAngle<T> &other) const {
            return (_axis == other.axis() && _angle == other.angle());
        }

        // Not Equal
        bool operator!=(const AxisAngle<T> &other) const {
            return (_axis != other.axis() && _angle != other.angle());
        }

        void normalize(){
            assert(_axis.lengthSq() != 0);
            _axis.normalize();
        }

        vec3<T> getNormalizeAxis() const {
            assert(_axis.lengthSq() != 0);
            return _axis.getNormalize();
        }

        AxisAngle<T> getNormalize() const {
            assert(_axis.lengthSq() != 0);
            return AxisAngle<T>(_axis.getNormalize(), _angle);
        }

        // // set

        // void set(const AxisAngle<T> &other){
        //     *this = other;
        // }

        // void set(const EulerAngle<T> &aa){

        // }

        // void set(const Quaternion<T> &q){

        // }

        // void set(const RotationMatrix<T> &R){

        // }

        // void set(const TransformMatrix<T> &T){

        // }

        // // convert
        // EulerAngle<T> toEuler() const {
        //     EulerAngle<T> result;
        //     return result;
        // }

        // Quaternion<T> toQuaternion() const {
        //     Quaternion<T> result;
        //     return result;
        // }

        // RotationMatrix<T> toRotationMatrix() const {
        //     RotationMatrix<T> result;
        //     return result;
        // }

        // TransformMatrix<T> toTransformMatrix() const {
        //     TransformMatrix<T> result;
        //     return result;
        // }

        friend bool floatEqual(const AxisAngle &lhs, const AxisAngle &rhs){
            using LLib::Math::floatEqual;
            return floatEqual(lhs._axis, rhs._axis) && floatEqual(lhs._angle, rhs._angle);
        }

        friend std::ostream &operator<<(std::ostream &out, const AxisAngle &aa){
            out << "(" << aa._x << ", " << aa._y << ", " << aa._z << "; " << aa._theta << ")";
            return out;
        }

        friend std::istream &operator>>(std::istream &in, AxisAngle &&aa){
            in >> aa._x >> aa._y >> aa._z >> aa._theta;
            return in;
        }


    }; // class AxisAngle
} // namespace LLib
#endif // _LL_AXISANGLE_H_

//   /** \returns the inverse rotation, i.e., an angle-axis with opposite rotation angle */
//   EIGEN_DEVICE_FUNC AngleAxis inverse() const
//   { return AngleAxis(-m_angle, m_axis); }