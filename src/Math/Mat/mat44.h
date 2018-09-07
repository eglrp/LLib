#ifndef _LL_MAT44_H_
#define _LL_MAT44_H_

#include "../../Utility/utility.h"
#include "../Vec/vec_header.h"

namespace LLib
{
    // row-like
    // <pre>
    //    0  1  2  3
    //    4  5  6  7
    //    8  9  10 11
    //    12 13 14 15
    // <pre>
    template <typename T>
    class mat44
    {
    public:
        // data
        using ValueType = T;

        union{
            T mat[16];
            T mat2[4][4];
            struct{
                T
                _m00, _m01, _m02, _m03,
                _m10, _m11, _m12, _m13,
                _m20, _m21, _m22, _m23,
                _m30, _m31, _m32, _m33;
            };
        };

        // dimension
        static const uint Cols;
        static const uint Rows;
        static const uint Num;
        static bool isSquare(){
            return true;
        }

        _CPU_AND_GPU_CODE_ static mat44 zeros(){
            return mat44(0, 0, 0, 0, 
                         0, 0, 0, 0,
                         0, 0, 0, 0,
                         0, 0, 0, 0);
        }

        _CPU_AND_GPU_CODE_ static mat44 identity(){
            return mat44(1, 0, 0, 0, 
                         0, 1, 0, 0,
                         0, 0, 1, 0,
                         0, 0, 0, 1);
        }

        _CPU_AND_GPU_CODE_ static mat44 full(T x){
            return mat44(x);
        }

        _CPU_AND_GPU_CODE_ static mat44 diag(T x){
            return mat44(x, 0, 0, 0,
                         0, x, 0, 0,
                         0, 0, x, 0,
                         0, 0, 0, x);
        }
 
        _CPU_AND_GPU_CODE_ static mat44 diag(T x, T y, T z, T w){
            return mat44(x, 0, 0, 0, 
                         0, y, 0, 0,
                         0, 0, z, 0,
                         0, 0, 0, w);
        }

        template <typename U>
        _CPU_AND_GPU_CODE_ static mat44 diag(const vec4<U> &v){
            return mat44(v.x, 0,   0,   0,
                         0,   v.y, 0,   0,
                         0,   0,   v.z, 0,
                         0,   0,   0,   v.w);
        }

        // set func
        _CPU_AND_GPU_CODE_ void setIdentity(){
            _m00 = 1; _m01 = 0; _m02 = 0; _m03 = 0;
            _m10 = 0; _m11 = 1; _m12 = 0; _m13 = 0;
            _m20 = 0; _m21 = 0; _m22 = 1; _m23 = 0;
            _m30 = 0; _m31 = 0; _m32 = 0; _m33 = 1;
        }

        _CPU_AND_GPU_CODE_ void setZeros(){
            _m00 = 0; _m01 = 0; _m02 = 0; _m03 = 0;
            _m10 = 0; _m11 = 0; _m12 = 0; _m13 = 0;
            _m20 = 0; _m21 = 0; _m22 = 0; _m23 = 0;
            _m30 = 0; _m31 = 0; _m32 = 0; _m33 = 0;
        }

        _CPU_AND_GPU_CODE_ void setFull(T x){
            _m00 = x; _m01 = x; _m02 = x; _m03 = x;
            _m10 = x; _m11 = x; _m12 = x; _m13 = x;
            _m20 = x; _m21 = x; _m22 = x; _m23 = x;
            _m30 = x; _m31 = x; _m32 = x; _m33 = x;
        }

        _CPU_AND_GPU_CODE_ void setDiag(T x){
            _m00 = x; _m01 = 0; _m02 = 0; _m03 = 0;
            _m10 = 0; _m11 = x; _m12 = 0; _m13 = 0;
            _m20 = 0; _m21 = 0; _m22 = x; _m23 = 0;
            _m30 = 0; _m31 = 0; _m32 = 0; _m33 = x;
        }

        _CPU_AND_GPU_CODE_ void setDiag(T x, T y, T z, T w){
            _m00 = x; _m01 = 0; _m02 = 0; _m03 = 0;
            _m10 = 0; _m11 = y; _m12 = 0; _m13 = 0;
            _m20 = 0; _m21 = 0; _m22 = z; _m23 = 0;
            _m30 = 0; _m31 = 0; _m32 = 0; _m33 = w;
        }

