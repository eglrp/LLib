#ifndef _LL_VEC4_H
#define _LL_VEC4_H

#include "../../Utility/utility.h"
#include "vec3.h"

namespace LLib
{
    // 4D vector
    template <typename T>
    class vec4
    {
    public:
      // data
      using ValueType = T;
      static const int Dim;
      union{
          struct{
              T x, y, z, w;
          };
          struct{
              T r, g, b, a;
          };
          T array[4];
      };

      // static func
      _CPU_AND_GPU_CODE_ static vec4 zeros(){
        return vec4(0);
      }

      _CPU_AND_GPU_CODE_ static vec4 ones(){
        return vec4(1);
      }

      _CPU_AND_GPU_CODE_ static vec4 full(T x){
        return vec4(x);
      }

      // constructor
      _CPU_AND_GPU_CODE_ vec4(T x = 0){
        array[0] = array[1] = array[2] = array[3] = x;
      }

      _CPU_AND_GPU_CODE_ vec4(T x_, T y_, T z_, T w_){
        x = x_;
        y = y_;
        z = z_;
        w = w_;
      }

      template <typename U>
      _CPU_AND_GPU_CODE_ vec4(const vec4<U> &other){
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
      }

      template <typename U>
      _CPU_AND_GPU_CODE_ vec4(const U *other){
        array[0] = other[0];
        array[1] = other[1];
        array[2] = other[2];
        array[3] = other[3];
      }

      template <typename U>
      _CPU_AND_GPU_CODE_ vec4(const vec3<U> &other, U w_ = 1){
        x = other.x;
        y = other.y;
        z = other.z;
        w = w_;
      }

      // convert type
      template <typename U>
      _CPU_AND_GPU_CODE_ vec4<U> toType() const {
        return vec4<U>(*this);
      }

      // access
      _CPU_AND_GPU_CODE_ T &operator[](const uint i){
        assert(i < 4);
        return array[i];
      }

      _CPU_AND_GPU_CODE_ const T &operator[](const uint i) const {
        assert(i < 4);
        return array[i];
      }

      _CPU_AND_GPU_CODE_ T &at(int const i){
        assert(i < 4);
        return array[i];
      }

      _CPU_AND_GPU_CODE_ const T &at(int i) const {
        assert(i < 4);
        return array[i];
      }

      // assign
      _CPU_AND_GPU_CODE_ vec4 &operator=(const vec4 &other){
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        return *this;
      }

      // negative
      _CPU_AND_GPU_CODE_ vec4 operator-() const {
        return vec4(-x, -y, -z, -w);
      }

      // +
      _CPU_AND_GPU_CODE_ void operator+=(T x){
        array[0] += x;
        array[1] += x;
        array[2] += x;
        array[3] += x;
      }

      _CPU_AND_GPU_CODE_ void operator+=(const vec4 &other){
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
      }

      _CPU_AND_GPU_CODE_ friend vec4 operator+(const vec4 &lhs, const vec4 &rhs){
        vec4 result(lhs);
        result += rhs;
        return result;
      }

      // -
      _CPU_AND_GPU_CODE_ void operator-=(T x){
        array[0] -= x;
        array[1] -= x;
        array[2] -= x;
        array[3] -= x;
      }

      _CPU_AND_GPU_CODE_ void operator-=(const vec4 &other){
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
      }

      _CPU_AND_GPU_CODE_ friend vec4 operator-(const vec4 &lhs, const vec4 &rhs){
        vec4 result(lhs);
        result -= rhs;
        return result;
      }

      // *
      _CPU_AND_GPU_CODE_ void operator*=(T x){
        array[0] *= x;
        array[1] *= x;
        array[2] *= x;
        array[3] *= x;
      }

      _CPU_AND_GPU_CODE_ void operator*=(const vec4 &other){
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
      }

      _CPU_AND_GPU_CODE_ friend vec4 operator*(T x, const vec4 &v){
          vec4 result(v);
          result *= x;
          return result;
      }
      _CPU_AND_GPU_CODE_ friend vec4 operator*(const vec4 &v, T x){
          vec4 result(v);
          result *= x;
          return result;
      }

      _CPU_AND_GPU_CODE_ friend vec4 operator*(const vec4 &lhs, const vec4 &rhs){
        vec4 result(lhs);
        result *= rhs;
        return result;
      }

