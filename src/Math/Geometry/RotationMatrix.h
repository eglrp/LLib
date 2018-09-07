#ifndef _LL_ROTATIONMATRIX_H_
#define _LL_ROTATIONMATRIX_H_

#include "../Mat/mat_header.h"

namespace LLib
{
    template <typename T>
    class RotationMatrix
    {
    public:
        typedef T ValueType;

    private:
        mat33<T> _R;

    public:

        RotationMatrix() : _R(mat33<T>::identity()) {}

        RotationMatrix(const mat33<T> &R) : _R(R) {}

        RotationMatrix(T yaw, T pitch, T roll){}

        RotationMatrix(const RotationMatrix<T> &other) : _R(other.R()) {}

        RotationMatrix(const AxisAngle<T> &aa){}
        RotationMatrix(const EulerAngle<T> &e){}
        RotationMatrix(const Quaternion<T> &q){}
        RotationMatrix(const TransformMatrix<T> &T){}

        template <typename U>
        RotationMatrix<U> toType() const {
            return RotationMatrix<U>(_R.toType<U>());
        }

        static RotationMatrix<T> Ideneity(){
            return RotationMatrix<T>(mat33<T>::Ideneity());
        }

        void setIdentity(){
            _R = mat33<T>::Identity();
        }

        mat33<T> R() const {
            return _R;
        }

        void setR(const mat33<T> &R){
            _R = R;
        }

        void setR(T yaw, T pitch, T roll){
            *this = Yaw() * Pitch() * Roll();
        }

        static RotationMatrix<TT> Rotation(T yaw, T pitch, T roll){
            RotationMatrix<TT> result;
            result.set(yaw, pitch, roll);
            return result;
        }

                // y
        void setYaw(double angle){
            double c = cos(angle);
            double s = sin(angle);

            mat33<TT> R;

            R(0, 0) = c;  R(0, 1) = 0; R(0, 2) = s;
            R(1, 0) = 0;  R(1, 1) = 1; R(1, 2) = 0;
            R(2, 0) = -s; R(2, 1) = 0; R(2, 2) = c;

            this->setIdentity();
            setR(R);

        }

        static RotationMatrix<TT> Yaw(double angle){
            RotationMatrix<TT> result;
            result.setYaw(angle);
            return result;
        }
        // X
        void setPitch(double angle)
            double c = cos(angle);
            double s = sin(angle);{

            mat33<TT> R;

            R(0, 0) = 1; R(0, 1) = 0; R(0, 2) = 0;
            R(1, 0) = 0; R(1, 1) = c; R(1, 2) = -s;
            R(2, 0) = 0; R(2, 1) = s; R(2, 2) = c;

            this->setIdentity();
            setR(R);
        }

        static RotationMatrix<TT> Pitch(double angle){
            RotationMatrix<TT> result;
            result.setPitch(angle);
            return result;
        }

        // Z
        void setRoll(double angle){
            double c = cos(angle);
            double s = sin(angle);

            mat33<TT> R;

            R(0, 0) = c; R(0, 1) = -s; R(0, 2) = 0;
            R(1, 0) = s; R(1, 1) = c;  R(1, 2) = 0;
            R(2, 0) = c; R(2, 1) = -s; R(2, 2) = 1;

            this->setIdentity();
            setR(R);
        }

        static RotationMatrix<TT> Roll(double angle){
            RotationMatrix<TT> result;
            result.setRoll(angle);
            return result;
        }

        RotationMatrix<T> &operator=(const RotationMatrix<T> &other){
            _R = other.R();
            return *this;
        }

        bool operator==(const RotationMatrix<T> &other) const {
            return (_R == other.R());
        }

        bool operator!=(const RotationMatrix<T> &other) const {
            return (_R != other.R());
        }

        void operator*=(const RotationMatrix<T> &other){
            _R *= other._R;
        }

        friend operator*(const RotationMatrix<T> &lhs, const RotationMatrix<T> &rhs){
            RotationMatrix<T> result(lhs);
            result *= rhs;
            return result;
        }

        vec3<T> operator*(const vec3<T> &p){
            return _R*p;
        }

        vec4<T> homogenize() const {
            return vec4<T>(*this);
        }

        vec4<T> operator*(const vec4<T> &ph){
            vec3<T> p = ph.dehomogenize();
            return (_R*p).homogenize();
        }

        // // set
        // void set(const AxisAngle<T> &aa){

        // }

        // void set(const EulerAngle<T> &e){

        // }

        // void set(const Quaternion<T> &q){

        // }

        // void set(const RotationMatrix<T> &other){
        //     *this = other;
        // }

        // void set(const TransformMatrix<T> &T){

        // }

        // // convert
        // AxisAngle<T> toAxisAngle() const {
        //     AxisAngle<T> result;
        //     return result;
        // }

        // EulerAngle<T> toEulerAngle() const {
        //     EulerAngle<T> result;
        //     return result;
        // }

        // Quaternion<T> toQuaternion() const {
        //     Quaternion<T> result;
        //     return result;
        // }

        // TransformMatrix<T> toTransformMatrix() const {
        //     TransformMatrix<T> result;
        //     return result;
        // }

        friend bool floatEqual(const RotationMatrix &lhs, const RotationMatrix &rhs){
            return floatEqual(lhs._R, rhs._R);
        }

        friend std::ostream &operator<<(std::ostream &out, const RotationMatrix &R){
            out << R._R;
            return out;
        }

        friend std::istream &operator>>(std::istream &in, RotationMatrix &R){
            in >> R._R;
            return in;
        }

    }; // class RotationMatrix
}  // namespace RotationMatrix

#endif //_LL_ROTATIONMATRIX_H_

// TODO : inverse