        _CPU_AND_GPU_CODE_ void setDiag(const vec4<T> &v){
            _m00 = v.x; _m01 = 0;   _m02 = 0;   _m03 = 0;
            _m10 = 0;   _m11 = v.y; _m12 = 0;   _m13 = 0;
            _m20 = 0;   _m21 = 0;   _m22 = v.z; _m23 = 0;
            _m30 = 0;   _m31 = 0;   _m32 = 0;   _m33 = v.w;
       }


        // constructor
        _CPU_AND_GPU_CODE_ mat44(T x = 0){
            mat[0] = mat[1] = mat[2] = mat[3] = mat[4] = mat[5] = mat[6] = mat[7] = mat[8] = mat[9] = mat[10] = mat[11] = mat[12] = mat[13] = mat[14] = mat[15] = x;
        }

        template <typename U>
        _CPU_AND_GPU_CODE_ mat44(const U *m){
                mat[0]  = m[0];
                mat[1]  = m[1];
                mat[2]  = m[2];
                mat[3]  = m[3];
                mat[4]  = m[4];
                mat[5]  = m[5];
                mat[6]  = m[6];
                mat[7]  = m[7];
                mat[8]  = m[8];
                mat[9]  = m[9];
                mat[10] = m[10];
                mat[11] = m[11];
                mat[12] = m[12];
                mat[13] = m[13];
                mat[14] = m[14];
                mat[15] = m[15];
        }

        _CPU_AND_GPU_CODE_ mat44(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22, T m23, T m30, T m31, T m32, T m33){
            _m00 = m00; _m01 = m01; _m02 = m02; _m03 = m03;
            _m10 = m10; _m11 = m11; _m12 = m12; _m13 = m13;
            _m20 = m20; _m21 = m21; _m22 = m22; _m23 = m23;
            _m30 = m30; _m31 = m31; _m32 = m32; _m33 = m33; 
        }

        template <typename U>
        _CPU_AND_GPU_CODE_ mat44(const mat44<U> &other){
            _m00 = other._m00;
            _m01 = other._m01;
            _m02 = other._m02;
            _m03 = other._m03;
            _m10 = other._m10;
            _m11 = other._m11;
            _m12 = other._m12;
            _m13 = other._m13;
            _m20 = other._m20;
            _m21 = other._m21;
            _m22 = other._m22;
            _m23 = other._m23;
            _m30 = other._m30;
            _m31 = other._m31;
            _m32 = other._m32;
            _m33 = other._m33;
        }

        // convert type
        template <typename U>
        _CPU_AND_GPU_CODE_ mat44<U> toType() const {
            return mat44<U>(*this);
        }

        // access
        _CPU_AND_GPU_CODE_ T &at(const uint i, const uint j){
            assert(i < 4 && j < 4);
            return mat2[i][j];
        }

        _CPU_AND_GPU_CODE_ const T &at(const uint i, const uint j) const {
            assert(i < 4 && j < 4);
            return mat2[i][j];
        }

        _CPU_AND_GPU_CODE_ T &at(const uint i){
            assert(i < 16);
            return mat[i];
        }

        _CPU_AND_GPU_CODE_ const T &at(const uint i) const {
            assert(i < 16);
            return mat[i];
        }

        _CPU_AND_GPU_CODE_ T &operator()(const uint i, const uint j){
            assert(i < 4 && j < 4);
            return mat2[i][j];
        }

        _CPU_AND_GPU_CODE_ const T &operator()(const uint i, const uint j) const {
            assert(i < 4 && j < 4);
            return mat2[i][j];
        }

        _CPU_AND_GPU_CODE_ T &operator[](const uint i){
            assert(i < 16);
            return mat[i];
        }

        _CPU_AND_GPU_CODE_ const T &operator[](const uint i) const {
            assert(i < 16);
            return mat[i];
        }

        // == / !=
        _CPU_AND_GPU_CODE_ bool operator==(const mat44 &other) const {
            for(size_t i = 0; i < 16; i++){
                if(mat[i] != other[i]) return false;
            }
            return true;
        }

        _CPU_AND_GPU_CODE_ bool operator!=(const mat44 &other) const {
            return !(*this == other);
        }


        // negative
        _CPU_AND_GPU_CODE_ mat44 operator-() const {
            T m[16];
            m[0]  = -mat[0];
            m[1]  = -mat[1];
            m[2]  = -mat[2];
            m[3]  = -mat[3];
            m[4]  = -mat[4];
            m[5]  = -mat[5];
            m[6]  = -mat[6];
            m[7]  = -mat[7];
            m[8]  = -mat[8];
            m[9]  = -mat[9];
            m[10] = -mat[10];
            m[11] = -mat[11];
            m[12] = -mat[12];
            m[13] = -mat[13];
            m[14] = -mat[14];
            m[15] = -mat[15];
            return mat44(m);
        }

