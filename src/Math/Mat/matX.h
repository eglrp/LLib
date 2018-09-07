#ifndef _LL_MATX_H_
#define _LL_MATX_H_

#include "../../Utility/utility.h"
#include "../Vec/vec_header.h"

namespace LLib
{
    template <typename T, uint H, uint W>
    class matX
    {
        public:
            // data
            using ValueType = T;

            union{
                T mat[H*W];
                T mat2[H][W];
            };

            // dimension
            // TODO : derfine as static
            uint Num;
            _CPU_AND_GPU_CODE_ static bool isSquare(){
                return W == H;
            }

            _CPU_AND_GPU_CODE_ static matX zeros(){
                return matX(0);
            }

            _CPU_AND_GPU_CODE_ static matX identity(){
                assert(W == H);
                matX result;

                #pragma omp parallel for
                for(size_t i = 0; i < H; i++)
                    result(i, i) = 1;

                return result;
            }

            _CPU_AND_GPU_CODE_ static matX full(T x){
                return matX(x);
            }

            _CPU_AND_GPU_CODE_ static matX diag(T x){
                assert(W == H);
                matX result;

                #pragma omp parallel for
                for(size_t i = 0; i < H; i++)
                    result(i, i) = x;

                return result;
            }

            // set func
            _CPU_AND_GPU_CODE_ void setIdentity(){
                *this = identity();
            }

            _CPU_AND_GPU_CODE_ void setZeros(){
                *this = zeros();
            }

            _CPU_AND_GPU_CODE_ void setFull(T x){
                *this = full(x);
            }

            _CPU_AND_GPU_CODE_ void setDiag(T x){
                *this = diag(x);
            }

            // constructor
            _CPU_AND_GPU_CODE_ matX(T x = 0) : Num(W*H) {
                #pragma omp parallel for
                for(size_t i = 0; i < Num; i++)
                    mat[i] = x;

            }

            template <typename U>
            _CPU_AND_GPU_CODE_ matX(const matX<U, H, W> &other) : Num(W*H) {
                #pragma omp parallel for
                for(size_t i = 0; i < Num; i++)
                    mat[i] = other[i];
            }

            template <typename U>
            _CPU_AND_GPU_CODE_ matX(const U *m) : Num(W*H) {
                #pragma omp parallel for
                for(size_t i = 0; i < Num; i++)
                    mat[i] = m[i];
            }

            // convert type
            template <typename U>
            _CPU_AND_GPU_CODE_ matX<U, H, W> toType() const {
                return matX<U, H, W>(*this);
            }

            // access
            _CPU_AND_GPU_CODE_ T &at(const uint i, const uint j){
                assert(i < H && j < W);
                return mat[i*W + j];
            }
            
            _CPU_AND_GPU_CODE_ const T &at(const uint i, const uint j) const {
                assert(i < H && j < W);
                return mat[i*W + j];
            }

            _CPU_AND_GPU_CODE_ T &at(const uint i){
                assert(i < Num);
                return mat[i];
            }

            _CPU_AND_GPU_CODE_ const T &at(const uint i) const {
                assert(i < Num);
                return mat[i];
            }

            _CPU_AND_GPU_CODE_ T &operator()(const uint i, const uint j){
                assert(i < H && j < W);
                return mat[i*W + j];
            }

            _CPU_AND_GPU_CODE_ const T operator()(const uint i, const uint j) const {
                assert(i < H && j < W);
                return mat[i*W + j];
            }

            _CPU_AND_GPU_CODE_ T &operator[](const uint i){
                assert(i < Num);
                return mat[i];
            }

            _CPU_AND_GPU_CODE_ const T &operator[](const uint i) const {
                assert(i < Num);
                return mat[i];
            }

            // == / !=
            _CPU_AND_GPU_CODE_ bool operator==(const matX &other) const {
                for(size_t i = 0; i < Num; i++){
                    if(mat[i] != other[i]) return false;
                }
                return true;
            }

            _CPU_AND_GPU_CODE_ bool operator!=(const matX &other) const {
                return !(*this == other);
            }

            // negative
            _CPU_AND_GPU_CODE_ matX operator-() const {
                matX m;

                #pragma omp parallel for
                for(size_t i = 0; i < Num; i++)
                    m[i] = -mat[i];
                
                return m;
            }

            // +
            _CPU_AND_GPU_CODE_ void operator+=(T x){
                #pragma omp parallel for
                for(size_t i = 0; i < Num; i++)
                    mat[i] += x;
            }

            _CPU_AND_GPU_CODE_ void operator+=(const matX &other){
                #pragma omp parallel for
                for(size_t i = 0; i < Num; i++)
                    mat[i] += other[i];
            }

            _CPU_AND_GPU_CODE_ friend matX operator+(const matX &lhs, const matX &rhs){
                matX result(lhs);
                result += rhs;
                return result;
            }

            // -
            _CPU_AND_GPU_CODE_ void operator-=(T x){
                #pragma omp parallel for
                for(size_t i = 0; i < Num; i++)
                    mat[i] -= x;
            }

