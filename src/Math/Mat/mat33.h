#ifndef _LL_MAT33_H_
#define _LL_MAT33_H_

#include "../../Utility/utility.h"
#include "../Vec/vec_header.h"

namespace LLib
{
    // row-like
    // <pre>
    //    0  1  2
    //    3  4  5
    //    6  7  8
    // <pre>
    template <typename T>
    class mat33
    {
    public:
        // data
        using ValueType = T;

        union{
            T mat[9];
            T mat2[3][3];
            struct{
                T
                _m00, _m01, _m02,
                _m10, _m11, _m12,
                _m20, _m21, _m22;
            };
        };

        // dimension
        static const uint Cols;
        static const uint Rows;    
        static const uint Num;
        _CPU_AND_GPU_CODE_ static bool isSquare(){
            return true;
        }

        // static func
        _CPU_AND_GPU_CODE_ static mat33 zeros(){
            return mat33(0, 0, 0, 
                         0, 0, 0,
                         0, 0, 0);
        }

        _CPU_AND_GPU_CODE_ static mat33 identity(){
            return mat33(1, 0, 0, 
                         0, 1, 0,
                         0, 0, 1);
        }

        _CPU_AND_GPU_CODE_ static mat33 full(T x){
            return mat33(x);
        }

        _CPU_AND_GPU_CODE_ static mat33 diag(T x){
            return mat33(x, 0, 0,
                         0, x, 0,
                         0, 0, x);
        }

        _CPU_AND_GPU_CODE_ static mat33 diag(T x, T y, T z){
            return mat33(x, 0, 0, 
                         0, y, 0,
                         0, 0, z);
        }

        template <typename U>
        _CPU_AND_GPU_CODE_ static mat33 diag(const vec3<U> &v){
            return mat33(v.x, 0,   0, 
                         0,   v.y, 0,
                         0,   0,   v.z);
        }

        // set func
        _CPU_AND_GPU_CODE_ void setIdentity(){
            _m00 = 1; _m01 = 0; _m02 = 0;
            _m10 = 0; _m11 = 1; _m12 = 0;
            _m20 = 0; _m21 = 0; _m22 = 1;
        }

        _CPU_AND_GPU_CODE_ void setZeros(){
            _m00 = 0; _m01 = 0; _m02 = 0;
            _m10 = 0; _m11 = 0; _m12 = 0;
            _m20 = 0; _m21 = 0; _m22 = 0;
        }

        _CPU_AND_GPU_CODE_ void setFull(T x){
            _m00 = x; _m01 = x; _m02 = x;
            _m10 = x; _m11 = x; _m12 = x;
            _m20 = x; _m21 = x; _m22 = x;
        }

        _CPU_AND_GPU_CODE_ void setDiag(T x){
            _m00 = x; _m01 = 0; _m02 = 0;
            _m10 = 0; _m11 = x; _m12 = 0;
            _m20 = 0; _m21 = 0; _m22 = x;
        }

        _CPU_AND_GPU_CODE_ void setDiag(T x, T y, T z){
            _m00 = x; _m01 = 0; _m02 = 0;
            _m10 = 0; _m11 = y; _m12 = 0;
            _m20 = 0; _m21 = 0; _m22 = z;
        }

        _CPU_AND_GPU_CODE_ void setDiag(const vec3<T> &v){
            _m00 = v.x; _m01 = 0;   _m02 = 0;  
            _m10 = 0;   _m11 = v.y; _m12 = 0;  
            _m20 = 0;   _m21 = 0;   _m22 = v.z;
       }


        // constructor
        _CPU_AND_GPU_CODE_ mat33(T x = 0){
            mat[0] = mat[1] = mat[2] = mat[3] = mat[4] = mat[5] = mat[6] = mat[7] = mat[8] = x;
        }

        template <typename U>
        _CPU_AND_GPU_CODE_ mat33(const U *m){
                mat[0] = m[0];
                mat[1] = m[1];
                mat[2] = m[2];
                mat[3] = m[3];
                mat[4] = m[4];
                mat[5] = m[5];
                mat[6] = m[6];
                mat[7] = m[7];
                mat[8] = m[8];
        }

        _CPU_AND_GPU_CODE_ mat33(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22){
            _m00 = m00; _m01 = m01; _m02 = m02;
            _m10 = m10; _m11 = m11; _m12 = m12;
            _m20 = m20; _m21 = m21; _m22 = m22;
        }

        template <typename U>
        _CPU_AND_GPU_CODE_ mat33(const mat33<U> &other){
            _m00 = other._m00;
            _m01 = other._m01;
            _m02 = other._m02;
            _m10 = other._m10;
            _m11 = other._m11;
            _m12 = other._m12;
            _m20 = other._m20;
            _m21 = other._m21;
            _m22 = other._m22;
        }