        // +
        _CPU_AND_GPU_CODE_ void operator+=(T x){
            mat[0]  += x;
            mat[1]  += x;
            mat[2]  += x;
            mat[3]  += x;
            mat[4]  += x;
            mat[5]  += x;
            mat[6]  += x;
            mat[7]  += x;
            mat[8]  += x;
            mat[9]  += x;
            mat[10] += x;
            mat[11] += x;
            mat[12] += x;
            mat[13] += x;
            mat[14] += x;
            mat[15] += x;
        }

        _CPU_AND_GPU_CODE_ void operator+=(const mat44 &other){
            mat[0]  += other[0];
            mat[1]  += other[1];
            mat[2]  += other[2];
            mat[3]  += other[3];
            mat[4]  += other[4];
            mat[5]  += other[5];
            mat[6]  += other[6];
            mat[7]  += other[7];
            mat[8]  += other[8];
            mat[9]  += other[9];
            mat[10] += other[10];
            mat[11] += other[11];
            mat[12] += other[12];
            mat[13] += other[13];
            mat[14] += other[14];
            mat[15] += other[15];
        }

        _CPU_AND_GPU_CODE_ friend mat44 operator+(const mat44 &lhs, const mat44 &rhs){
            mat44 result(lhs);
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
            mat[9] -= x;
            mat[10] -= x;
            mat[11] -= x;
            mat[12] -= x;
            mat[13] -= x;
            mat[14] -= x;
            mat[15] -= x;
        }

        _CPU_AND_GPU_CODE_ void operator-=(const mat44 &other){
            mat[0]  -= other[0];
            mat[1]  -= other[1];
            mat[2]  -= other[2];
            mat[3]  -= other[3];
            mat[4]  -= other[4];
            mat[5]  -= other[5];
            mat[6]  -= other[6];
            mat[7]  -= other[7];
            mat[8]  -= other[8];
            mat[9]  -= other[9];
            mat[10] -= other[10];
            mat[11] -= other[11];
            mat[12] -= other[12];
            mat[13] -= other[13];
            mat[14] -= other[14];
            mat[15] -= other[15];
        }

        _CPU_AND_GPU_CODE_ friend mat44 operator-(const mat44 &lhs, const mat44 &rhs){
            mat44 result(lhs);
            result -= rhs;
            return result;
        }

        // *
        _CPU_AND_GPU_CODE_ void operator*=(T x){
            mat[0]  *= x;
            mat[1]  *= x;
            mat[2]  *= x;
            mat[3]  *= x;
            mat[4]  *= x;
            mat[5]  *= x;
            mat[6]  *= x;
            mat[7]  *= x;
            mat[8]  *= x;
            mat[9]  *= x;
            mat[10] *= x;
            mat[11] *= x;
            mat[12] *= x;
            mat[13] *= x;
            mat[14] *= x;
            mat[15] *= x;
        }

        _CPU_AND_GPU_CODE_ void operator*=(const mat44 &other){
            mat[0]  *= other[0];
            mat[1]  *= other[1];
            mat[2]  *= other[2];
            mat[3]  *= other[3];
            mat[4]  *= other[4];
            mat[5]  *= other[5];
            mat[6]  *= other[6];
            mat[7]  *= other[7];
            mat[8]  *= other[8];
            mat[9]  *= other[9];
            mat[10] *= other[10];
            mat[11] *= other[11];
            mat[12] *= other[12];
            mat[13] *= other[13];
            mat[14] *= other[14];
            mat[15] *= other[15];
        }

        _CPU_AND_GPU_CODE_ friend mat44 operator*(const mat44 &m, T x){
            mat44 result(m);
            result *= x;
            return result;
        }

        _CPU_AND_GPU_CODE_ friend mat44 operator*(T x, const mat44 &m){
            mat44 result(m);
            result *= x;
            return result;
        }

