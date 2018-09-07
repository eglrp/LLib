#ifndef _LL_VEC6_H
#define _LL_VEC6_H

#include "../../Utility/utility.h"

namespace LLib
{
    // 6D vector
    template <typename T>
    class vec6
    {
    public:
      // data
      using ValueType = T;
      static const uint Dim;
      union{
          struct{
              vec3<T> rot_;
              vec3<T> t_;
          };
          T array[6];
      };

      // static func
      _CPU_AND_GPU_CODE_ static vec6 zeros(){
        return vec6(0);
      }

      _CPU_AND_GPU_CODE_ static vec6 ones(){
        return vec6(1);
      }

      _CPU_AND_GPU_CODE_ static vec6 full(T x){
        return vec6(x);
      }

      // constructor
      _CPU_AND_GPU_CODE_ vec6(T x = 0){
        array[0] = array[1] = array[2] = array[3] = array[4] = array[5] = x;
      }

      _CPU_AND_GPU_CODE_ vec6(T x0, T x1, T x2, T x3, T x4, T x5){
        array[0] = x0;
        array[1] = x1;
        array[2] = x2;
        array[3] = x3;
        array[4] = x4;
        array[5] = x5;
      }

      template <typename U>
      _CPU_AND_GPU_CODE_ vec6(const vec6<U> &other){
        array[0] = other[0];
        array[1] = other[1];
        array[2] = other[2];
        array[3] = other[3];
        array[4] = other[4];
        array[5] = other[5];
      }

      template <typename U>
      _CPU_AND_GPU_CODE_ vec6(const U *other){
        array[0] = other[0];
        array[1] = other[1];
        array[2] = other[2];
        array[3] = other[3];
        array[4] = other[4];
        array[5] = other[5];
      }

      _CPU_AND_GPU_CODE_ vec6(const vec3<T> &rot, const vec3<T> &t){
        rot_ = rot;
        t_ = t;
      }

      // convert type
      template <typename U>
      _CPU_AND_GPU_CODE_ vec6<U> toType() const {
        return vec6<U>(*this);
      }

      // access
      _CPU_AND_GPU_CODE_ T &operator[](const uint i){
        assert(i < 6);
        return array[i];
      }

      _CPU_AND_GPU_CODE_ const T &operator[](const uint i) const {
        assert(i < 6);
        return array[i];
      }

      _CPU_AND_GPU_CODE_ T &at(const uint i){
        assert(i < 6);
        return array[i];
      }

      _CPU_AND_GPU_CODE_ const T &at(const uint i) const {
        assert(i < 6);
        return array[i];
      }

      // assign
      _CPU_AND_GPU_CODE_ vec6 &operator=(const vec6 &other){
        array[0] = other[0];
        array[1] = other[1];
        array[2] = other[2];
        array[3] = other[3];
        array[4] = other[4];
        array[5] = other[5];
        return *this;
      }

      // negative
      _CPU_AND_GPU_CODE_ vec6 operator-() const {
        return vec6(-array[0], -array[1], -array[2], -array[3], -array[4], -array[5]);
      }

      // +
      _CPU_AND_GPU_CODE_ void operator+=(T x){
        array[0] += x;
        array[1] += x;
        array[2] += x;
        array[3] += x;
        array[4] += x;
        array[5] += x;
      }

      _CPU_AND_GPU_CODE_ void operator+=(const vec6 &other){
        array[0] += other[0];
        array[1] += other[1];
        array[2] += other[2];
        array[3] += other[3];
        array[4] += other[4];
        array[5] += other[5];
      }

      _CPU_AND_GPU_CODE_ friend vec6 operator+(const vec6 &lhs, const vec6 &rhs){
        vec6 result(lhs);
        result += rhs;
        return result;
      }

      // -
      _CPU_AND_GPU_CODE_ void operator-=(T x){
        array[0] -= x;
        array[1] -= x;
        array[2] -= x;
        array[3] -= x;
        array[4] -= x;
        array[5] -= x;
      }

      _CPU_AND_GPU_CODE_ void operator-=(const vec6 &other){
        array[0] -= other[0];
        array[1] -= other[1];
        array[2] -= other[2];
        array[3] -= other[3];
        array[4] -= other[4];
        array[5] -= other[5];
      }

      _CPU_AND_GPU_CODE_ friend vec6 operator-(const vec6 &lhs, const vec6 &rhs){
        vec6 result(lhs);
        result -= rhs;
        return result;
      }

      // *
      _CPU_AND_GPU_CODE_ void operator*=(T x){
        array[0] *= x;
        array[1] *= x;
        array[2] *= x;
        array[3] *= x;
        array[4] *= x;
        array[5] *= x;
      }

      _CPU_AND_GPU_CODE_ void operator*=(const vec6 &other){
        array[0] *= other[0];
        array[1] *= other[1];
        array[2] *= other[2];
        array[3] *= other[3];
        array[4] *= other[4];
        array[5] *= other[5];
      }