        // convert type
        template <typename U>
        _CPU_AND_GPU_CODE_ mat33<U> toType() const {
            return mat33<U>(*this);
        }

        // access
        _CPU_AND_GPU_CODE_ T &at(const uint i, const uint j){
            assert(i < 3 && j < 3);
            return mat2[i][j];
        }

        _CPU_AND_GPU_CODE_ const T &at(const uint i, const uint j) const {
            assert(i < 3 && j < 3);
            return mat2[i][j];
        }

        _CPU_AND_GPU_CODE_ T  &at(const uint i){
            assert(i < 9);
            return mat[i];
        }

        _CPU_AND_GPU_CODE_ const T &at(const uint i) const {
            assert(i < 9);
            return mat[i];
        }

        _CPU_AND_GPU_CODE_ T &operator()(const uint i, const uint j){
            assert(i < 3 && j < 3);
            return mat2[i][j];
        }
        
        _CPU_AND_GPU_CODE_ const T &operator()(const uint i, const uint j) const {
            assert(i < 3 && j < 3);
            return mat2[i][j];
        }

        _CPU_AND_GPU_CODE_ T &operator[](const uint i){
            assert(i < 9);
            return mat[i];
        }

        _CPU_AND_GPU_CODE_ const T &operator[](const uint i) const {
            assert(i < 9);
            return mat[i];
        }

        // == / !=
        _CPU_AND_GPU_CODE_ bool operator==(const mat33 &other) const {
            for(size_t i = 0; i < 9; i++){
                if(mat[i] != other[i]) return false;
            }
            return true;
        }

        _CPU_AND_GPU_CODE_ bool operator!=(const mat33 &other) const {
            return !(*this == other);
        }

        // negative
        _CPU_AND_GPU_CODE_ mat33 operator-() const {
            T m[9];
            m[0] = -mat[0];
            m[1] = -mat[1];
            m[2] = -mat[2];
            m[3] = -mat[3];
            m[4] = -mat[4];
            m[5] = -mat[5];
            m[6] = -mat[6];
            m[7] = -mat[7];
            m[8] = -mat[8];
            return mat33(m);
        }

        // +
        _CPU_AND_GPU_CODE_ void operator+=(T x){
            mat[0] += x;
            mat[1] += x;
            mat[2] += x;
            mat[3] += x;
            mat[4] += x;
            mat[5] += x;
            mat[6] += x;
            mat[7] += x;
            mat[8] += x;
        }

        _CPU_AND_GPU_CODE_ void operator+=(const mat33 &other){
            mat[0] += other[0];
            mat[1] += other[1];
            mat[2] += other[2];
            mat[3] += other[3];
            mat[4] += other[4];
            mat[5] += other[5];
            mat[6] += other[6];
            mat[7] += other[7];
            mat[8] += other[8];
        }

        _CPU_AND_GPU_CODE_ friend mat33 operator+(const mat33 &lhs, const mat33 &rhs){
            mat33 result(lhs);
            result += rhs;
            return result;
        }

        // -
        _CPU_AND_GPU_CODE_ void operator-=(T x){
            mat[0] -= x;
            mat[1] -= x;
            mat[2] -= x;
            mat[3] -= x;
            mat[4] -= x;
            mat[5] -= x;
            mat[6] -= x;
            mat[7] -= x;
            mat[8] -= x;
        }

        _CPU_AND_GPU_CODE_ void operator-=(const mat33 &other){
            mat[0] -= other[0];
            mat[1] -= other[1];
            mat[2] -= other[2];
            mat[3] -= other[3];
            mat[4] -= other[4];
            mat[5] -= other[5];
            mat[6] -= other[6];
            mat[7] -= other[7];
            mat[8] -= other[8];
        }

        _CPU_AND_GPU_CODE_ friend mat33 operator-(const mat33 &lhs, const mat33 &rhs){
            mat33 result(lhs);
            result -= rhs;
            return result;
        }

        // *
        _CPU_AND_GPU_CODE_ void operator*=(T x){
            mat[0] *= x;
            mat[1] *= x;
            mat[2] *= x;
            mat[3] *= x;
            mat[4] *= x;
            mat[5] *= x;
            mat[6] *= x;
            mat[7] *= x;
            mat[8] *= x;
        }

        _CPU_AND_GPU_CODE_ void operator*=(const mat33 &other){
            mat[0] *= other[0];
            mat[1] *= other[1];
            mat[2] *= other[2];
            mat[3] *= other[3];
            mat[4] *= other[4];
            mat[5] *= other[5];
            mat[6] *= other[6];
            mat[7] *= other[7];
            mat[8] *= other[8];
        }

