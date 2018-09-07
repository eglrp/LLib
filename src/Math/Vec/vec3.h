#ifndef _LL_VEC3_H
#define _LL_VEC3_H

#include "../../Utility/utility.h"

namespace LLib
{
    // 3D vector
    template <typename T>
    class vec3
    {
    public:
      // data
      using ValueType = T;
      static const int Dim;
      union{
          struct{
              T x, y, z;
          };
          struct{
              T r, g, b;
          };
          struct{
              T yaw, pitch, roll;
          };
          T array[3];
      };

      // static func
      _CPU_AND_GPU_CODE_ static vec3 zeros(){
        return vec3(0);
      }

      _CPU_AND_GPU_CODE_ static vec3 ones(){
        return vec3(1);
      }

      _CPU_AND_GPU_CODE_ static vec3 full(T x){
        return vec3(x);
      }

      // constructor
      _CPU_AND_GPU_CODE_ vec3(T x = 0){
        array[0] = array[1] = array[2] = x;
      }

      _CPU_AND_GPU_CODE_ vec3(T x_, T y_, T z_){
        x = x_;
        y = y_;
        z = z_;
      }

      template <typename U>      
      _CPU_AND_GPU_CODE_ vec3(const vec3<U> &other){
        x = other.x;
        y = other.y;
        z = other.z;
      }

      template <typename U>
      _CPU_AND_GPU_CODE_ vec3(const U *other){
        array[0] = other[0];
        array[1] = other[1];
        array[2] = other[2];
      }

      // convert type
      template <typename U>
      _CPU_AND_GPU_CODE_ vec3<U> toType() const {
        return vec3<U>(*this);
      }

      // access
      _CPU_AND_GPU_CODE_ T &operator[](const uint i){
        assert(i < 3);
        return array[i];
      }

      _CPU_AND_GPU_CODE_ const T &operator[](const uint i) const{
        assert(i < 3);
        return array[i];
      }

      _CPU_AND_GPU_CODE_ T &at(const uint i){
        assert(i < 3);
        return array[i];
      }

      _CPU_AND_GPU_CODE_ const T &at(const uint i) const {
        assert(i < 3);
        return array[i];
      }

      // assign
      _CPU_AND_GPU_CODE_ vec3 &operator=(const vec3 &other){
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
      }

      // negative
      _CPU_AND_GPU_CODE_ vec3 operator-() const {
        return vec3(-x, -y, -z);
      }

      // +
      _CPU_AND_GPU_CODE_ void operator+=(T x){
        array[0] += x;
        array[1] += x;
        array[2] += x;
      }

      _CPU_AND_GPU_CODE_ void operator+=(const vec3 &other){
        x += other.x;
        y += other.y;
        z += other.z;
      }

      _CPU_AND_GPU_CODE_ friend vec3 operator+(const vec3 &lhs, const vec3 &rhs){
        vec3 result(lhs);
        result += rhs;
        return result;
      }

      // -
      _CPU_AND_GPU_CODE_ void operator-=(T x){
        array[0] -= x;
        array[1] -= x;
        array[2] -= x;
      }

      _CPU_AND_GPU_CODE_ void operator-=(const vec3 &other){
        x -= other.x;
        y -= other.y;
        z -= other.z;
      }

      _CPU_AND_GPU_CODE_ friend vec3 operator-(const vec3 &lhs, const vec3 &rhs){
        vec3 result(lhs);
        result -= rhs;
        return result;
      }

      // *
      _CPU_AND_GPU_CODE_ void operator*=(T x){
        array[0] *= x;
        array[1] *= x;
        array[2] *= x;
      }

      _CPU_AND_GPU_CODE_ void operator*=(const vec3 &other){
        x *= other.x;
        y *= other.y;
        z *= other.z;
      }

      _CPU_AND_GPU_CODE_ friend vec3 operator*(T x, const vec3 &v){
          vec3 result(v);
          result *= x;
          return result;
      }
      _CPU_AND_GPU_CODE_ friend vec3 operator*(const vec3 &v, T x){
          vec3 result(v);
          result *= x;
          return result;
      }

      _CPU_AND_GPU_CODE_ friend vec3 operator*(const vec3 &lhs, const vec3 &rhs){
        vec3 result(lhs);
        result *= rhs;
        return result;
      }