        _CPU_AND_GPU_CODE_ friend vec4<T> operator*(const mat44 &m, const vec4<T> &v){
            vec4<T> result;
            result[0] = m(0,0)*v[0] + m(0,1)*v[1] + m(0,2)*v[2] + m(0,3)*v[3];
            result[1] = m(1,0)*v[0] + m(1,1)*v[1] + m(1,2)*v[2] + m(1,3)*v[3];
            result[2] = m(2,0)*v[0] + m(2,1)*v[1] + m(2,2)*v[2] + m(2,3)*v[3];
            result[3] = m(3,0)*v[0] + m(3,1)*v[1] + m(3,2)*v[2] + m(3,3)*v[3];
            return result;
        }

        _CPU_AND_GPU_CODE_ friend vec4<T> operator*(const vec4<T> &v, const mat44 &m){
            vec4<T> result;
            result[0] = m(0,0)*v[0] + m(1,0)*v[1] + m(2,0)*v[2] + m(3,0)*v[3];
            result[1] = m(0,1)*v[0] + m(1,1)*v[1] + m(2,1)*v[2] + m(3,1)*v[3];
            result[2] = m(0,2)*v[0] + m(1,2)*v[1] + m(2,2)*v[2] + m(3,2)*v[3];
            result[3] = m(0,3)*v[0] + m(1,3)*v[1] + m(2,3)*v[2] + m(3,3)*v[3];
            return result;
        }

        _CPU_AND_GPU_CODE_ friend mat44 operator*(const mat44 &lhs, const mat44 &rhs){
            mat44 result(lhs);
            result *= rhs;
            return result;
        }

        _CPU_AND_GPU_CODE_ friend mat44 matmul(const mat44 &lhs, const mat44 &rhs){
            mat44 result;
            result._m00 = lhs._m00*rhs._m00 + lhs._m01*rhs._m10 + lhs._m02*rhs._m20 + lhs._m03*rhs._m30;
            result._m01 = lhs._m00*rhs._m01 + lhs._m01*rhs._m11 + lhs._m02*rhs._m21 + lhs._m03*rhs._m31;
            result._m02 = lhs._m00*rhs._m02 + lhs._m01*rhs._m12 + lhs._m02*rhs._m22 + lhs._m03*rhs._m32;
            result._m03 = lhs._m00*rhs._m03 + lhs._m01*rhs._m13 + lhs._m02*rhs._m23 + lhs._m03*rhs._m33;
            result._m10 = lhs._m10*rhs._m00 + lhs._m11*rhs._m10 + lhs._m12*rhs._m20 + lhs._m13*rhs._m30;
            result._m11 = lhs._m10*rhs._m01 + lhs._m11*rhs._m11 + lhs._m12*rhs._m21 + lhs._m13*rhs._m31;
            result._m12 = lhs._m10*rhs._m02 + lhs._m11*rhs._m12 + lhs._m12*rhs._m22 + lhs._m13*rhs._m32;
            result._m13 = lhs._m10*rhs._m03 + lhs._m11*rhs._m13 + lhs._m12*rhs._m23 + lhs._m13*rhs._m33;
            result._m20 = lhs._m20*rhs._m00 + lhs._m21*rhs._m10 + lhs._m22*rhs._m20 + lhs._m23*rhs._m30;
            result._m21 = lhs._m20*rhs._m01 + lhs._m21*rhs._m11 + lhs._m22*rhs._m21 + lhs._m23*rhs._m31;
            result._m22 = lhs._m20*rhs._m02 + lhs._m21*rhs._m12 + lhs._m22*rhs._m22 + lhs._m23*rhs._m32;
            result._m23 = lhs._m20*rhs._m03 + lhs._m21*rhs._m13 + lhs._m22*rhs._m23 + lhs._m23*rhs._m33;
            result._m30 = lhs._m30*rhs._m00 + lhs._m31*rhs._m10 + lhs._m32*rhs._m20 + lhs._m33*rhs._m30;
            result._m31 = lhs._m30*rhs._m01 + lhs._m31*rhs._m11 + lhs._m32*rhs._m21 + lhs._m33*rhs._m31;
            result._m32 = lhs._m30*rhs._m02 + lhs._m31*rhs._m12 + lhs._m32*rhs._m22 + lhs._m33*rhs._m32;
            result._m33 = lhs._m30*rhs._m03 + lhs._m31*rhs._m13 + lhs._m32*rhs._m23 + lhs._m33*rhs._m33;

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
            mat[0]  /= x;
            mat[1]  /= x;
            mat[2]  /= x;
            mat[3]  /= x;
            mat[4]  /= x;
            mat[5]  /= x;
            mat[6]  /= x;
            mat[7]  /= x;
            mat[8]  /= x;
            mat[9]  /= x;
            mat[10] /= x;
            mat[11] /= x;
            mat[12] /= x;
            mat[13] /= x;
            mat[14] /= x;
            mat[15] /= x;
        }