        _CPU_AND_GPU_CODE_ friend mat33 operator*(const mat33 &m, T x){
            mat33 result(m);
            result *= x;
            return result;
        }

        _CPU_AND_GPU_CODE_ friend mat33 operator*(T x, const mat33 &m){
            mat33 result(m);
            result *= x;
            return result;
        }

        _CPU_AND_GPU_CODE_ friend mat33 operator*(const mat33 &lhs, const mat33 &rhs){
            mat33 result(lhs);
            result *= rhs;
            return result;
        }

        _CPU_AND_GPU_CODE_ friend vec3<T> operator*(const mat33 &m, const vec3<T> &v){
            vec3<T> result;
            result[0] = m(0,0)*v[0] + m(0,1)*v[1] + m(0,2)*v[2];
            result[1] = m(1,0)*v[0] + m(1,1)*v[1] + m(1,2)*v[2];
            result[2] = m(2,0)*v[0] + m(2,1)*v[1] + m(2,2)*v[2];
            return result;
        }

        _CPU_AND_GPU_CODE_ friend vec3<T> operator*(const vec3<T> &v, const mat33 &m){
            vec3<T> result;
            result[0] = m(0,0)*v[0] + m(1,0)*v[1] + m(2,0)*v[2];
            result[1] = m(0,1)*v[0] + m(1,1)*v[1] + m(2,1)*v[2];
            result[2] = m(0,2)*v[0] + m(1,2)*v[1] + m(2,2)*v[2];
            return result;
        }

        _CPU_AND_GPU_CODE_ friend mat33 matmul(const mat33 &lhs, const mat33 &rhs){
            mat33 result;
            result._m00 = lhs._m00*rhs._m00 + lhs._m01*rhs._m10 + lhs._m02*rhs._m20;
            result._m01 = lhs._m00*rhs._m01 + lhs._m01*rhs._m11 + lhs._m02*rhs._m21;	
            result._m02 = lhs._m00*rhs._m02 + lhs._m01*rhs._m12 + lhs._m02*rhs._m22;
            result._m10 = lhs._m10*rhs._m00 + lhs._m11*rhs._m10 + lhs._m12*rhs._m20;	
            result._m11 = lhs._m10*rhs._m01 + lhs._m11*rhs._m11 + lhs._m12*rhs._m21;	
            result._m12 = lhs._m10*rhs._m02 + lhs._m11*rhs._m12 + lhs._m12*rhs._m22;
            result._m20 = lhs._m20*rhs._m00 + lhs._m21*rhs._m10 + lhs._m22*rhs._m20;	
            result._m21 = lhs._m20*rhs._m01 + lhs._m21*rhs._m11 + lhs._m22*rhs._m21;	
            result._m22 = lhs._m20*rhs._m02 + lhs._m21*rhs._m12 + lhs._m22*rhs._m22;
            
            return result;
        }

        // /
        _CPU_AND_GPU_CODE_ bool all() const {
            for(size_t i = 0; i < 4; i++)
                if(mat[i] == 0) return false;
                
            return true;
        }

        _CPU_AND_GPU_CODE_ void operator/=(T x){
            assert(x != 0);
            mat[0] /= x;
            mat[1] /= x;
            mat[2] /= x;
            mat[3] /= x;
            mat[4] /= x;
            mat[5] /= x;
            mat[6] /= x;
            mat[7] /= x;
            mat[8] /= x;
        }

        _CPU_AND_GPU_CODE_ void operator/=(const mat33 &other){
            assert(other.all());
            mat[0] /= other[0];
            mat[1] /= other[1];
            mat[2] /= other[2];
            mat[3] /= other[3];
            mat[4] /= other[4];
            mat[5] /= other[5];
            mat[6] /= other[6];
            mat[7] /= other[7];
            mat[8] /= other[8];
        }

        _CPU_AND_GPU_CODE_ friend mat33 operator/(const mat33 &lhs, const mat33 &rhs){
            mat33 result(lhs);
            result /= rhs;
            return result;
        }

        // trace
        _CPU_AND_GPU_CODE_ T trace() const {
            return (_m00 + _m11 + _m22);
        }

        // determinant
        // http://www.euclideanspace.com/maths/algebra/matrix/functions/determinant/threeD/index.htm
        _CPU_AND_GPU_CODE_ double det() const {
            double det_ ;
            det_ = 
              _m00*_m11*_m22
            - _m00*_m21*_m12
            + _m10*_m21*_m02
            - _m10*_m01*_m22
            + _m20*_m01*_m12
            - _m20*_m11*_m02;
            return det_;
        }