      _CPU_AND_GPU_CODE_ friend vec6 operator*(T x, const vec6 &v){
          vec6 result(v);
          result *= x;
          return result;
      }
      _CPU_AND_GPU_CODE_ friend vec6 operator*(const vec6 &v, T x){
          vec6 result(v);
          result *= x;
          return result;
      }

      _CPU_AND_GPU_CODE_ friend vec6 operator*(const vec6 &lhs, const vec6 &rhs){
        vec6 result(lhs);
        result *= rhs;
        return result;
      }

      // /

      _CPU_AND_GPU_CODE_ bool all() const {
        for(size_t i = 0; i < 6; i++)
          if(!array[i]) return false;

        return true;
      }

      _CPU_AND_GPU_CODE_ void operator/=(T x){
        assert(x != 0);
        array[0] /= x;
        array[1] /= x;
        array[2] /= x;
        array[3] /= x;
        array[4] /= x;
        array[5] /= x;
      }

      _CPU_AND_GPU_CODE_ void operator/=(const vec6 &other){
        assert(other.all());
        array[0] /= other[0];
        array[1] /= other[1];
        array[2] /= other[2];
        array[3] /= other[3];
        array[4] /= other[4];
        array[5] /= other[5];
      }

      _CPU_AND_GPU_CODE_ friend vec6 operator/(const vec6 &lhs, const vec6 &rhs){
        vec6 result(lhs);
        result /= rhs;
        return result;
      }

      // == / !=
      _CPU_AND_GPU_CODE_ bool operator==(const vec6 &other) const {
        for(size_t i = 0; i < 6; i++)
          if(array[i] != other[i]) return false;
        
        return true;
      }

      _CPU_AND_GPU_CODE_ bool operator!=(const vec6 &other) const {
        return !(*this == other);
      }

      // dot
      _CPU_AND_GPU_CODE_ double dot(const vec6 &other) const {
        return ((*this)*other).sum();
      }

      _CPU_AND_GPU_CODE_ friend double dot(const vec6 &lhs, const vec6 &rhs){
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
      _CPU_AND_GPU_CODE_ friend double distSq(const vec6 &lhs, const vec6 &rhs){
        vec6 diff = lhs - rhs;
        return diff.lengthSq();
      }

      _CPU_AND_GPU_CODE_ friend double dist(const vec6 &lhs, const vec6 &rhs){
        vec6 diff = lhs - rhs;
        return diff.length();
      }

      // normalize
      _CPU_AND_GPU_CODE_ vec6 normalize(){
        double l = length();
        if(l < EPS) return *this;
        double ratio = 1.0/l;
        *this *= ratio;
        return *this;
      }

      _CPU_AND_GPU_CODE_ vec6 getNormalize() const {
        vec6 result(*this);
        return result.normalize();
      }

      // get data pointer
      _CPU_AND_GPU_CODE_ T *getData(){
        return array;
      }

      // per-element func
      _CPU_AND_GPU_CODE_ vec6<float> frac() const {
        return vec6<float>(Math::frac(array[0]), Math::frac(array[1]), Math::frac(array[2]), Math::frac(array[3]), Math::frac(array[4]), Math::frac(array[5]));
      }
      
      _CPU_AND_GPU_CODE_ vec6 round() const {
        return vec6<T>(Math::round(array[0]), Math::round(array[1]), Math::round(array[2]), Math::round(array[3]), Math::round(array[4]), Math::round(array[5]));
      }
      
      _CPU_AND_GPU_CODE_ vec6 ceil() const {
        return vec6<T>(Math::ceil(array[0]), Math::ceil(array[1]), Math::ceil(array[2]), Math::ceil(array[3]), Math::ceil(array[4]), Math::ceil(array[5]));
      }
      
      _CPU_AND_GPU_CODE_ vec6 floor() const {
        return vec6<T>(Math::floor(array[0]), Math::floor(array[1]), Math::floor(array[2]), Math::floor(array[3]), Math::floor(array[4]), Math::floor(array[5]));
      }
      
      _CPU_AND_GPU_CODE_ vec6 abs() const {
        return vec6<T>(Math::abs(array[0]), Math::abs(array[1]), Math::abs(array[2]), Math::abs(array[3]), Math::abs(array[4]), Math::abs(array[5]));
      }

      // statistics
      _CPU_AND_GPU_CODE_ T sum() const {
        return(array[0] + array[1] + array[2] + array[3] + array[4] + array[5]);
      }

      _CPU_AND_GPU_CODE_ double mean() const {
        return sum()/6;
      }

      _CPU_AND_GPU_CODE_ double var() const {
        T m = mean();
        vec6 diff = *this - m;
        return diff.dot(diff)/6;
      }

      // *************************************************************************
      
      // get set
      _CPU_AND_GPU_CODE_ const vec3<T> &getRot() const {
        return rot_;
      }

      _CPU_AND_GPU_CODE_ const vec3<T> &gett() const {
        return t_;
      }

      _CPU_AND_GPU_CODE_ void setRot(const vec3<T> &rot){
        rot_ = rot;
      }

      _CPU_AND_GPU_CODE_ void setRot(T r1, T r2, T r3){
        rot_ = vec3<T>(r1, r2, r3);
      }

      _CPU_AND_GPU_CODE_ void sett(const vec3<T> &t){
        t_ = t;
      }

      _CPU_AND_GPU_CODE_ void sett(T t1, T t2, T t3){
        t_ = vec3<T>(t1, t2, t3);
      }

    }; // class vec4

