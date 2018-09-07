#ifndef _LL_VECX_H_
#define _LL_VECX_H_

#include "../../Utility/utility.h"

namespace LLib
{
    // ND vector
    template <typename T, uint N>
    class vecX
    {
    public:
        // data
        using ValueType = T;
        static const uint Dim;
        T array[N];

        // static func
        _CPU_AND_GPU_CODE_ static vecX zeros(){
            vecX result;
            return result;
        }

        _CPU_AND_GPU_CODE_ static vecX ones(){
            vecX result(1);
            return result;
        }
        
        _CPU_AND_GPU_CODE_ static vecX full(T x){
            vecX result(x);
            return result;
        }

        // constructor
        _CPU_AND_GPU_CODE_ vecX(T x = 0){
            fill(x);
        }

        template <typename U>
        _CPU_AND_GPU_CODE_ vecX(const U *v){
            fill(v);
        }

        template <typename U>
        _CPU_AND_GPU_CODE_ vecX(const vecX<U, N> &other){
            fill(other.array);
        }

        // convert type
        template <typename U>
        _CPU_AND_GPU_CODE_ vecX<U, N> toType() const {
            return vecX<U, N>(*this);
        }

        // fill
        template <typename U>
        _CPU_AND_GPU_CODE_ void fill(U x){
            #pragma omp parallel for
            for(size_t i = 0; i < N; i++)
                array[i] = x;
        }

        template <typename U>
        _CPU_AND_GPU_CODE_ void fill(const U *v){
            #pragma omp parallel for
            for(size_t i = 0; i < N; i++)
                array[i] = v[i];
        }

        // access
        _CPU_AND_GPU_CODE_ T &operator[](const uint i){
            assert(i < Dim);
            return array[i];
        }

        _CPU_AND_GPU_CODE_ const T &operator[](const uint i) const {
            assert(i < Dim);
            return array[i];
        }

        _CPU_AND_GPU_CODE_ T &at(const uint i){
            assert(i < Dim);
            return array[i];
        }

        _CPU_AND_GPU_CODE_ const T &at(const uint i) const {
            assert(i < Dim);
            return array[i];
        }

        // assign
        template<typename U>
        _CPU_AND_GPU_CODE_ vecX &operator=(const vecX<U, N> &other){
            fill(other.getData());
            return *this;
        }

        // negative
        _CPU_AND_GPU_CODE_ vecX operator-() const {
            vecX result;
            
            #pragma omp parallel for
            for(size_t i = 0; i < N; i++)
                result[i] = -array[i];

            return result;
        }

        // +
        _CPU_AND_GPU_CODE_ void operator+=(const T x){
            #pragma omp parallel for
            for(size_t i = 0; i < N; i++)
                array[i] += x;
        }

        _CPU_AND_GPU_CODE_ void operator+=(const vecX &other){
            #pragma omp parallel for
            for(size_t i = 0; i < N; i++)
                array[i] += other[i];
        }

        _CPU_AND_GPU_CODE_ friend vecX operator+(const vecX &lhs, const vecX &rhs){
            vecX result(lhs);
            result += rhs;
            return result;
        }

        // -
        _CPU_AND_GPU_CODE_ void operator-=(const T x){
            #pragma omp parallel for
            for(size_t i = 0; i < N; i++)
                array[i] -= x;
        }

        _CPU_AND_GPU_CODE_ void operator-=(const vecX &other){
            #pragma omp parallel for
            for(size_t i = 0; i < N; i++)
                array[i] -= other[i];
        }

        _CPU_AND_GPU_CODE_ friend vecX operator-(const vecX &lhs, const vecX &rhs){
            vecX result(lhs);
            result -= rhs;
            return result;
        }


        // *
        _CPU_AND_GPU_CODE_ void operator*=(const T x){
            #pragma omp parallel for
            for(size_t i = 0; i < N; i++)
                array[i] *= x;
        }

        _CPU_AND_GPU_CODE_ void operator*=(const vecX &other){
            #pragma omp parallel for
            for(size_t i = 0; i < N; i++)
                array[i] *= other[i];
        }

        _CPU_AND_GPU_CODE_ friend vecX operator*(T x, const vecX &v){
            vecX result(v);
            result *= x;
            return result;
        }

        _CPU_AND_GPU_CODE_ friend vecX operator*(const vecX &v, T x){
            vecX result(v);
            result *= x;
            return result;
        }