        _CPU_AND_GPU_CODE_ void operator/=(const mat44 &other){
            assert(other.all());
            mat[0]  /= other[0];
            mat[1]  /= other[1];
            mat[2]  /= other[2];
            mat[3]  /= other[3];
            mat[4]  /= other[4];
            mat[5]  /= other[5];
            mat[6]  /= other[6];
            mat[7]  /= other[7];
            mat[8]  /= other[8];
            mat[9]  /= other[9];
            mat[10] /= other[10];
            mat[11] /= other[11];
            mat[12] /= other[12];
            mat[13] /= other[13];
            mat[14] /= other[14];
            mat[15] /= other[15];
        }

        _CPU_AND_GPU_CODE_ friend mat44 operator/(const mat44 &lhs, const mat44 &rhs){
            mat44 result(lhs);
            result /= rhs;
            return result;
        }

        // trace
        _CPU_AND_GPU_CODE_ T trace() const {
            return (_m00 + _m11 + _m22 + _m33);
        }

        // determinant
        // http://www.euclideanspace.com/maths/algebra/matrix/functions/determinant/fourD/index.htm
        _CPU_AND_GPU_CODE_ double det() const {
            double det_;
            det_ = 
            _m03*_m12*_m21*_m30 - _m02*_m13*_m21*_m30 - _m03*_m11*_m22*_m30 + _m01*_m13*_m22*_m30+
            _m02*_m11*_m23*_m30 - _m01*_m12*_m23*_m30 - _m03*_m12*_m20*_m31 + _m02*_m13*_m20*_m31+
            _m03*_m10*_m22*_m31 - _m00*_m13*_m22*_m31 - _m02*_m10*_m23*_m31 + _m00*_m12*_m23*_m31+
            _m03*_m11*_m20*_m32 - _m01*_m13*_m20*_m32 - _m03*_m10*_m21*_m32 + _m00*_m13*_m21*_m32+
            _m01*_m10*_m23*_m32 - _m00*_m11*_m23*_m32 - _m02*_m11*_m20*_m33 + _m01*_m12*_m20*_m33+
            _m02*_m10*_m21*_m33 - _m00*_m12*_m21*_m33 - _m01*_m10*_m22*_m33 + _m00*_m11*_m22*_m33;

            return det_;
        }

        // inverse
        // http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm
        _CPU_AND_GPU_CODE_ mat44 getInv() const{
            double det_ = det();
            assert(det_ != 0);
            T idet_ = static_cast<T>(1.0/det_);

            mat44 inv_;
            inv_._m00 = _m12*_m23*_m31 - _m13*_m22*_m31 + _m13*_m21*_m32 - _m11*_m23*_m32 - _m12*_m21*_m33 + _m11*_m22*_m33;
            inv_._m01 = _m03*_m22*_m31 - _m02*_m23*_m31 - _m03*_m21*_m32 + _m01*_m23*_m32 + _m02*_m21*_m33 - _m01*_m22*_m33;
            inv_._m02 = _m02*_m13*_m31 - _m03*_m12*_m31 + _m03*_m11*_m32 - _m01*_m13*_m32 - _m02*_m11*_m33 + _m01*_m12*_m33;
            inv_._m03 = _m03*_m12*_m21 - _m02*_m13*_m21 - _m03*_m11*_m22 + _m01*_m13*_m22 + _m02*_m11*_m23 - _m01*_m12*_m23;
            inv_._m10 = _m13*_m22*_m30 - _m12*_m23*_m30 - _m13*_m20*_m32 + _m10*_m23*_m32 + _m12*_m20*_m33 - _m10*_m22*_m33;
            inv_._m11 = _m02*_m23*_m30 - _m03*_m22*_m30 + _m03*_m20*_m32 - _m00*_m23*_m32 - _m02*_m20*_m33 + _m00*_m22*_m33;
            inv_._m12 = _m03*_m12*_m30 - _m02*_m13*_m30 - _m03*_m10*_m32 + _m00*_m13*_m32 + _m02*_m10*_m33 - _m00*_m12*_m33;
            inv_._m13 = _m02*_m13*_m20 - _m03*_m12*_m20 + _m03*_m10*_m22 - _m00*_m13*_m22 - _m02*_m10*_m23 + _m00*_m12*_m23;
            inv_._m20 = _m11*_m23*_m30 - _m13*_m21*_m30 + _m13*_m20*_m31 - _m10*_m23*_m31 - _m11*_m20*_m33 + _m10*_m21*_m33;
            inv_._m21 = _m03*_m21*_m30 - _m01*_m23*_m30 - _m03*_m20*_m31 + _m00*_m23*_m31 + _m01*_m20*_m33 - _m00*_m21*_m33;
            inv_._m22 = _m01*_m13*_m30 - _m03*_m11*_m30 + _m03*_m10*_m31 - _m00*_m13*_m31 - _m01*_m10*_m33 + _m00*_m11*_m33;
            inv_._m23 = _m03*_m11*_m20 - _m01*_m13*_m20 - _m03*_m10*_m21 + _m00*_m13*_m21 + _m01*_m10*_m23 - _m00*_m11*_m23;
            inv_._m30 = _m12*_m21*_m30 - _m11*_m22*_m30 - _m12*_m20*_m31 + _m10*_m22*_m31 + _m11*_m20*_m32 - _m10*_m21*_m32;
            inv_._m31 = _m01*_m22*_m30 - _m02*_m21*_m30 + _m02*_m20*_m31 - _m00*_m22*_m31 - _m01*_m20*_m32 + _m00*_m21*_m32;
            inv_._m32 = _m02*_m11*_m30 - _m01*_m12*_m30 - _m02*_m10*_m31 + _m00*_m12*_m31 + _m01*_m10*_m32 - _m00*_m11*_m32;
            inv_._m33 = _m01*_m12*_m20 - _m02*_m11*_m20 + _m02*_m10*_m21 - _m00*_m12*_m21 - _m01*_m10*_m22 + _m00*_m11*_m22;

            return inv_*idet_;
        }