    template <typename T> const uint vec6<T>::Dim = 6;

    // << / >>
    template <typename T>
    std::ostream &operator<<(std::ostream &out, const vec6<T> &v){
      out << "(" << v[0] << "," << v[1] << "," << v[2] << "," << v[3] << "," << v[4] << "," << v[5] << ")";
      return out;
    }

    template <typename T>
    std::istream &operator>>(std::istream &in, vec6<T> &v){
      in >> v[0] >> v[1] >> v[2] >> v[3] >> v[4] >> v[5];
      if(!in){
        v = 0;
      }
      return in;
    }

namespace Math
    {
    
    template <typename T>
    _CPU_AND_GPU_CODE_ bool floatEqual(const vec6<T> &lhs, const vec6<T> &rhs){
      return floatEqual(lhs[0], rhs[0]) && 
             floatEqual(lhs[1], rhs[1]) &&
             floatEqual(lhs[2], rhs[2]) &&
             floatEqual(lhs[3], rhs[3]) &&
             floatEqual(lhs[4], rhs[4]) &&
             floatEqual(lhs[5], rhs[5]);
    }

    // min max
    template <typename T>
    _CPU_AND_GPU_CODE_ vec6<T> max(const vec6<T> &v, T x) {
      return vec6<T>(max(v[0], x),
                     max(v[1], x),
                     max(v[2], x),
                     max(v[3], x),
                     max(v[4], x),
                     max(v[5], x));
    }
    
    template <typename T>
    _CPU_AND_GPU_CODE_ vec6<T> max(const vec6<T> &lhs, const vec6<T> &rhs) {
      return vec6<T>(max(lhs[0], rhs[0]),
                     max(lhs[1], rhs[1]),
                     max(lhs[2], rhs[2]),
                     max(lhs[3], rhs[3]),
                     max(lhs[4], rhs[4]),
                     max(lhs[5], rhs[5]));
    }
  
    template <typename T>
    _CPU_AND_GPU_CODE_ vec6<T> min(const vec6<T> &v, T x) {
      return vec6<T>(min(v[0], x),
                     min(v[1], x),
                     min(v[2], x),
                     min(v[3], x),
                     min(v[4], x),
                     min(v[5], x));
    }
    
    template <typename T>
    _CPU_AND_GPU_CODE_ vec6<T> min(const vec6<T> &lhs, const vec6<T> &rhs) {
      return vec6<T>(min(lhs[0], rhs[0]),
                     min(lhs[1], rhs[1]),
                     min(lhs[2], rhs[2]),
                     min(lhs[3], rhs[3]),
                     min(lhs[4], rhs[4]),
                     min(lhs[5], rhs[5]));
    }     
    
    // per-element func
    template<typename T>
    _CPU_AND_GPU_CODE_ vec6<float> frac(const vec6<T> &v) {
      return v.frac();
    }
    
    template<typename T>
    _CPU_AND_GPU_CODE_ vec6<T> round(const vec6<T> &v) {
      return v.round();
    }
    
    template<typename T>
    _CPU_AND_GPU_CODE_ vec6<T> ceil(const vec6<T> &v) {
      return v.ceil();
    }
    
    template<typename T>
    _CPU_AND_GPU_CODE_ vec6<T> floor(const vec6<T> &v) {
      return v.floor();
    }
    
    template<typename T>
    _CPU_AND_GPU_CODE_ vec6<T> abs(const vec6<T> &v) {
      return v.abs();
    }

    // statistics
    template <typename T>
    _CPU_AND_GPU_CODE_ typename vec6<T>::ValueType sum(const vec6<T> &v){
        return v.sum();
    }

    template <typename T>
    _CPU_AND_GPU_CODE_ double mean(const vec6<T> &v){
        return v.mean();
    }

    template <typename T>
    _CPU_AND_GPU_CODE_ double var(const vec6<T> &v){
        return v.var();
    }
    
} // namespace Math

} // namespace LLib

#endif // _LL_VEC4_H

// TODO : random

		// static const vec4<T> origin;
		// static const vec4<T> eX;
		// static const vec4<T> eY;
		// static const vec4<T> eZ;
		// static const vec4<T> eW;