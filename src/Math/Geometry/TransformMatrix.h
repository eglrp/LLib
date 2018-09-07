#ifndef _LL_TRANSFORMMATRIX_H_
#define _LL_TRANSFORMMATRIX_H_

namespace LLib
{
    template <typename TT>
    class TransformMatrix
    { 
    public:
        typedef TT ValueType;

    private:
        mat44<TT> _T;

    public:

        TransformMatrix() : _T(mat44<TT>::identity()) {}

        TransformMatrix(const vec3<TT> &t) {}

        TransformMatrix(const mat33<TT> &R) {}

        TransformMatrix(const mat33<TT> &R, const vec3<T> &t) {}

        TransformMatrix(const mat44<TT> &T_) : _T(T_) {}

        TransformMatrix(const TransformMatrix<TT> &other) : _T(other.T()) {}

        TransformMatrix(const AxisAngle<TT> &aa){}
        TransformMatrix(const EulerAngle<TT> &e){}
        TransformMatrix(const Quaternion<TT> &q){}
        TransformMatrix(const RotationMatrix<TT> &rm){}

        template <typename U>
        TransformMatrix<U> toType() const {
            return TransformMatrix<U>(_T.toType<U>());
        }

        static TransformMatrix<TT> Identity(){
            return TransformMatrix<TT>(mat44<TT>::Identity());
        }

        void setIdentity(){
            _T = mat44<TT>::Identity();
        }

        mat44<TT> &T() const {
            return _T;
        }

        mat33<TT> R() const {
            return mat33<TT>(
                _T(0, 0), _T(0, 1), _T(0, 2),
                _T(1, 0), _T(1, 1), _T(1, 2),
                _T(2, 0), _T(2, 1), _T(2, 2)
            );
        }

        RotationMatrix<TT> R() const {
            return RotationMatrix<TT>(R());
        }

        vec3<TT> &t() const {
            return vec3<TT>(_T(0, 3), _T(1, 3), _T(2, 3));
        }

        void setT(const mat44<TT> &T){
            _T = T;
        }

        void setT(const mat33<TT> &R, const vec3<TT> &t){
            setR(R);
            sett(t);
        }

        void setR(const mat33<TT> &R){
            _T(0, 0) = R(0, 0); _T(0, 1) = R(0, 1); _T(0, 2) = R(0, 2);
            _T(1, 0) = R(1, 0); _T(1, 1) = R(1, 1); _T(1, 2) = R(1, 2);
            _T(2, 0) = R(2, 0); _T(2, 1) = R(2, 1); _T(2, 2) = R(2, 2);
        }

        void setR(T yaw, T pitch, T roll){
            *this = Yaw() * Pitch() * Roll();
        }

        TransformMatrix<TT> Rotation(T yaw, T pitch, T roll){
            TransformMatrix<TT> result;
            result.set(yaw, pitch, roll);
            return result;
        }

        void sett(const vec3<TT> &t){
            _T(0, 3) = t[0];
            _T(1, 3) = t[1];
            _T(2, 3) = t[2];
        }

        void sett(TT tx, TT ty, TT tz){
            _T(0, 3) = tx;
            _T(1, 3) = ty;
            _T(2, 3) = tz;
        }

        void sett(TT x){
            _T(0, 3) = x;
            _T(1, 3) = x;
            _T(2, 3) = x;
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

        static TransformMatrix<TT> Yaw(double angle){
            TransformMatrix<TT> result;
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

        static TransformMatrix<TT> Pitch(double angle){
            TransformMatrix<TT> result;
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

        static TransformMatrix<TT> Roll(double angle){
            TransformMatrix<TT> result;
            result.setRoll(angle);
            return result;
        }

        TransformMatrix<TT> &operator=(const TransformMatrix<TT> &other){
            _T = other.T();
            return *this;
        }

        bool operator==(const TransformMatrix<TT> &other) const {
            return (_T == other.T());
        }

        bool operator!=(const TransformMatrix<TT> &other) const {
            return (_T != other.T());
        }

        void operator*=(const TransformMatrix<TT> &other){
            _T *= other._T;
        }

        friend TransformMatrix<TT> operator*(const TransformMatrix &lhs, const TransformMatrix &rhs){
            TransformMatrix<TT> result(lhs);
            result *= rhs;
            return result;
        }

        vec3<TT> operator*(const vec3<TT> &p){
            vec4<TT> ph = vec4<TT>(p);
            vec4<TT> result = _T*ph;
            return result.dehomogenize();
        }

        vec4<TT> operator*(const vec4<TT> &ph){
            return _T*ph;
        }

        // // set
        // void set(const AxisAngle<T> &aa){

        // }

        // void set(const EulerAngle<T> &e){

        // }

        // void set(const Quaternion<T> &q){

        // }

        // void set(const RotationMatrix<T> &R){

        // }

        // void set(const TransformMatrix &other){
        //     *this = other;
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

        // RotationMatrix<T> toRotationMatrix() const {
        //     RotationMatrix<T> result;
        //     return result;
        // }

    }; // class TransformMatrix
} // namespace LLbase

#endif // _LL_TRANSFORMMATRIX_H_















    // static Matrix4x4 face(const vec3<FloatType>& vA, const vec3<FloatType>& vB)
    // {
    //     typedef vec3<FloatType> vec3;
    //     auto a = vA.getNormalized();
    //     auto b = vB.getNormalized();
    //     auto axis = b ^ a;
    //     float angle = vec3::angleBetween(a, b);

    //     if (angle == 0.0f) {  // No rotation
    //       return identity();
    //     } else if (axis.lengthSq() == 0.0f) {  // Need any perpendicular axis
          
    //       float dotX = vec3::dot(vec3::eX, a);
    //       if (std::abs(dotX) != (FloatType)1.0) {
    //         axis = vec3::eX - dotX * a;
    //       } else {
    //         axis = vec3::eY - vec3::dot(vec3::eY,a) * a;
    //       }
    //       axis.normalize();
    //     }
        
    //     return rotation(axis, -angle);
    // }

// TODO : inverse