        _CPU_AND_GPU_CODE_ mat44 &inv(){
            *this = getInv();
            return *this;
        }

        // transpose
        _CPU_AND_GPU_CODE_ mat44 getTranspose() const{
            T transpose_[16];
            transpose_[0]  = _m00;
            transpose_[1]  = _m10;
            transpose_[2]  = _m20;
            transpose_[3]  = _m30;
            transpose_[4]  = _m01;
            transpose_[5]  = _m11;
            transpose_[6]  = _m21;
            transpose_[7]  = _m31;
            transpose_[8]  = _m02;
            transpose_[9]  = _m12;
            transpose_[10] = _m22;
            transpose_[11] = _m32;
            transpose_[12] = _m03;
            transpose_[13] = _m13;
            transpose_[14] = _m23;
            transpose_[15] = _m33;

            return mat44(transpose_);
        }

        _CPU_AND_GPU_CODE_ mat44 &transpose(){
            *this = getTranspose();
            return *this;
        }

        // row / col
        _CPU_AND_GPU_CODE_ vec4<T> col(const uint c) const {
            assert(c < 4);
            vec4<T> result;
            if(c == 0){
                result = vec4<T>(_m00, _m10, _m20, _m30);
                return result;
            } 
            if(c == 1){
                result = vec4<T>(_m01, _m11, _m21, _m31);
                return result;
            }
            if(c == 2){
                result = vec4<T>(_m02, _m12, _m22, _m32);
                return result;
            }
            if(c == 3){
                result = vec4<T>(_m03, _m13, _m23, _m33);
                return result;
            }
        }

        _CPU_AND_GPU_CODE_ vec4<T> row(const uint r) const {
            assert(r < 4);
            vec4<T> result;
            if(r == 0){
                result = vec4<T>(_m00, _m01, _m02, _m03);
                return result;
            } 
            if(r == 1){
                result = vec4<T>(_m10, _m11, _m12, _m13);
                return result;
            }
            if(r == 2){
                result = vec4<T>(_m20, _m21, _m22, _m23);
                return result;
            }
            if(r == 3){
                result = vec4<T>(_m30, _m31, _m32, _m33);
                return result;
            }
        }

        _CPU_AND_GPU_CODE_ T *getData(){
            return mat;
        }

        // per-element func  
        _CPU_AND_GPU_CODE_ mat44<float> frac() const {
        return mat44(Math::frac(mat[0]), Math::frac(mat[1]), Math::frac(mat[2]), Math::frac(mat[3]), Math::frac(mat[4]), Math::frac(mat[5]), Math::frac(mat[6]), Math::frac(mat[7]), Math::frac(mat[8]), Math::frac(mat[9]), Math::frac(mat[10]), Math::frac(mat[11]), Math::frac(mat[12]), Math::frac(mat[13]), Math::frac(mat[14]), Math::frac(mat[15]));
        }
        
