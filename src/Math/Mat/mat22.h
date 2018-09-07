#ifndef _LL_MAT22_H_
#define _LL_MAT22_H_

#include "../../Utility/utility.h"
#include "../Vec/vec_header.h"

namespace LLib
{
    // row-like
    // <pre>
    //    0  1
    //    2  3
    // <pre>
    template <typename T>
    class mat22
    {
    public:
        // data
        using ValueType = T;

        union{
            T mat[4];
            T mat2[2][2];
            struct{
                T
                _m00, _m01,
                _m10, _m11;
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
        _CPU_AND_GPU_CODE_ static mat22 zeros(){
            return mat22(0, 0, 
                         0, 0);
        }

        _CPU_AND_GPU_CODE_ static mat22 identity(){
            return mat22(1, 0, 
                         0, 1);
        }

        _CPU_AND_GPU_CODE_ static mat22 full(T x){
            return mat22(x);
        }

        _CPU_AND_GPU_CODE_ static mat22 diag(T x){
            return mat22(x, 0, 
                         0, x);
        }

        _CPU_AND_GPU_CODE_ static mat22 diag(T x, T y){
            return mat22(x, 0, 
                         0, y);
        }

        template <typename U>
        _CPU_AND_GPU_CODE_ static mat22 diag(const vec2<U> &v){
            return mat22(v.x, 0, 0, v.y);
        }

        // set func
        _CPU_AND_GPU_CODE_ void setIdentity(){
            _m00 = 1; _m01 = 0;
            _m10 = 0; _m11 = 1;
        }

        _CPU_AND_GPU_CODE_ void setZeros(){
            _m00 = 0; _m01 = 0;
            _m10 = 0; _m11 = 0;
        }

        _CPU_AND_GPU_CODE_ void setFull(T x){
            _m00 = x; _m01 = x;
            _m10 = x; _m11 = x;
        }

        _CPU_AND_GPU_CODE_ void setDiag(T x){
            _m00 = x; _m01 = 0;
            _m10 = 0; _m11 = x;
        }

        _CPU_AND_GPU_CODE_ void setDiag(T x, T y){
            _m00 = x; _m01 = 0;
            _m10 = 0; _m11 = y;
        }

        _CPU_AND_GPU_CODE_ void setDiag(const vec2<T> &v){
            _m00 = v.x; _m01 = 0;
            _m10 = 0;   _m11 = v.y;
       }


        // constructor
        _CPU_AND_GPU_CODE_ mat22(T x = 0){
            mat[0] = mat[1] = mat[2] = mat[3] = x;
        }

        template <typename U>
        _CPU_AND_GPU_CODE_ mat22(const U *m){
                mat[0] = m[0];
                mat[1] = m[1];
                mat[2] = m[2];
                mat[3] = m[3];
        }

        _CPU_AND_GPU_CODE_ mat22(T m00, T m01, T m10, T m11){
            _m00 = m00; _m01 = m01;
            _m10 = m10; _m11 = m11;
        }

        template <typename U>
        _CPU_AND_GPU_CODE_ mat22(const mat22<U> &other){
            _m00 = other._m00;
            _m01 = other._m01;
            _m10 = other._m10;
            _m11 = other._m11;
        }
        
        // convert type
        template <typename U>
        _CPU_AND_GPU_CODE_ mat22<U> toType() const {
            return mat22<U>(*this);
        }

        // access
        _CPU_AND_GPU_CODE_ T &at(const uint i){
            assert(i < 4);
            return mat[i];
        }

        _CPU_AND_GPU_CODE_ const T &at(const uint i) const {
            assert(i < 4);
            return mat[i];
        }

        _CPU_AND_GPU_CODE_ T &at(const uint i, const uint j){
            assert(i < 2 && j < 2);
            return mat2[i][j];
        }

        _CPU_AND_GPU_CODE_ const T &at(const uint i, const uint j) const {
            assert(i < 2 && j < 2);
            return mat2[i][j];
        }

        _CPU_AND_GPU_CODE_ T &operator()(const uint i, const uint j){
            assert(i < 2 && j < 2);
            return mat2[i][j];
        }

        _CPU_AND_GPU_CODE_ const T &operator()(const uint i, const uint j) const {
            assert(i < 2 && j < 2);
            return mat2[i][j];
        }

        _CPU_AND_GPU_CODE_ T &operator[](const uint i){
            assert(i < 4);
            return mat[i];
        }

        _CPU_AND_GPU_CODE_ const T &operator[](const uint i) const {
            assert(i < 4);
            return mat[i];
        }

        // // == / != 
        _CPU_AND_GPU_CODE_ bool operator==(const mat22 &other) const {
            for(size_t i = 0; i < 4; i++){
                if(mat[i] != other[i]) return false;
            }
            return true;
        }

        _CPU_AND_GPU_CODE_ bool operator!=(const mat22 &other) const {
            return !(*this == other);
        }

        // negative
        _CPU_AND_GPU_CODE_ mat22 operator-(){
            T m[4];
            m[0] = -mat[0];
            m[1] = -mat[1];
            m[2] = -mat[2];
            m[3] = -mat[3];
            return mat22(m);
        }

