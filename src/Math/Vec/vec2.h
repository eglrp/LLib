#ifndef _LL_VEC2_H
#define _LL_VEC2_H

#include "../../Utility/utility.h"

namespace LLib
{
    // 2D vector
    template <typename T>
    class vec2
    {
    public:
        // data
        using ValueType = T;
        static const uint Dim;
        union{
            struct{
                T x, y;
            };
            struct{
                T width, height;
            };
            T array[2];
        };

        // static func
        _CPU_AND_GPU_CODE_ static vec2 zeros(){
            return vec2(0);
        }

        _CPU_AND_GPU_CODE_ static vec2 ones(){
            return vec2(1);
        }

        _CPU_AND_GPU_CODE_ static vec2 full(T x){
            return vec2(x);
        }


        // constructor
        _CPU_AND_GPU_CODE_ vec2(T x = 0){
            array[0] = array[1] = x;
        }

        _CPU_AND_GPU_CODE_ vec2(T x_, T y_){
            x = x_;
            y = y_;
        }

        template <typename U>
        _CPU_AND_GPU_CODE_ vec2(const vec2<U> &other){
            x = other.x;
            y = other.y;
        }

        template <typename U>
        _CPU_AND_GPU_CODE_ vec2(const U *other){
            array[0] = other[0];
            array[1] = other[1];
        }

        // convert type
        template<typename U>
        _CPU_AND_GPU_CODE_ vec2<U> toType() const {
            return vec2<U>(*this);
        }

        // access
        _CPU_AND_GPU_CODE_ T &operator[](const uint i){
            assert(i < 2);
            return array[i];
        }

        _CPU_AND_GPU_CODE_ const T &operator[](const uint i) const {
            assert(i < 2);
            return array[i];
        }

        _CPU_AND_GPU_CODE_ T &at(const uint i){
            assert(i < 2);
            return array[i];
        }
        
        _CPU_AND_GPU_CODE_ const T &at(const uint i) const {
            assert(i < 2);
            return array[i];
        }

        // assign
        _CPU_AND_GPU_CODE_ vec2 &operator=(const vec2 &other){
            x = other.x;
            y = other.y;
            return *this;
        }

        // negative
        _CPU_AND_GPU_CODE_ vec2 operator-() const {
            return vec2(-x, -y);
        }

        // +
        _CPU_AND_GPU_CODE_ void operator+=(T x){
            array[0] += x;
            array[1] += x;
        }

        _CPU_AND_GPU_CODE_ void operator+=(const vec2 &other) {
            x += other.x;
            y += other.y;
        }

        _CPU_AND_GPU_CODE_ friend vec2 operator+(const vec2 &lhs, const vec2 &rhs){
            vec2 result(lhs);
            result += rhs;
            return result;
        }

        // -
        _CPU_AND_GPU_CODE_ void operator-=(T x){
            array[0] -= x;
            array[1] -= x;
        }

        _CPU_AND_GPU_CODE_ void operator-=(const vec2 &other){
            x -= other.x;
            y -= other.y;
        }

        _CPU_AND_GPU_CODE_ friend vec2 operator-(const vec2 &lhs, const vec2 &rhs){
            vec2 result(lhs);
            result -= rhs;
            return result;
        }


        // *
        _CPU_AND_GPU_CODE_ void operator*=(T x){
            array[0] *= x;
            array[1] *= x;
        }

        _CPU_AND_GPU_CODE_ void operator*=(const vec2 &other){
            x *= other.x;
            y *= other.y;
        }

        _CPU_AND_GPU_CODE_ friend vec2 operator*(T x, const vec2 &v){
            vec2 result(v);
            result *= x;
            return result;
        }
        _CPU_AND_GPU_CODE_ friend vec2 operator*(const vec2 &v, T x){
            vec2 result(v);
            result *= x;
            return result;
        }

        _CPU_AND_GPU_CODE_ friend vec2 operator*(const vec2 &lhs, const vec2 &rhs){
            vec2 result(lhs);
            result *= rhs;
            return result;
        }
        
        // /
        _CPU_AND_GPU_CODE_ bool all() const {
        for(size_t i = 0; i < 2; i++)
          if(!array[i]) return false;

        return true;
        }

        _CPU_AND_GPU_CODE_ void operator/=(T x){
            assert(x != 0);
            array[0] /= x;
            array[1] /= x;
        }

        _CPU_AND_GPU_CODE_ void operator/=(const vec2 &other){
            assert(other.all());
            x /= other.x;
            y /= other.y;
        }

        _CPU_AND_GPU_CODE_ friend vec2 operator/(const vec2 &lhs, const vec2 &rhs){
            vec2 result(lhs);
            result /= rhs;
            return result;
        }

        // == / !=
        _CPU_AND_GPU_CODE_ bool operator==(const vec2 &other) const {
            return (x == other.x && y == other.y);
        }

        _CPU_AND_GPU_CODE_ bool operator!=(const vec2 &other) const {
            return !(*this == other);
        }

        // dot
        _CPU_AND_GPU_CODE_ double dot(const vec2 &other) const {
          return (x*other.x + y*other.y);
        }

        _CPU_AND_GPU_CODE_ friend double dot(const vec2 &lhs, const vec2 &rhs){
          return (lhs.x*rhs.x + lhs.y*rhs.y);
        }

