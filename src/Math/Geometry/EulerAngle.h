#ifndef _LL_EULERANGLE_H_
#define _LL_EULERANGLE_H_

#include "../Vec/vec_header.h"

namespace LLib
{
    // http://www.euclideanspace.com/maths/geometry/rotations/euler/index.htm
    // singularity: PI/2, -PI/2
    // Right hand coordinate system
    template <typename T>
    class EulerAngle
    {
    public:
        typedef T ValueType;

    private:
        // rotation at x axis:
        // axis-angle : (1 0 0), roll
        // quaternion : c + i*s
        // rotation matrix : [1 0 0 ]
        //                   [0 cr -sr]
        //                   [0 sr cr ]

        // rotation at y axis:
        // axis-angle : (0 1 0), yaw
        // quaternion : c + j*s
        // rotation matrix : [ cy 0 sy]
        //                   [ 0 1 0]
        //                   [-sy 0 cy]

        // rotation at z axis: 
        // axis-angle : (0 0 1), pitch
        // quaternion : c + k*s
        // rotation matrix : [cp -sp 0]
        //                   [sp cp  0]
        //                   [0 0  1]

        // yzx
        // [cy*cp	-cy*sp*cr + sy*sr  cy*sp*sr + sy*cr ]
        // [sp	    cp*cr              -cp*sr           ]
        // [-sy*cp	sy*sp*cr + cy*sr   -sy*sp*sr + cy*cr]

        union{
            struct{
                T _heading;      // angle applied first (y axis)
                T _attitude;     // angle applied second (z axis)
                T _bank;         // angle applied last (x axis)
            };

            struct{
                T _azimuth;      // angle applied first (y axis)
                T _elevation;    // angle applied second (z axis)
                T _tilt;         // angle applied last (x axis)
            };

            struct{
                T _theta;        // angle applied first (y axis)
                T _phi;          // angle applied second (z axis)
                T _psi;          // angle applied last (x axis)
            };

            // main interface
            struct{
                T _yaw;         // angle applied first (y axis)
                T _pitch;       // angle applied second (z axis)
                T _roll;        // angle applied last (x axis)
            };

        };

        public:

            EulerAngle(T yaw = 0, T pitch = 0, T roll = 0) : _yaw(yaw), _pitch(pitch), _roll(roll) {}

            EulerAngle(const EulerAngle<T> &other) : _yaw(other.yaw()), _pitch(other.pitch()), _roll(other.roll()) {}

            EulerAngle(const vec3<T> &angles) : _yaw(angles[0]), _pitch(angles[1]), _roll(angles[2]) {}

            EulerAngle(const T *angles) : _yaw(angles[0]), _pitch(angles[1]), _roll(angles[2]) {}

            template <typename U>
            EulerAngle<U> toType() const {
                return EulerAngle<U>(static_cast<U>(yaw), static_cast<U>(pitch), static_cast<U>(roll));
            }

            T yaw() const {
                return _yaw;
            }

            T pitch() const {
                return _pitch;
            }

            T roll() const {
                return _roll;
            }

            void setYaw(T yaw){
                _yaw = yaw;
            }

            void setPitch(T pitch){
                _pitch = pitch;
            }

            void setRoll(T roll){
                _roll = roll;
            }

            void set(const vec3<T> &v){
                _yaw = v.yaw;
                _pitch = v.pitch;
                _roll = v.roll;
            }

            EulerAngle<T> &operator=(const EulerAngle<T> &other){
                _yaw = other.yaw();
                _pitch = other.pitch();
                _roll = other.roll();
                return *this;
            }

            bool operator==(const EulerAngle<T> &other) const {
                return (_yaw == other.yaw() && _pitch == other.pitch(), _roll == other.roll());
            }

            bool operator!=(const EulerAngle<T> &other) const {
                return (_yaw != other.yaw() && _pitch != other.pitch(), _roll != other.roll());
            }

            // // set
            // void set(const AxisAngle<T> &aa){

            // }

            // void set(const EulerAngle<T> &other){
            //     *this = other;
            // }

            // void set(const Quaternion<T> &q){

            // }

            // void set(const RotationMatrix<T> &R){

            // }

            // void set(const TransformMatrix<T> &T){

            // }

            // // convert
            // AxisAngle<T> toAxisAngle() const {
            //     AxisAngle<T> result;
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
        // };

        friend bool floatEqual(const EulerAngle &lhs, const EulerAngle &rhs){
            using LLib::Math::floatEqual;
            return floatEqual(lhs._yaw, rhs._yaw) && floatEqual(lhs._pitch, rhs._pitch) && floatEqual(lhs._roll, rhs._roll);
        }

        friend std::ostream &operator<<(std::ostream &out, const EulerAngle &euler){
            out << "(" << euler._yaw << ", " << euler._pitch << ", " << euler._yaw << ")";
            return out;
        }

        friend std::istream &operator>>(std::istream &in,EulerAngle &euler){
            in >> euler._yaw >> euler._pitch >> euler._yaw;
            return in;
        }

    }; // class EulerAngle

} // namespace LLib

#endif // _LL_EULERANGLE_H_