        _CPU_AND_GPU_CODE_ friend vecX operator*(const vecX &lhs, const vecX &rhs){
            vecX result(lhs);
            result *= rhs;
            return result;
        }

        // /
        _CPU_AND_GPU_CODE_ bool all() const {
            for(size_t i = 0; i < N; i++)
                if(!array[i]) return false;

            return true;
        }

        _CPU_AND_GPU_CODE_ void operator/=(const T x){
            assert(x != 0);
            #pragma omp parallel for
            for(size_t i = 0; i < N; i++)
                array[i] /= x;
        }

        _CPU_AND_GPU_CODE_ void operator/=(const vecX &other){
            assert(other.all());
            #pragma omp parallel for
            for(size_t i = 0; i < N; i++)
                array[i] /= other[i];
        }

        _CPU_AND_GPU_CODE_ friend vecX operator/(const vecX &lhs, const vecX &rhs){
            vecX result(lhs);
            result /= rhs;
            return result;
        }

        // == / !=
        _CPU_AND_GPU_CODE_ bool operator==(const vecX &other) const {
            for(size_t i = 0; i < N; i++)
                if(array[i] != other[i]) return false;
            
            return true;
        }

        _CPU_AND_GPU_CODE_ bool operator!=(const vecX &other) const {
            return !(*this == other);
        }


        // dot
        _CPU_AND_GPU_CODE_ T dot(const vecX &other) const {
            return ((*this)*other).sum();
        }

        _CPU_AND_GPU_CODE_ friend T dot(const vecX &lhs, const vecX &rhs){
            return (lhs*rhs).sum();
        }

        // length
        _CPU_AND_GPU_CODE_ double lengthSq() const {
            return this->dot(*this);
        }

        _CPU_AND_GPU_CODE_ double length() const {
            return sqrt(this->dot(*this));
        }

        // distance
        _CPU_AND_GPU_CODE_ friend double distSq(const vecX &lhs, const vecX &rhs){
            vecX diff = lhs - rhs;
            return diff.lengthSq();
        }

        _CPU_AND_GPU_CODE_ friend double dist(const vecX &lhs, const vecX &rhs){
            vecX diff = lhs - rhs;
            return diff.length();
        }

        // normalize
        _CPU_AND_GPU_CODE_ vecX normalize(){
            double l = length();
            if(l < EPS) return *this;
            double ratio = 1.0/l;
            *this *= ratio;
            return *this;
        }

        _CPU_AND_GPU_CODE_ vecX getNormalize() const {
            vecX result(*this);
            return result.normalize();
        }

        // get data pointer
        _CPU_AND_GPU_CODE_ T *getData(){
            return array;
        }

        // per-element func
        _CPU_AND_GPU_CODE_ vecX<float, N> frac() const {
            vecX<float, N> result;
            #pragma omp parallel for
            for(size_t i = 0; i < Dim; i++)
                result[i] = Math::frac(array[i]);
            return result;
        }

        _CPU_AND_GPU_CODE_ vecX round() const {
            vecX result;
            #pragma omp parallel for
            for(size_t i = 0; i < Dim; i++)
                result[i] = Math::round(array[i]);
            
            return result;
        }

        _CPU_AND_GPU_CODE_ vecX ceil() const {
            vecX result;
            #pragma omp parallel for
            for(size_t i = 0; i < Dim; i++)
                result[i] = Math::ceil(array[i]);
            
            return result;
        }

        _CPU_AND_GPU_CODE_ vecX floor() const {
            vecX result;
            #pragma omp parallel for
            for(size_t i = 0; i < Dim; i++)
                result[i] = Math::floor(array[i]);
            
            return result;
        }

        _CPU_AND_GPU_CODE_ vecX abs() const {
            vecX<T, N> result;
            #pragma omp parallel for
            for(size_t i = 0; i < Dim; i++)
                result[i] = Math::abs(array[i]);
            
            return result;
        }

        // statistics
        _CPU_AND_GPU_CODE_ T sum() const {
            T result = 0;

            #pragma omp parallel for
            for(size_t i = 0; i < Dim; i++)
                #pragma omp atomic
                result += array[i];

            return result;
        }

        _CPU_AND_GPU_CODE_ double mean() const {
            return sum()/Dim;
        }

        _CPU_AND_GPU_CODE_ double var() const {
            T m = mean();
            vecX diff = *this - m;
            return diff.dot(diff)/Dim;
        }

        // *************************************************************************
      