        // length
        _CPU_AND_GPU_CODE_ double lengthSq() const {
            return (x*x + y*y);
        }

        _CPU_AND_GPU_CODE_ double length() const {
            return sqrt(x*x + y*y);
        }

        // distance
        _CPU_AND_GPU_CODE_ friend double distSq(const vec2 &lhs, const vec2 &rhs){
        return (lhs.x-rhs.x)*(lhs.x-rhs.x) + (lhs.y-rhs.y)*(lhs.y-rhs.y);
        }

        _CPU_AND_GPU_CODE_ friend double dist(const vec2 &lhs, const vec2 &rhs){
        return sqrt((lhs.x-rhs.x)*(lhs.x-rhs.x) + (lhs.y-rhs.y)*(lhs.y-rhs.y));
        }

        // normalize
        _CPU_AND_GPU_CODE_ vec2 normalize() {
            double l = length();
            if(l < EPS) return *this;
            double ratio = 1.0 / l;
            *this *= ratio;
            return *this;
        }

        _CPU_AND_GPU_CODE_ vec2 getNormalize() const {
          vec2 result(*this);
          return result.normalize();
        }


        // get data pointer
        _CPU_AND_GPU_CODE_ T *getData(){
            return array;
        }

        // per-element func
        _CPU_AND_GPU_CODE_ vec2<float> frac() const {
          return vec2<float>(Math::frac(x), Math::frac(y));
        }

        _CPU_AND_GPU_CODE_ vec2 round() const {
          return vec2(Math::round(x), Math::round(y));
        }

        _CPU_AND_GPU_CODE_ vec2 ceil() const {
          return vec2(Math::ceil(x), Math::ceil(y));
        }

        _CPU_AND_GPU_CODE_ vec2 floor() const {
          return vec2(Math::floor(x), Math::floor(y));
        }

        _CPU_AND_GPU_CODE_ vec2 abs() const {
          return vec2(Math::abs(x), Math::abs(y));
        }

        // statistics
        _CPU_AND_GPU_CODE_ T sum() const {
            return (x + y);
        }

        _CPU_AND_GPU_CODE_ double mean() const {
            return sum()/2;
        }

        _CPU_AND_GPU_CODE_ double var() const {
            T m = mean();
            vec2 diff = *this - m;
            return diff.dot(diff)/2;
        }

    }; // class vec2

    template <typename T> const uint vec2<T>::Dim = 2;

    // << / >>
    template <typename T>
    std::ostream &operator<<(std::ostream &out, const vec2<T> &v){
      out << "(" << v.x << "," << v.y << ")";
      return out;
    }

    template <typename T>
    std::istream &operator>>(std::istream &in, vec2<T> &v){
      in >> v.x >> v.y;
      if(!in){
        v = 0;
      }
      return in;
    } 

namespace Math
{
    template <typename T>
    _CPU_AND_GPU_CODE_ bool floatEqual(const vec2<T> &lhs, const vec2<T> &rhs){
      return floatEqual(lhs.x, rhs.x) && floatEqual(lhs.y, rhs.y);
    }

    // min max
    template <typename T>
    _CPU_AND_GPU_CODE_ vec2<T> max(const vec2<T> &v, T x) {
      return vec2<T>(max(v.x, x),
                     max(v.y, x));
    }

    template <typename T>
    _CPU_AND_GPU_CODE_ vec2<T> max(const vec2<T> &lhs, const vec2<T> &rhs) {
      return vec2<T>(max(lhs.x, rhs.x),
                     max(lhs.y, rhs.y));
    }

    template <typename T>
    _CPU_AND_GPU_CODE_ vec2<T> min(const vec2<T> &v, T x) {
      return vec2<T>(min(v.x, x),
                     min(v.y, x));
    }

    template <typename T>
    _CPU_AND_GPU_CODE_ vec2<T> min(const vec2<T> &lhs, const vec2<T> &rhs) {
      return vec2<T>(min(lhs.x, rhs.x),
                     min(lhs.y, rhs.y));
    }

    // per-element func
    template<typename T>
    _CPU_AND_GPU_CODE_ vec2<float> frac(const vec2<T> &v) {
      return v.frac();
    }

    template<typename T>
    _CPU_AND_GPU_CODE_ vec2<T> round(const vec2<T> &v) {
      return v.round();
    }

    template<typename T>
    _CPU_AND_GPU_CODE_ vec2<T> ceil(const vec2<T> &v) {
      return v.ceil();
    }

    template<typename T>
    _CPU_AND_GPU_CODE_ vec2<T> floor(const vec2<T> &v) {
      return v.floor();
    }

    template<typename T>
    _CPU_AND_GPU_CODE_ vec2<T> abs(const vec2<T> &v) {
      return v.abs();
    }

    // statistics
    template <typename T>
    _CPU_AND_GPU_CODE_ typename vec2<T>::ValueType sum(const vec2<T> &v){
        return v.sum();
    }

    template <typename T>
    _CPU_AND_GPU_CODE_ double mean(const vec2<T> &v){
        return v.mean();
    }

    template <typename T>
    _CPU_AND_GPU_CODE_ double var(const vec2<T> &v){
        return v.var();
    }

} // namespace Math

} // namespace LLib

#endif // _LL_VEC2_H


// TODO : random

	// static const vec2<T> origin;
	// static const vec2<T> eX;
	// static const vec2<T> eY;