        // +
        _CPU_AND_GPU_CODE_ void operator+=(T x){
            mat[0] += x;
            mat[1] += x;
            mat[2] += x;
            mat[3] += x;
        }

        _CPU_AND_GPU_CODE_ void operator+=(const mat22 &other){
            mat[0] += other[0];
            mat[1] += other[1];
            mat[2] += other[2];
            mat[3] += other[3];
        }

        _CPU_AND_GPU_CODE_ friend mat22 operator+(const mat22 &lhs, const mat22 &rhs){
            mat22 result(lhs);
            result += rhs;
            return result;
        }

        // -
        _CPU_AND_GPU_CODE_ void operator-=(T x){
            mat[0] -= x;
            mat[1] -= x;
            mat[2] -= x;
            mat[3] -= x;
        }

        _CPU_AND_GPU_CODE_ void operator-=(const mat22 &other){
            mat[0] -= other[0];
            mat[1] -= other[1];
            mat[2] -= other[2];
            mat[3] -= other[3];
        }

        _CPU_AND_GPU_CODE_ friend mat22 operator-(const mat22 &lhs, const mat22 &rhs){
            mat22 result(lhs);
            result -= rhs;
            return result;
        }

        // *
        _CPU_AND_GPU_CODE_ void operator*=(T x){
            mat[0] *= x;
            mat[1] *= x;
            mat[2] *= x;
            mat[3] *= x;
        }

        _CPU_AND_GPU_CODE_ void operator*=(const mat22 &other){
            mat[0] *= other[0];
            mat[1] *= other[1];
            mat[2] *= other[2];
            mat[3] *= other[3];
        }

        friend mat22 operator*(T x, const mat22 &m){
            mat22 result(m);
            result *= x;
            return result;
        }

        friend mat22 operator*(const mat22 &m, T x){
            mat22 result(m);
            result *= x;
            return result;
        }

        friend vec2<T> operator*(const mat22 &m, const vec2<T> &v){
            vec2<T> result;
            result[0] = m(0,0)*v[0] + m(0,1)*v[1];
            result[1] = m(1,0)*v[0] + m(1,1)*v[1];
            return result;
        }

        friend vec2<T> operator*(const vec2<T> &v, const mat22 &m){
            vec2<T> result;
            result[0] = m(0,0)*v[0] + m(1,0)*v[1];
            result[1] = m(0,1)*v[0] + m(1,1)*v[1];
            return result;
        }

        friend mat22 operator*(const mat22 &lhs, const mat22 &rhs){
            mat22 result(lhs);
            result *= rhs;
            return result;
        }

        friend mat22 matmul(const mat22 &lhs, const mat22 &rhs){
            mat22 result;
            result._m00 = lhs._m00*rhs._m00 + lhs._m01*rhs._m10;
            result._m01 = lhs._m00*rhs._m01 + lhs._m01*rhs._m11;
            result._m10 = lhs._m10*rhs._m00 + lhs._m11*rhs._m10;
            result._m11 = lhs._m10*rhs._m01 + lhs._m11*rhs._m11;
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
        }

        _CPU_AND_GPU_CODE_ void operator/=(const mat22 &other){
            assert(other.all());
            mat[0] /= other[0];
            mat[1] /= other[1];
            mat[2] /= other[2];
            mat[3] /= other[3];
        }

        _CPU_AND_GPU_CODE_ friend mat22 operator/(const mat22 &lhs, const mat22 &rhs){
            mat22 result(lhs);
            result /= rhs;
            return result;
        }

        // trace
        _CPU_AND_GPU_CODE_ T trace() const {
            return (_m00 + _m11);
        }

        // determinant
        // http://www.euclideanspace.com/maths/algebra/matrix/functions/determinant/twoD/index.htm
        _CPU_AND_GPU_CODE_ double det() const {
            double det_;
            det_ = 
              _m00*_m11 
            - _m01*_m10;
            return det_;
        }

        // inverse
        // http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/twoD/index.htm
        _CPU_AND_GPU_CODE_ mat22 getInv() const{
            double det_ = det();
            assert(det_ != 0);
            T idet_ = static_cast<T>(1.0/det_);

            mat22 inv_;

            inv_._m00 = _m11;
            inv_._m01 = -_m01;
            inv_._m10 = -_m10;
            inv_._m11 = _m00;


            return inv_*idet_;
        }

        _CPU_AND_GPU_CODE_ mat22 &inv(){
            *this = getInv();
            return *this;
        }

        // transpose
        _CPU_AND_GPU_CODE_ mat22 getTranspose() const{
            T transpose_[4];
            transpose_[0] = _m00;
            transpose_[1] = _m10;
            transpose_[2] = _m01;
            transpose_[3] = _m11;

            return mat22(transpose_);
        }

        _CPU_AND_GPU_CODE_ mat22 &transpose(){
            *this = getTranspose();
            return *this;
        }