        // TODO
        // segment
        template <uint L>
        _CPU_AND_GPU_CODE_ vecX<T, L> segment(const uint pos){
            assert((pos + L) < Dim);
            vecX<T, L> v;
            
            #pragma omp parallel for
            for(size_t i = 0; i < L; i++)
                v[i] = array[i+pos];

            return v;
        }

    }; // class vecX

    template <typename T, uint N> const uint vecX<T, N>::Dim = N;

    // https://stackoverflow.com/questions/6907194/how-to-typedef-a-template-class
    // template <typename T, uint N>
    // using cuVecX = vecX<T, N, true>;

    // template <typename T, uint N>
    // using VecX = vecX<T, N, false>;

    // TODO
    // template <typename T, uint N>
    // std::istream &operator>>(std::istream &in, const vecX<T, N> &v){

    //     for(size_t i = 0; i < N; i++)
    //         in >> v[i];
    //     if(!in){
    //       v = 0;
    //     }
    //     return in;
    // }

    template <typename T, uint N>
    std::ostream &operator<<(std::ostream &out, const vecX<T, N> &v){

        out << "[";
        for(size_t i = 0; i < N-1; i++)
            out << v[i] << ",";
        out << v[N-1] << "]" << std::endl;
        
        return out;
    }

    namespace Math
    {

        template <typename T, uint N>
        _CPU_AND_GPU_CODE_ bool floatEqual(const vecX<T, N> &lhs, const vecX<T, N> &rhs){
            for(size_t i = 0; i < vecX<T, N>::Dim; i++)
                if(!floatEqual(lhs[i], rhs[i])) return false;
            
            return true;
        }

        // min max
        template <typename T, uint N>
        _CPU_AND_GPU_CODE_ vecX<T, N> min(const vecX<T, N> &v, T x){
            vecX<T, N> result;
            #pragma omp parallel for
            for(size_t i = 0; i < vecX<T, N>::Dim; i++)
                result[i] = min(v[i], x);
            
            return result;
        }

        template <typename T, uint N>
        _CPU_AND_GPU_CODE_ vecX<T, N> min(const vecX<T, N> &lhs, const vecX<T, N> &rhs){
            vecX<T, N> result;
            #pragma omp parallel for
            for(size_t i = 0; i < vecX<T, N>::Dim; i++)
                result[i] = min(lhs[i], rhs[i]);
            
            return result;
        }

        template <typename T, uint N>
        _CPU_AND_GPU_CODE_ vecX<T, N> max(const vecX<T, N> &v, T x){
            vecX<T, N> result;
            #pragma omp parallel for
            for(size_t i = 0; i < vecX<T, N>::Dim; i++)
                result[i] = max(v[i], x);
            
            return result;
        }

        template <typename T, uint N>
        _CPU_AND_GPU_CODE_ vecX<T, N> max(const vecX<T, N> &lhs, const vecX<T, N> &rhs){
            vecX<T, N> result;
            #pragma omp parallel for
            for(size_t i = 0; i < vecX<T, N>::Dim; i++)
                result[i] = max(lhs[i], rhs[i]);
            
            return result;
        }

        // per-element func
        template <typename T, uint N>
        _CPU_AND_GPU_CODE_ vecX<float, N> frac(const vecX<T, N> &v){
            return v.frac();
        }

        template <typename T, uint N>
        _CPU_AND_GPU_CODE_ vecX<T, N> round(const vecX<T, N> &v){
            return v.round();
        }

        template <typename T, uint N>
        _CPU_AND_GPU_CODE_ vecX<T, N> ceil(const vecX<T, N> &v){
            return v.ceil();
        }

        template <typename T, uint N>
        _CPU_AND_GPU_CODE_ vecX<T, N> floor(const vecX<T, N> &v){
            return v.floor();
        }

        template <typename T, uint N>
        _CPU_AND_GPU_CODE_ vecX<T, N> abs(const vecX<T, N> &v){
            return v.abs();
        }

        // statics
        template <typename T, uint N>
        _CPU_AND_GPU_CODE_ typename vecX<T, N>::ValueType sum(const vecX<T, N> &v){
            return v.sum();
        }

        template <typename T, uint N>
        _CPU_AND_GPU_CODE_ double mean(const vecX<T, N> &v){
            return v.mean();
        }

        template <typename T, uint N>
        _CPU_AND_GPU_CODE_ double var(const vecX<T, N> &v){
            return v.var();
        }


    }  // namespace Math

} // namespace LLib

#endif // _LL_VECX_H_