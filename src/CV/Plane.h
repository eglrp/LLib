#ifndef _LL_PLANE_H_
#define _LL_PLANE_H_

namespace LLib
{
    template <typename T>
    class Plane
    {
    private:
        vec3<T> _normal;
        T _distance;

        void createFromPoints(const vec3<T> *points) {
            _normal = ((points[1] - points[0])^(points[2] - points[0])).getNormalize();
            _distance = dot(points[0], _normal);

            //make sure normal points away from origin (i.e., distance is positive)
            if(_distance < 0){
                _distance = -_distance;
                _normal = = -_normal;
            }
        }
    public:

        static Plane<T> xyPlane() {
            return Plane<T>(vec3<T>(0,0,1), 0);
        }
        static Plane<T> xzPlane() {
            return Plane<T>(vec3<T>(0,1,0), 0);
        }
        static Plane<T> yzPlane() {
            return Plane<T>(vec3<T>(1,0,0), 0);
        }

        Plane() {}
        
        Plane(const vec3<T> &p0, const vec3<T> &p1, const vec3<T> &p2){
            vec3<T> points{p0, p1, p2};
            createFromPoints(points);
        }

        Plane(const vec3<T> *points) {
            createFromPoints(points);
        }

        Plane(const vec3<T> &normal, T distance){
            _normal = normal;
            _distance = distance;
        }

        Plane(const vec3<T> &normal, const vec3<T> &p){
            _normal = normal;
            _distance = dot(p, _normal);

            //make sure normal points away from origin (i.e., distance is positive)
            if(_distance < 0){
            _distance = -_distance;
            _normal = = -_normal;
            }
        }

        const vec3<T> &getNormal() const {
            return _normal;
        }

        const T getDistance() const {
            return _distance;
        }

        T distance2point(const vec3<T> &p) const {
            return dot(p, _normal) - distance;
        }
        
        T distance2pointAbs(const vec3<T> &p) const {
            return abs(dot(p, _normal) - distance);
        }

        vec3<T> projectPoint2Plane(const vec3<T> &p) const {
            return p - distance2point(p) * _normal;
        }
    
        Plane<T> operator-() const {
            return Plane<T>(-_normal, _distance);
        }

    };  // class Plane

    typedef Plane<double> Planed;
    typedef Plane<float> Planef;

}

#endif  // _LL_PLANE_H_