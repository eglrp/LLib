#ifndef _LL_RAY_H_
#define _LL_RAY_H_

namespace LLib
{
    template <typename>
    class Ray
    {
    private:
        vec3<T> _dir;
        vec3<T> _origin;
    public:
        Ray() {}

        Ray(const vec3<T> &origin, const vec3<T> &dir){
            _dir = dir;
            _origin = origin;
        }

        const vec3<T> &getOrigin() const {
            return _origin;
        }

        const vec3<T> &getDirection() const {
            return _dir;
        }

        vec3<T> getHitPoint(T t) const {
            return _origin + _dir*t;
        }

        // TODO
        // inline void transform(const Matrix4x4<T>& m) {
        //     *this = Ray(m * m_origin,  m.transformNormalAffine(m_direction));
        // }
    
        // inline void rotate(const Matrix3x3<T>& m) {
        //     *this = Ray(m_origin, m * m_direction);
        // }
    
        // inline void translate(const vec3<T>& p) {
        //     *this = Ray(m_origin + p, m_direction);
        // }
        
        friend std::ostream &operator<<(std::ostream out, const Ray &r){
            out << r.getOrigin << " | " << r.getDirection();
            return out;
        }
    };  // class Ray

    typedef Ray<double> Rayd;
    typedef Ray<float> Rayf;

}  // namespace LLib

#endif  // _LL_RAY_H_