        // inverse
        // http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/threeD/index.htm
        _CPU_AND_GPU_CODE_ mat33 getInv() const{
            double det_ = det();
            assert(det_ != 0);
            T idet_ = static_cast<T>(1.0/det_);

            mat33 inv_;

            inv_._m00 = _m11*_m22 - _m12*_m21;
            inv_._m01 = _m02*_m21 - _m01*_m22;
            inv_._m02 = _m01*_m12 - _m02*_m11;
            inv_._m10 = _m12*_m20 - _m10*_m22;
            inv_._m11 = _m00*_m22 - _m02*_m20;
            inv_._m12 = _m02*_m10 - _m00*_m12;
            inv_._m20 = _m10*_m21 - _m11*_m20;
            inv_._m21 = _m01*_m20 - _m00*_m21;
            inv_._m22 = _m00*_m11 - _m01*_m10;

            return inv_*idet_;
        }

        _CPU_AND_GPU_CODE_ mat33 &inv(){
            *this = getInv();
            return *this;
        }

        // transpose
        _CPU_AND_GPU_CODE_ mat33 getTranspose() const{
            T transpose_[9];
            transpose_[0] = _m00;
            transpose_[1] = _m10;
            transpose_[2] = _m20;
            transpose_[3] = _m01;
            transpose_[4] = _m11;
            transpose_[5] = _m21;
            transpose_[6] = _m02;
            transpose_[7] = _m12;
            transpose_[8] = _m22;

            return mat33(transpose_);
        }

        _CPU_AND_GPU_CODE_ mat33 &transpose(){
            *this = getTranspose();
            return *this;
        }

        // row / col
        _CPU_AND_GPU_CODE_ vec3<T> col(const uint c) const {
            assert(c < 3);
            vec3<T> result;
            if(c == 0){
                result = vec3<T>(_m00, _m10, _m20);
                return result;
            } 
            if(c == 1){
                result = vec3<T>(_m01, _m11, _m21);
                return result;
            }
            if(c == 2){
                result = vec3<T>(_m02, _m12, _m22);
                return result;
            }
        }

        _CPU_AND_GPU_CODE_ vec3<T> row(const uint r) const {
            assert(r < 3);
            vec3<T> result;
            if(r == 0){
                result = vec3<T>(_m00, _m01, _m02);
                return result;
            } 
            if(r == 1){
                result = vec3<T>(_m10, _m11, _m12);
                return result;
            }
            if(r == 2){
                result = vec3<T>(_m20, _m21, _m22);
                return result;
            }
        }

        _CPU_AND_GPU_CODE_ T *getData(){
            return mat;
        }

        // per-element func
        _CPU_AND_GPU_CODE_ mat33<float> frac() const  {
        return mat33(Math::frac(mat[0]), Math::frac(mat[1]), Math::frac(mat[2]), Math::frac(mat[3]), Math::frac(mat[4]), Math::frac(mat[5]), Math::frac(mat[6]), Math::frac(mat[7]), Math::frac(mat[8]));
        }
        
        _CPU_AND_GPU_CODE_ mat33 round() const  {
        return mat33(Math::round(mat[0]), Math::round(mat[1]), Math::round(mat[2]), Math::round(mat[3]), Math::round(mat[4]), Math::round(mat[5]), Math::round(mat[6]), Math::round(mat[7]), Math::round(mat[8]));
        }
        
        _CPU_AND_GPU_CODE_ mat33 ceil() const  {
        return mat33(Math::ceil(mat[0]), Math::ceil(mat[1]), Math::ceil(mat[2]), Math::ceil(mat[3]), Math::ceil(mat[4]), Math::ceil(mat[5]), Math::ceil(mat[6]), Math::ceil(mat[7]), Math::ceil(mat[8]));
        }
        
        _CPU_AND_GPU_CODE_ mat33 floor() const  {
        return mat33(Math::floor(mat[0]), Math::floor(mat[1]), Math::floor(mat[2]), Math::floor(mat[3]), Math::floor(mat[4]), Math::floor(mat[5]), Math::floor(mat[6]), Math::floor(mat[7]), Math::floor(mat[8]));
        }
        
        _CPU_AND_GPU_CODE_ mat33 abs() const  {
        return mat33(Math::abs(mat[0]), Math::abs(mat[1]), Math::abs(mat[2]), Math::abs(mat[3]), Math::abs(mat[4]), Math::abs(mat[5]), Math::abs(mat[6]), Math::abs(mat[7]), Math::abs(mat[8]));
        }

    }; // class mat33