      // /
      _CPU_AND_GPU_CODE_ _CPU_AND_GPU_CODE_ bool all() const {
        for(size_t i = 0; i < 3; i++)
          if(!array[i]) return false;

        return true;
      }

      _CPU_AND_GPU_CODE_ void operator/=(T x){
        assert(x != 0);
        array[0] /= x;
        array[1] /= x;
        array[2] /= x;
      }

      _CPU_AND_GPU_CODE_ void operator/=(const vec3 &other){
        assert(other.all());
        x /= other.x;
        y /= other.y;
        z /= other.z;
      }

      _CPU_AND_GPU_CODE_ friend vec3 operator/(const vec3 &lhs, const vec3 &rhs){
        vec3 result(lhs);
        result /= rhs;
        return result;
      }

      // == / !=
      _CPU_AND_GPU_CODE_ bool operator==(const vec3 &other) const {
        return (x == other.x && y == other.y && z == other.z);
      }

      _CPU_AND_GPU_CODE_ bool operator!=(const vec3 &other) const {
        return !(*this == other);
      }

      // dot
      _CPU_AND_GPU_CODE_ double dot(const vec3 &other) const {
        return (x*other.x + y*other.y + z*other.z);
      }

      _CPU_AND_GPU_CODE_ friend double dot(const vec3 &lhs, const vec3 &rhs){
        return (lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z);
      }

      // length
      _CPU_AND_GPU_CODE_ double lengthSq() const {
        return (x*x + y*y + z*z);
      }

      _CPU_AND_GPU_CODE_ double length() const {
        return sqrt(x*x + y*y + z*z);
      }

      // distance
      _CPU_AND_GPU_CODE_ friend double distSq(const vec3 &lhs, const vec3 &rhs){
        return (lhs.x-rhs.x)*(lhs.x-rhs.x) + (lhs.y-rhs.y)*(lhs.y-rhs.y) + (lhs.z-rhs.z)*(lhs.z-rhs.z);
      }

      _CPU_AND_GPU_CODE_ friend double dist(const vec3 &lhs, const vec3 &rhs){
        return sqrt((lhs.x-rhs.x)*(lhs.x-rhs.x) + (lhs.y-rhs.y)*(lhs.y-rhs.y) + (lhs.z-rhs.z)*(lhs.z-rhs.z));
      }

      // normalize
      _CPU_AND_GPU_CODE_ vec3 normalize(){
        double l = length();
        if(l < EPS) return *this;
        double ratio = 1.0/l;
        *this *= ratio;
        return *this;
      }

      _CPU_AND_GPU_CODE_ vec3 getNormalize() const {
        vec3 result(*this);
        return result.normalize();
      }

      // get data pointer
      _CPU_AND_GPU_CODE_ T *getData(){
        return array;
      }

      // per-element func
      _CPU_AND_GPU_CODE_ vec3<float> frac() const {
        return vec3<float>(Math::frac(x), Math::frac(y), Math::frac(z));
      }

      _CPU_AND_GPU_CODE_ vec3 round() const {
        return vec3(Math::round(x), Math::round(y), Math::round(z));
      }

      _CPU_AND_GPU_CODE_ vec3 ceil() const {
        return vec3(Math::ceil(x), Math::ceil(y), Math::ceil(z));
      }

      _CPU_AND_GPU_CODE_ vec3 floor() const {
        return vec3(Math::floor(x), Math::floor(y), Math::floor(z));
      }

      _CPU_AND_GPU_CODE_ vec3 abs() const {
        return vec3(Math::abs(x), Math::abs(y), Math::abs(z));
      }

      // statistics
      _CPU_AND_GPU_CODE_ T sum() const {
        return (x + y + z);
      }

      _CPU_AND_GPU_CODE_ double mean() const {
        return sum()/3;
      }

      _CPU_AND_GPU_CODE_ double var() const {
        T m = mean();
        vec3 diff = *this - m;
        return diff.dot(diff)/3;
      }

      // *************************************************************************

      // cross
      _CPU_AND_GPU_CODE_ vec3 operator^(const vec3 &other) const {
        return vec3(y*other.z - z*other.y,  z*other.x - x*other.z, x*other.y - y*other.x);
      }