        _CPU_AND_GPU_CODE_ mat44 round() const {
        return mat44(Math::round(mat[0]), Math::round(mat[1]), Math::round(mat[2]), Math::round(mat[3]), Math::round(mat[4]), Math::round(mat[5]), Math::round(mat[6]), Math::round(mat[7]), Math::round(mat[8]), Math::round(mat[9]), Math::round(mat[10]), Math::round(mat[11]), Math::round(mat[12]), Math::round(mat[13]), Math::round(mat[14]), Math::round(mat[15]));
        }
        
        _CPU_AND_GPU_CODE_ mat44 ceil() const {
        return mat44(Math::ceil(mat[0]), Math::ceil(mat[1]), Math::ceil(mat[2]), Math::ceil(mat[3]), Math::ceil(mat[4]), Math::ceil(mat[5]), Math::ceil(mat[6]), Math::ceil(mat[7]), Math::ceil(mat[8]), Math::ceil(mat[9]), Math::ceil(mat[10]), Math::ceil(mat[11]), Math::ceil(mat[12]), Math::ceil(mat[13]), Math::ceil(mat[14]), Math::ceil(mat[15]));
        }
        
        _CPU_AND_GPU_CODE_ mat44 floor() const {
        return mat44(Math::floor(mat[0]), Math::floor(mat[1]), Math::floor(mat[2]), Math::floor(mat[3]), Math::floor(mat[4]), Math::floor(mat[5]), Math::floor(mat[6]), Math::floor(mat[7]), Math::floor(mat[8]), Math::floor(mat[9]), Math::floor(mat[10]), Math::floor(mat[11]), Math::floor(mat[12]), Math::floor(mat[13]), Math::floor(mat[14]), Math::floor(mat[15]));
        }
        
        _CPU_AND_GPU_CODE_ mat44 abs() const {
        return mat44(Math::abs(mat[0]), Math::abs(mat[1]), Math::abs(mat[2]), Math::abs(mat[3]), Math::abs(mat[4]), Math::abs(mat[5]), Math::abs(mat[6]), Math::abs(mat[7]), Math::abs(mat[8]), Math::abs(mat[9]), Math::abs(mat[10]), Math::abs(mat[11]), Math::abs(mat[12]), Math::abs(mat[13]), Math::abs(mat[14]), Math::abs(mat[15]));
        }


    }; // class mat44

    template<typename T> const uint mat44<T>::Cols = 4;
    template<typename T> const uint mat44<T>::Rows = 4;
    template<typename T> const uint mat44<T>::Num = 16; 
    
    // in / out
    template <typename T>
    std::ostream &operator<<(std::ostream &out, const mat44<T> &m){
        out << "[" << m(0,0) << " " << m(0,1) << " " << m(0,2) << " " << m(0,3) << "]" << std::endl;
        out << "[" << m(1,0) << " " << m(1,1) << " " << m(1,2) << " " << m(1,3) << "]" << std::endl;
        out << "[" << m(2,0) << " " << m(2,1) << " " << m(2,2) << " " << m(2,3) << "]" << std::endl;
        out << "[" << m(3,0) << " " << m(3,1) << " " << m(3,2) << " " << m(3,3) << "]" << std::endl;
        return out;
    }
    
    template <typename T>
    std::istream &operator>>(std::istream &in, mat44<T> &m){
        in >> m(0,0) >> m(0,1) >> m(0,2) >> m(0,3)
           >> m(1,0) >> m(1,1) >> m(1,2) >> m(1,3)
           >> m(2,0) >> m(2,1) >> m(2,2) >> m(2,3)
           >> m(3,0) >> m(3,1) >> m(3,2) >> m(3,3);
        if(!in){
            m = mat44<T>();
        }
        return in;
    }

namespace Math
{
    // for mat44
    template <typename T>
    _CPU_AND_GPU_CODE_ bool floatEqual(const mat44<T> &lhs, const mat44<T> &rhs){
        return floatEqual(lhs[0], rhs[0]) && 
               floatEqual(lhs[1], rhs[1]) &&
               floatEqual(lhs[2], rhs[2]) &&
               floatEqual(lhs[3], rhs[3]) &&
               floatEqual(lhs[4], rhs[4]) &&
               floatEqual(lhs[5], rhs[5]) &&
               floatEqual(lhs[6], rhs[6]) &&
               floatEqual(lhs[7], rhs[7]) &&
               floatEqual(lhs[8], rhs[8]) &&
               floatEqual(lhs[9], rhs[9]) &&
               floatEqual(lhs[10], rhs[10]) &&
               floatEqual(lhs[11], rhs[11]) &&
               floatEqual(lhs[12], rhs[12]) &&
               floatEqual(lhs[13], rhs[13]) &&
               floatEqual(lhs[14], rhs[14]) &&
               floatEqual(lhs[15], rhs[15]);
    }
    