    template<typename T> const uint mat33<T>::Cols = 3;
    template<typename T> const uint mat33<T>::Rows = 3;
    template<typename T> const uint mat33<T>::Num = 9; 
    
    // in / out
    template <typename T>
    std::ostream &operator<<(std::ostream &out, const mat33<T> &m){
        out << "[" << m(0,0) << " " << m(0,1) << " " << m(0,2) << "]" << std::endl;
        out << "[" << m(1,0) << " " << m(1,1) << " " << m(1,2) << "]" << std::endl;
        out << "[" << m(2,0) << " " << m(2,1) << " " << m(2,2) << "]" << std::endl;
        return out;
    }
        
    template <typename T>
    std::istream &operator>>(std::istream &in, mat33<T> &m){
        in >> m(0,0) >> m(0,1) >> m(0,2)
           >> m(1,0) >> m(1,1) >> m(1,2) 
           >> m(2,0) >> m(2,1) >> m(2,2);
        if(!in){
            m = mat33<T>();
        }
        return in;
    }

namespace Math
{
    // for mat33

    template <typename T>
    _CPU_AND_GPU_CODE_ bool floatEqual(const mat33<T> &lhs, const mat33<T> &rhs){
        return floatEqual(lhs[0], rhs[0]) && 
               floatEqual(lhs[1], rhs[1]) &&
               floatEqual(lhs[2], rhs[2]) &&
               floatEqual(lhs[3], rhs[3]) &&
               floatEqual(lhs[4], rhs[4]) &&
               floatEqual(lhs[5], rhs[5]) &&
               floatEqual(lhs[6], rhs[6]) &&
               floatEqual(lhs[7], rhs[7]) &&
               floatEqual(lhs[8], rhs[8]);
    }

    // max min
    template <typename T>
    _CPU_AND_GPU_CODE_ mat33<T> max(const mat33<T> &m, T x) {
        return mat33<T>(max(m[0], x),
                        max(m[1], x),
                        max(m[2], x),
                        max(m[3], x),
                        max(m[4], x),
                        max(m[5], x),
                        max(m[6], x),
                        max(m[7], x),
                        max(m[8], x));
    }
    
    template <typename T>
    _CPU_AND_GPU_CODE_ mat33<T> max(const mat33<T> &lhs, const mat33<T> &rhs) {
        return mat33<T>(max(lhs[0], rhs[0]),
                        max(lhs[1], rhs[1]),
                        max(lhs[2], rhs[2]),
                        max(lhs[3], rhs[3]),
                        max(lhs[4], rhs[4]),
                        max(lhs[5], rhs[5]),
                        max(lhs[6], rhs[6]),
                        max(lhs[7], rhs[7]),
                        max(lhs[8], rhs[8]));
    }
    
    template <typename T>
    _CPU_AND_GPU_CODE_ mat33<T> min(const mat33<T> &m, T x) {
        return mat33<T>(min(m[0], x),
                        min(m[1], x),
                        min(m[2], x),
                        min(m[3], x),
                        min(m[4], x),
                        min(m[5], x),
                        min(m[6], x),
                        min(m[7], x),
                        min(m[8], x));
    }
    
    template <typename T>
    _CPU_AND_GPU_CODE_ mat33<T> min(const mat33<T> &lhs, const mat33<T> &rhs) {
        return mat33<T>(min(lhs[0], rhs[0]),
                        min(lhs[1], rhs[1]),
                        min(lhs[2], rhs[2]),
                        min(lhs[3], rhs[3]),
                        min(lhs[4], rhs[4]),
                        min(lhs[5], rhs[5]),
                        min(lhs[6], rhs[6]),
                        min(lhs[7], rhs[7]),
                        min(lhs[8], rhs[8]));
    }

    
    // per-element func
    template <typename T>
    _CPU_AND_GPU_CODE_ mat33<float> frac(const mat33<T> &mat) {
    return mat.frac();
    }

    template <typename T>
    _CPU_AND_GPU_CODE_ mat33<T> round(const mat33<T> &mat) {
    return mat.round();
    }
    
    template <typename T>
    _CPU_AND_GPU_CODE_ mat33<T> ceil(const mat33<T> &mat) {
    return mat.ceil();
    }
    
    template <typename T>
    _CPU_AND_GPU_CODE_ mat33<T> floor(const mat33<T> &mat) {
    return mat.floor();
    }
    
    template <typename T>
    _CPU_AND_GPU_CODE_ mat33<T> abs(const mat33<T> &mat) {
    return mat.abs();
    }

} // namespace Math

} // namespace LLib

#endif // _LL_MAT33_H