      _CPU_AND_GPU_CODE_ vec3 cross(const vec3 &other){
        return vec3(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
      }

      _CPU_AND_GPU_CODE_ friend vec3 cross(const vec3 &lhs, const vec3 &rhs){
        vec3 result(lhs);
        return result.cross(rhs);
      }

      // TODO
      // homogenize
      // _CPU_AND_GPU_CODE_ vec4<T> getHomogenize() const {
      //     return vec4<T>(*this);
      // }

    }; // class vec3

    template <typename T> const int vec3<T>::Dim = 3;

    // << / >>
    template <typename T>
    std::ostream &operator<<(std::ostream &out, const vec3<T> &v){
      out << "(" << v.x << "," << v.y << "," << v.z << ")";
      return out;
    }

    template <typename T>
    std::istream &operator>>(std::istream &in, vec3<T> &v){
      in >> v.x >> v.y >> v.z;
      if(!in){
        v = 0;
      }
      return in;
    }


namespace Math
    {

    template <typename T>
    _CPU_AND_GPU_CODE_ bool floatEqual(const vec3<T> &lhs, const vec3<T> &rhs){
      return floatEqual(lhs.x, rhs.x) && 
             floatEqual(lhs.y, rhs.y) &&
             floatEqual(lhs.z, rhs.z);
    }

    // min max
    template <typename T>
    _CPU_AND_GPU_CODE_ vec3<T> max(const vec3<T> &v, T x) {
      return vec3<T>(max(v.x, x),
                     max(v.y, x),
                     max(v.z, x));
    }

    template <typename T>
    _CPU_AND_GPU_CODE_ vec3<T> max(const vec3<T> &lhs, const vec3<T> &rhs) {
      return vec3<T>(max(lhs.x, rhs.x),
                     max(lhs.y, rhs.y),
                     max(lhs.z, rhs.z));
    }

    template <typename T>
    _CPU_AND_GPU_CODE_ vec3<T> min(const vec3<T> &v, T x) {
      return vec3<T>(min(v.x, x),
                    min(v.y, x),
                    min(v.z, x));
    }

    template <typename T>
    _CPU_AND_GPU_CODE_ vec3<T> min(const vec3<T> &lhs, const vec3<T> &rhs) {
      return vec3<T>(min(lhs.x, rhs.x),
                     min(lhs.y, rhs.y),
                     min(lhs.z, rhs.z));
    }

    // per-element func
    template<typename T>
    _CPU_AND_GPU_CODE_ vec3<float> frac(const vec3<T> &v) {
      return v.frac();
    }

    template<typename T>
    _CPU_AND_GPU_CODE_ vec3<T> round(const vec3<T> &v) {
      return v.round();
    }

    template<typename T>
    _CPU_AND_GPU_CODE_ vec3<T> ceil(const vec3<T> &v) {
      return v.ceil();
    }

    template<typename T>
    _CPU_AND_GPU_CODE_ vec3<T> floor(const vec3<T> &v) {
      return v.floor();
    }

    template<typename T>
    _CPU_AND_GPU_CODE_ vec3<T> abs(const vec3<T> &v) {
      return v.abs();
    }
    
    // statistics
    template <typename T>
    _CPU_AND_GPU_CODE_ typename vec3<T>::ValueType sum(const vec3<T> &v){
        return v.sum();
    }

    template <typename T>
    _CPU_AND_GPU_CODE_ double mean(const vec3<T> &v){
        return v.mean();
    }

    template <typename T>
    _CPU_AND_GPU_CODE_ double var(const vec3<T> &v){
        return v.var();
    }

} // namespace Math

} // namespace LLib

#endif // _LL_VEC3_H

// TODO : random


       // returns the angle between two vectors *in degrees*
    // static T angleBetween(const vec3<T> &v0, const vec3<T> &v1) {
    //     T l0 = v0.length();
    //     T l1 = v1.length();
    //     if(l0 <= 0.0f || l1 <= 0.0f)
    //         return 0.0f;
    //     else
    //         return math::radiansToDegrees(acosf(math::clamp(vec3<T>::dot(v0, v1) / l0 / l1, -1.0f, 1.0f)));
    // }