      // /
      _CPU_AND_GPU_CODE_ _CPU_AND_GPU_CODE_ bool all() const {
        for(size_t i = 0; i < 4; i++)
          if(!array[i]) return false;

        return true;
      }

      _CPU_AND_GPU_CODE_ void operator/=(T x){
        assert(x != 0);
        array[0] /= x;
        array[1] /= x;
        array[2] /= x;
        array[3] /= x;
      }

      _CPU_AND_GPU_CODE_ void operator/=(const vec4 &other){
        assert(other.all());
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
      }

      _CPU_AND_GPU_CODE_ friend vec4 operator/(const vec4 &lhs, const vec4 &rhs){
        vec4 result(lhs);
        result /= rhs;
        return result;
      }

      // == / !=

      _CPU_AND_GPU_CODE_ bool operator==(const vec4 &other) const {
        return (x == other.x && y == other.y && z == other.z && w == other.w);
      }

      _CPU_AND_GPU_CODE_ bool operator!=(const vec4 &other) const {
        return !(*this == other);
      }

      // dot
      _CPU_AND_GPU_CODE_ double dot(const vec4 &other) const {
        return (x*other.x + y*other.y + z*other.z + w*other.w);
      }

      _CPU_AND_GPU_CODE_ friend double dot(const vec4 &lhs, const vec4 &rhs){
        return (lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z + lhs.w*rhs.w);
      }

      // length
      _CPU_AND_GPU_CODE_ double lengthSq() const {
        return (x*x + y*y + z*z + w*w);
      }

      _CPU_AND_GPU_CODE_ double length() const {
        return sqrt(x*x + y*y + z*z + w*w);
      }

      // distance
      _CPU_AND_GPU_CODE_ friend double distSq(const vec4 &lhs, const vec4 &rhs){
        return (lhs.x-rhs.x)*(lhs.x-rhs.x) + (lhs.y-rhs.y)*(lhs.y-rhs.y) + (lhs.z-rhs.z)*(lhs.z-rhs.z) + (lhs.w-rhs.w)*(lhs.w-rhs.w);
      }

      _CPU_AND_GPU_CODE_ friend double dist(const vec4 &lhs, const vec4 &rhs){
        return sqrt((lhs.x-rhs.x)*(lhs.x-rhs.x) + (lhs.y-rhs.y)*(lhs.y-rhs.y) + (lhs.z-rhs.z)*(lhs.z-rhs.z) + (lhs.w-rhs.w)*(lhs.w-rhs.w));
      }

      // normalize
      _CPU_AND_GPU_CODE_ vec4 normalize(){
        double l = length();
        if(l < EPS) return *this;
        double ratio = 1.0/l;
        *this *= ratio;
        return *this;
      }

      _CPU_AND_GPU_CODE_ vec4 getNormalize() const {
        vec4 result(*this);
        return result.normalize();
      }

      // get data pointer
      _CPU_AND_GPU_CODE_ T *getData(){
        return array;
      }

      // per-element func
      _CPU_AND_GPU_CODE_ vec4<float> frac() const {
        return vec4<float>(Math::frac(x), Math::frac(y), Math::frac(z), Math::frac(w));
      }

      _CPU_AND_GPU_CODE_ vec4 round() const {
        return vec4(Math::round(x), Math::round(y), Math::round(z), Math::round(w));
      }

      _CPU_AND_GPU_CODE_ vec4 ceil() const {
        return vec4(Math::ceil(x), Math::ceil(y), Math::ceil(z), Math::ceil(w));
      }

      _CPU_AND_GPU_CODE_ vec4 floor() const {
        return vec4(Math::floor(x), Math::floor(y), Math::floor(z), Math::floor(w));
      }

      _CPU_AND_GPU_CODE_ vec4 abs() const {
        return vec4(Math::abs(x), Math::abs(y), Math::abs(z), Math::abs(w));
      }

      // statistics
      _CPU_AND_GPU_CODE_ T sum() const {
        return (x + y + z + w);
      }

      _CPU_AND_GPU_CODE_ double mean() const {
        return sum()/4;
      }

      _CPU_AND_GPU_CODE_ double var() const {
        T m = mean();
        vec4 diff = *this - m;
        return diff.dot(diff)/4;
      }

      // *************************************************************************