        // row / col
        _CPU_AND_GPU_CODE_ vec2<T> col(const uint c) const {
            assert(c < 2);
            vec2<T> result;
            if(c == 0){
                result = vec2<T>(_m00, _m10);
            } else {
                result = vec2<T>(_m01, _m11);
            }
            return result;
        }

        _CPU_AND_GPU_CODE_ vec2<T> row(const uint r) const {
            assert(r < 2);
            vec2<T> result;
            if(r == 0){
                result = vec2<T>(_m00, _m01);
            } else {
                result = vec2<T>(_m10, _m11);
            }
            return result;
        }

        _CPU_AND_GPU_CODE_ T *getData(){
            return mat;
        }

        // per-element func
        _CPU_AND_GPU_CODE_ mat22<float> frac() const {
            return mat22<float>(Math::frac(mat[0]), Math::frac(mat[1]), Math::frac(mat[2]), Math::frac(mat[3]));
        }

        _CPU_AND_GPU_CODE_ mat22 round() const {
            return mat22(Math::round(mat[0]), Math::round(mat[1]), Math::round(mat[2]), Math::round(mat[3]));
        }
        
        _CPU_AND_GPU_CODE_ mat22 ceil() const {
            return mat22(Math::ceil(mat[0]), Math::ceil(mat[1]), Math::ceil(mat[2]), Math::ceil(mat[3]));
        }
        
        _CPU_AND_GPU_CODE_ mat22 floor() const {
            return mat22(Math::floor(mat[0]), Math::floor(mat[1]), Math::floor(mat[2]), Math::floor(mat[3]));
        }
        
        _CPU_AND_GPU_CODE_ mat22 abs() const {
            return mat22(Math::abs(mat[0]), Math::abs(mat[1]), Math::abs(mat[2]), Math::abs(mat[3]));
        }

    }; // class mat22

    template<typename T> const uint mat22<T>::Cols = 2;
    template<typename T> const uint mat22<T>::Rows = 2;
    template<typename T> const uint mat22<T>::Num = 4;    

    // in / out
    template <typename T>
    std::ostream &operator<<(std::ostream &out, const mat22<T> &m){
        out << "[" << m(0,0) << " " << m(0,1) << "]" << std::endl;
        out << "[" << m(1,0) << " " << m(1,1) << "]" << std::endl;
        return out;
    }

    template <typename T>
    std::istream &operator>>(std::istream &in, mat22<T> &m){
        in >> m(0,0) >> m(0,1) >> m(1,0) >> m(1,1);
        if(!in){
            m = mat22<T>();
        }
        return in;
    }

namespace Math
{
    // for mat22

    template <typename T>
    _CPU_AND_GPU_CODE_ bool floatEqual(const mat22<T> &lhs, const mat22<T> &rhs){
        return floatEqual(lhs[0], rhs[0]) && 
               floatEqual(lhs[1], rhs[1]) &&
               floatEqual(lhs[2], rhs[2]) &&
               floatEqual(lhs[3], rhs[3]);
    }

    // max min
    template <typename T, typename U>
    _CPU_AND_GPU_CODE_ mat22<T> max(const mat22<T> &m, U x) {
        return mat22<T>(max(m[0], x),
                        max(m[1], x),
                        max(m[2], x),
                        max(m[3], x));
    }
    
    template <typename T>
    _CPU_AND_GPU_CODE_ mat22<T> max(const mat22<T> &lhs, const mat22<T> &rhs) {
        return mat22<T>(max(lhs[0], rhs[0]),
                        max(lhs[1], rhs[1]),
                        max(lhs[2], rhs[2]),
                        max(lhs[3], rhs[3]));
    }
    
    template <typename T, typename U>
    _CPU_AND_GPU_CODE_ mat22<T> min(const mat22<T> &m, U x) {
        return mat22<T>(min(m[0], x),
                        min(m[1], x),
                        min(m[2], x),
                        min(m[3], x));
    }
    
    template <typename T>
    _CPU_AND_GPU_CODE_ mat22<T> min(const mat22<T> &lhs, const mat22<T> &rhs) {
    return mat22<T>(min(lhs[0], rhs[0]),
                    min(lhs[1], rhs[1]),
                    min(lhs[2], rhs[2]),
                    min(lhs[3], rhs[3]));
    }
    
    // per-element func
    template <typename T>
    _CPU_AND_GPU_CODE_ mat22<float> frac(const mat22<T> &mat) {
    return mat.frac();
    }

    template <typename T>
    _CPU_AND_GPU_CODE_ mat22<T> round(const mat22<T> &mat) {
    return mat.round();
    }
    
    template <typename T>
    _CPU_AND_GPU_CODE_ mat22<T> ceil(const mat22<T> &mat) {
    return mat.ceil();
    }
    
    template <typename T>
    _CPU_AND_GPU_CODE_ mat22<T> floor(const mat22<T> &mat) {
    return mat.floor();
    }
    
    template <typename T>
    _CPU_AND_GPU_CODE_ mat22<T> abs(const mat22<T> &mat) {
    return mat.abs();
    }
    
} // namespace Math


} // namespace LLib

#endif // _LL_MAT22_H