    // 	static const vec3<T> origin;
	// static const vec3<T> eX;
	// static const vec3<T> eY;
	// static const vec3<T> eZ;

    //     template<class T>
    // inline T triangleArea(const vec3<T>& v0, const vec3<T>& v1, const vec3<T>& v2) {
    //     return ((v1 - v0) ^ (v2 - v0)).length() * (T)0.5;
    // }

    // template<class T>
    // inline T triangleArea(const vec2<T>& v0, const vec2<T>& v1, const vec2<T>& v2) {
    //     return triangleArea(vec3<T>(v0, 0.0f),
    //                         vec3<T>(v1, 0.0f),
    //                         vec3<T>(v2, 0.0f));
    // }

    // template<class T>
    // inline vec3<T> triangleNormal(const vec3<T>& v0, const vec3<T>& v1, const vec3<T>& v2) {
    //     return ((v1 - v0) ^ (v2 - v0)).getNormalized();
    // }

    // template<class T>
    // inline float trianglePointDistSq(const vec3<T>& t0, const vec3<T>& t1, const vec3<T>& t2, const vec3<T>& p) {
    //     const vec3<T> edge0 = t1 - t0;
    //     const vec3<T> edge1 = t2 - t0;
    //     const vec3<T> v0 = t0 - p;

    //     float a = edge0 | edge0;
    //     float b = edge0 | edge1;
    //     float c = edge1 | edge1;
    //     float d = edge0 | v0;
    //     float e = edge1 | v0;

    //     float det = a*c - b*b;
    //     float s = b*e - c*d;
    //     float t = b*d - a*e;

    //     if (s + t < det)
    //     {
    //         if (s < 0.f)
    //         {
    //             if (t < 0.f)
    //             {
    //                 if (d < 0.f)
    //                 {
    //                     s = clamp(-d / a, 0.f, 1.f);
    //                     t = 0.f;
    //                 }
    //                 else
    //                 {
    //                     s = 0.f;
    //                     t = clamp(-e / c, 0.f, 1.f);
    //                 }
    //             }
    //             else
    //             {
    //                 s = 0.f;
    //                 t = clamp(-e / c, 0.f, 1.f);
    //             }
    //         }
    //         else if (t < 0.f)
    //         {
    //             s = clamp(-d / a, 0.f, 1.f);
    //             t = 0.f;
    //         }
    //         else
    //         {
    //             float invDet = 1.f / det;
    //             s *= invDet;
    //             t *= invDet;
    //         }
    //     }
    //     else
    //     {
    //         if (s < 0.f)
    //         {
    //             float tmp0 = b + d;
    //             float tmp1 = c + e;
    //             if (tmp1 > tmp0)
    //             {
    //                 float numer = tmp1 - tmp0;
    //                 float denom = a - 2 * b + c;
    //                 s = clamp(numer / denom, 0.f, 1.f);
    //                 t = 1 - s;
    //             }
    //             else
    //             {
    //                 t = clamp(-e / c, 0.f, 1.f);
    //                 s = 0.f;
    //             }
    //         }
    //         else if (t < 0.f)
    //         {
    //             if (a + d > b + e)
    //             {
    //                 float numer = c + e - b - d;
    //                 float denom = a - 2 * b + c;
    //                 s = clamp(numer / denom, 0.f, 1.f);
    //                 t = 1 - s;
    //             }
    //             else
    //             {
    //                 s = clamp(-e / c, 0.f, 1.f);
    //                 t = 0.f;
    //             }
    //         }
    //         else
    //         {
    //             float numer = c + e - b - d;
    //             float denom = a - 2 * b + c;
    //             s = clamp(numer / denom, 0.f, 1.f);
    //             t = 1.f - s;
    //         }
    //     }

    //     const vec3f pos = t0 + s * edge0 + t * edge1;
    //     return vec3f::distSq(pos, p);
    // }

    // template<class T>
    // inline float trianglePointDist(const vec3<T>& t0, const vec3<T>& t1, const vec3<T>& t2, const vec3<T>& p)
    // {
    //     return sqrtf(trianglePointDistSq(t0, t1, t2, p));
    // }