      // cross (of .xyz)
      _CPU_AND_GPU_CODE_ vec4 operator^(const vec4 &other){
        return vec4(y*other.z - z*other.y,  z*other.x - x*other.z, x*other.y - y*other.x, 1);
      }

      _CPU_AND_GPU_CODE_ vec4 cross(const vec4 &other){
        return vec4(y*other.z - z*other.y,  z*other.x - x*other.z, x*other.y - y*other.x, 1);
      }

      _CPU_AND_GPU_CODE_ friend vec4 cross(const vec4 &lhs, const vec4 &rhs){
        vec4 result(lhs);
        return result.cross(rhs);
      }

      // dehomogenize
      _CPU_AND_GPU_CODE_ vec4 &dehomogenize()
      {
          assert(array[3] != 0);
          array[0] /= array[3];
          array[1] /= array[3];
          array[2] /= array[3];
          array[3] /= array[3];
          return *this;
      }

      _CPU_AND_GPU_CODE_ vec3<T> getDehomogenize() const {
          assert(array[3] != 0);
          return vec3<T>(array[0]/array[3], array[1]/array[3], array[2]/array[3]);
      }

    }; // class vec4

    template <typename T> const int vec4<T>::Dim = 4;

    // << / >>
    template <typename T>
    std::ostream &operator<<(std::ostream &out, const vec4<T> &v){
      out << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
      return out;
    }

    template <typename T>
    std::istream &operator>>(std::istream &in, vec4<T> &v){
      in >> v.x >> v.y >> v.z >> v.w;
      if(!in){
        v = 0;
      }
      return in;
    }

namespace Math
    {

    template <typename T>
    _CPU_AND_GPU_CODE_ bool floatEqual(const vec4<T> &lhs, const vec4<T> &rhs){
      return floatEqual(lhs.x, rhs.x) && 
             floatEqual(lhs.y, rhs.y) &&
             floatEqual(lhs.z, rhs.z) &&
             floatEqual(lhs.w, rhs.w);
    }

    // min max
    template <typename T>
    _CPU_AND_GPU_CODE_ vec4<T> max(const vec4<T> &v, T x) {
      return vec4<T>(max(v.x, x),
                     max(v.y, x),
                     max(v.z, x),
                     max(v.w, x));
    }
  
    template <typename T>
    _CPU_AND_GPU_CODE_ vec4<T> max(const vec4<T> &lhs, const vec4<T> &rhs) {
      return vec4<T>(max(lhs.x, rhs.x),
                     max(lhs.y, rhs.y),
                     max(lhs.z, rhs.z),
                     max(lhs.w, rhs.w));
    }
  
    template <typename T>
    _CPU_AND_GPU_CODE_ vec4<T> min(const vec4<T> &v, T x) {
      return vec4<T>(min(v.x, x),
                     min(v.y, x),
                     min(v.z, x),
                     min(v.w, x));
    }
  
    template <typename T>
    _CPU_AND_GPU_CODE_ vec4<T> min(const vec4<T> &lhs, const vec4<T> &rhs) {
      return vec4<T>(min(lhs.x, rhs.x),
                     min(lhs.y, rhs.y),
                     min(lhs.z, rhs.z),
                     min(lhs.w, rhs.w));
    }  
    
    // per-element func
    template<typename T>
    _CPU_AND_GPU_CODE_ vec4<float> frac(const vec4<T> &v) {
      return v.frac();
    }
    
    template<typename T>
    _CPU_AND_GPU_CODE_ vec4<T> round(const vec4<T> &v) {
      return v.round();
    }
    
    template<typename T>
    _CPU_AND_GPU_CODE_ vec4<T> ceil(const vec4<T> &v) {
      return v.ceil();
    }
    
    template<typename T>
    _CPU_AND_GPU_CODE_ vec4<T> floor(const vec4<T> &v) {
      return v.floor();
    }
    
    template<typename T>
    _CPU_AND_GPU_CODE_ vec4<T> abs(const vec4<T> &v) {
      return v.abs();
    }

    // statistics
    template <typename T>
    _CPU_AND_GPU_CODE_ typename vec4<T>::ValueType sum(const vec4<T> &v){
        return v.sum();
    }

    template <typename T>
    _CPU_AND_GPU_CODE_ double mean(const vec4<T> &v){
        return v.mean();
    }

    template <typename T>
    _CPU_AND_GPU_CODE_ double var(const vec4<T> &v){
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