    // max min
    template <typename T>
    _CPU_AND_GPU_CODE_ mat44<T> max(const mat44<T> &m, T x) {
        return mat44<T>(max(m[0], x),
                        max(m[1], x),
                        max(m[2], x),
                        max(m[3], x),
                        max(m[4], x),
                        max(m[5], x),
                        max(m[6], x),
                        max(m[7], x),
                        max(m[8], x),
                        max(m[9], x),
                        max(m[10], x),
                        max(m[11], x),
                        max(m[12], x),
                        max(m[13], x),
                        max(m[14], x),
                        max(m[15], x));
    }
    
    template <typename T>
    _CPU_AND_GPU_CODE_ mat44<T> max(const mat44<T> &lhs, const mat44<T> &rhs) {
        return mat44<T>(max(lhs[0], rhs[0]),
                        max(lhs[1], rhs[1]),
                        max(lhs[2], rhs[2]),
                        max(lhs[3], rhs[3]),
                        max(lhs[4], rhs[4]),
                        max(lhs[5], rhs[5]),
                        max(lhs[6], rhs[6]),
                        max(lhs[7], rhs[7]),
                        max(lhs[8], rhs[8]),
                        max(lhs[9], rhs[9]),
                        max(lhs[10], rhs[10]),
                        max(lhs[11], rhs[11]),
                        max(lhs[12], rhs[12]),
                        max(lhs[13], rhs[13]),
                        max(lhs[14], rhs[14]),
                        max(lhs[15], rhs[15]));
    }

    template <typename T>
    _CPU_AND_GPU_CODE_ mat44<T> min(const mat44<T> &m, T x) {
        return mat44<T>(min(m[0], x),
                        min(m[1], x),
                        min(m[2], x),
                        min(m[3], x),
                        min(m[4], x),
                        min(m[5], x),
                        min(m[6], x),
                        min(m[7], x),
                        min(m[8], x),
                        min(m[9], x),
                        min(m[10], x),
                        min(m[11], x),
                        min(m[12], x),
                        min(m[13], x),
                        min(m[14], x),
                        min(m[15], x));
     }

    template <typename T>
    _CPU_AND_GPU_CODE_ mat44<T> min(const mat44<T> &lhs, const mat44<T> &rhs) {
        return mat44<T>(min(lhs[0], rhs[0]),
                        min(lhs[1], rhs[1]),
                        min(lhs[2], rhs[2]),
                        min(lhs[3], rhs[3]),
                        min(lhs[4], rhs[4]),
                        min(lhs[5], rhs[5]),
                        min(lhs[6], rhs[6]),
                        min(lhs[7], rhs[7]),
                        min(lhs[8], rhs[8]),
                        min(lhs[9], rhs[9]),
                        min(lhs[10], rhs[10]),
                        min(lhs[11], rhs[11]),
                        min(lhs[12], rhs[12]),
                        min(lhs[13], rhs[13]),
                        min(lhs[14], rhs[14]),
                        min(lhs[15], rhs[15]));
    }

    
    // per-element func
    template <typename T>
    _CPU_AND_GPU_CODE_ mat44<float> frac(const mat44<T> &mat) {
    return mat.frac();
    }

    template <typename T>
    _CPU_AND_GPU_CODE_ mat44<T> round(const mat44<T> &mat) {
    return mat.round();
    }
    
    template <typename T>
    _CPU_AND_GPU_CODE_ mat44<T> ceil(const mat44<T> &mat) {
    return mat.ceil();
    }
    
    template <typename T>
    _CPU_AND_GPU_CODE_ mat44<T> floor(const mat44<T> &mat) {
    return mat.floor();
    }
    
    template <typename T>
    _CPU_AND_GPU_CODE_ mat44<T> abs(const mat44<T> &mat) {
    return mat.abs();
    }
    
} // namespace Math

} // namespace LLib

#endif // _LL_MAT44_H