            _CPU_AND_GPU_CODE_ void operator-=(const matX &other){
                #pragma omp parallel for
                for(size_t i = 0; i < Num; i++)
                    mat[i] -= other[i];
            }

            _CPU_AND_GPU_CODE_ friend matX operator-(const matX &lhs, const matX &rhs){
                matX result(lhs);
                result -= rhs;
                return result;
            }

            // *
            _CPU_AND_GPU_CODE_ void operator*=(T x){
                #pragma omp parallel for
                for(size_t i = 0; i < Num; i++)
                    mat[i] *= x;
            }

            _CPU_AND_GPU_CODE_ void operator*=(const matX &other){
                #pragma omp parallel for
                for(size_t i = 0; i < Num; i++)
                    mat[i] *= other[i];
            }

            _CPU_AND_GPU_CODE_ friend matX operator*(const matX &m, T x){
                matX result(m);
                result *= x;
                return result;
            }

            _CPU_AND_GPU_CODE_ friend matX operator*(T x, const matX &n){
                matX result(n);
                result *= x;
                return result;
            }

            _CPU_AND_GPU_CODE_ friend matX operator*(const matX &lhs, const matX &rhs){
                matX result(lhs);
                result *= rhs;
                return result;
            }

            // TODO : mat*vec, vec*mat, mat*mat
            // _CPU_AND_GPU_CODE_  friend vecX<T, H> operator*(const matX &m, const vecX<T, W> &v){
            //     vecX<T, H> result;
            //     for(size_t i = 0; i < H; i++)
            //         for(size_t j = 0; j<W; j++)    
            //             result[i] += m(i, j)*v[j];
            //     return result;
            // }

            // _CPU_AND_GPU_CODE_ friend vecX<T, W> operator(const vecX<W, H> &v, const matX &m){
            //     vecX<T, W> result;
            //     result = m.getTranspose()*v;
            //     return result;
            // }

            // _CPU_AND_GPU_CODE_ friend matX matmul(const matX &lhs, const matX &rhs){
            //     matX result;
            //     for(size_t i = 0; i < H; i++)
            //         for(size_t j = 0; j < W; j++)
            //             result(i, j) = lhs.row(i) * rhs.col(j);
            //     return result;
            // }

            // /
            _CPU_AND_GPU_CODE_ bool all(){
                for(size_t i = 0; i < Num; i++)
                    if(mat[i] == 0) return false;
                
                return true;
            }

            _CPU_AND_GPU_CODE_ void operator/=(T x){
                assert(x != 0);
                #pragma omp parallel for
                for(size_t i = 0; i < Num; i++)
                    mat[i] /= x;
            }

            _CPU_AND_GPU_CODE_ void operator/=(const matX &other){
                assert(all());
                #pragma omp parallel for
                for(size_t i = 0; i < Num; i++)
                    mat[i] /= other[i];
            }

            _CPU_AND_GPU_CODE_ friend matX operator/(const matX &lhs, const matX &rhs){
                matX result(lhs);
                result /= rhs;
                return result;
            }

            // trace
            _CPU_AND_GPU_CODE_ T trace() const {
                assert(H == W);
                T t = 0;

                #pragma omp parallel for
                for(size_t i = 0; i < W; i++)
                    #pragma omp atomic
                    t += mat2[i][i];

                return t;
            }

            // determinant
            _CPU_AND_GPU_CODE_ T det() const {
                NOT_IMPLENT
            }

            // inverse
            _CPU_AND_GPU_CODE_ void getInv() const {
                NOT_IMPLENT
            }

            _CPU_AND_GPU_CODE_ void inv(){
                NOT_IMPLENT
            }

            // transpose
            _CPU_AND_GPU_CODE_ matX getTranspose() const {
                T transpose_[Num];

                #pragma omp parallel for
                for(size_t i = 0; i < H; i++)
                    for(size_t j = 0; j < W; i++)
                    transpose_[i*W + j] = mat[j*H + i];

                return matX(transpose_);
            }

            _CPU_AND_GPU_CODE_ matX &transpose(){
                *this = getTranspose();
            }

            // row / col
            _CPU_AND_GPU_CODE_ vecX<T, W> row(const uint r) const {
                assert(r < H);
                vecX<T, W> result;
                
                #pragma omp parallel for
                for(size_t i = 0; i < W; i++)
                    result[i] = mat2[r][i];
                
                return result;
            }

            _CPU_AND_GPU_CODE_ vecX<T, H> col(const uint c) const {
                assert(c < W);
                vecX<T, H> result;
                
                #pragma omp parallel for
                for(size_t i = 0; i < H; i++)
                    result[i] = mat2[i][c];
                
                return result;
            }

            _CPU_AND_GPU_CODE_ T *getData(){
                return mat;
            }

            // TODO : block
            // matX<T, subH, subW> block(uint r, uint c) const {
            //     assert((r+subH) < H && (c+subW) < W);
            //     matX<T, subH, subW> m;

            //     for(uint i = r; i < r+subH; i++)
            //         for(uint j = c; j < c+sunW; j++)
            //             m(i-r, j-c) = mat[i*cols + j];

            //     return m;
            // }

            // per-element func
            _CPU_AND_GPU_CODE_ matX<float, H, W> frac() const {
                matX result;

                #pragma omp parallel for
                for(size_t i = 0; i < Num; i++)
                    result[i] = Math::frac(mat[i]);

                return result;
            }

            _CPU_AND_GPU_CODE_ matX round() const {
                matX result;

                #pragma omp parallel for
                for(size_t i = 0; i < Num; i++)
                    result[i] = Math::round(mat[i]);

                return result;
            }

            _CPU_AND_GPU_CODE_ matX ceil() const {
                matX result;

                #pragma omp parallel for
                for(size_t i = 0; i < Num; i++)
                    result[i] = Math::ceil(mat[i]);

                return result;
            }

            _CPU_AND_GPU_CODE_ matX floor() const {
                matX result;

                #pragma omp parallel for
                for(size_t i = 0; i < Num; i++)
                    result[i] = Math::floor(mat[i]);

                return result;
            }

            _CPU_AND_GPU_CODE_ matX abs() const {
                matX result;

                #pragma omp parallel for
                for(size_t i = 0; i < Num; i++)
                    result[i] = Math::abs(mat[i]);

                return result;
            }

    }; // class matX

    // in / out
    template <typename T, uint H, uint W>
    std::ostream &operator<<(std::ostream &out, const matX<T, H, W> &m){
        for(size_t i = 0; i < H; i++)
            for(size_t j = 0; j < W; j++)
            {
                if(j == 0) out << "[";
                out << " " << m(i, j) << " ";
                if(j == W-1) out << "]" << std::endl;
            }
        return out;
    }

    // template <typename T>
    // std::istream &operator>>(std::istream &in, mat22<T> &m){
    //     in >> m(0,0) >> m(0,1) >> m(1,0) >> m(1,1);
    //     if(!in){
    //         m = mat22<T>();
    //     }
    //     return in;
    // }

namespace Math
{
    // for matX 
    template <typename T, uint H, uint W>
    _CPU_AND_GPU_CODE_ bool floatEqual(const matX<T, H, W> &lhs, const matX<T, H, W> &rhs){
        for(size_t i = 0; i < lhs.Num; i++)
            if(!Math::floatEqual(lhs[i], rhs[i])) return false;
        return true;
    }

    // max min
    template <typename T, uint H, uint W>
    _CPU_AND_GPU_CODE_ matX<T, H, W> max(const matX<T, H, W> &lhs, const matX<T, H, W> &rhs){
        matX<T, H, W> result(lhs);
        #pragma omp parallel for
        for(size_t i = 0; i < lhs.Num; i++)
            result[i] = Math::max(result[i], rhs[i]);
        return result;
    }

    template <typename T, uint H, uint W>
    _CPU_AND_GPU_CODE_ matX<T, H, W> max(const matX<T, H, W> &m, T x){
        matX<T, H, W> result(m);
        #pragma omp parallel for
        for(size_t i = 0; i < m.Num; i++)
            result[i] = Math::max(result[i], x);
        return result;
    }

    template <typename T, uint H, uint W>
    _CPU_AND_GPU_CODE_ matX<T, H, W> min(const matX<T, H, W> &lhs, const matX<T, H, W> &rhs){
        matX<T, H, W> result(lhs);
        #pragma omp parallel for
        for(size_t i = 0; i < lhs.Num; i++)
            result[i] = Math::min(result[i], rhs[i]);
        return result;
    }

    template <typename T, uint H, uint W>
    _CPU_AND_GPU_CODE_ matX<T, H, W> min(const matX<T, H, W> &m, T x){
        matX<T, H, W> result(m);
        #pragma omp parallel for
        for(size_t i = 0; i < m.Num; i++)
            result[i] = Math::min(result[i], x);
        return result;
    }

    // per-element func
    template <typename T, uint H, uint W>
    _CPU_AND_GPU_CODE_ matX<float, H, W> frac(const matX<T, H, W> &mat) {
    return mat.frac();
    }

    template <typename T, uint H, uint W>
    _CPU_AND_GPU_CODE_ matX<T, H, W> round(const matX<T, H, W> &mat) {
    return mat.round();
    }
    
    template <typename T, uint H, uint W>
    _CPU_AND_GPU_CODE_ matX<T, H, W> ceil(const matX<T, H, W> &mat) {
    return mat.ceil();
    }
    
    template <typename T, uint H, uint W>
    _CPU_AND_GPU_CODE_ matX<T, H, W> floor(const matX<T, H, W> &mat) {
    return mat.floor();
    }
    
    template <typename T, uint H, uint W>
    _CPU_AND_GPU_CODE_ matX<T, H, W> abs(const matX<T, H, W> &mat) {
    return mat.abs();
    }

}  // namespace Math

}

#endif // _LL_MATX_H_