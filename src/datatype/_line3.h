#ifndef _LL_LINE3D_H_
#define _LL_LINE3D_H_

namespace LLib
{

    template<typename T>
    class Line3
    {
        private:
        	vec2<T> p;
        	vec2<T> dir;

        public:
            Line3(const vec3<T> &p0, const vec3<T> &p1)

        	const vec3<T> & getP() const
        	const vec3<T> & getDir() const

    };  // class Line3

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Line3<T> &l)
    {
        os << l.getP() << ", " << l.getDir() << std::endl;
        return os;
    }

    /*
            Line3 Implementation
    */
    template<typename T>
    inline Line3<T>::Line3(const vec3<T> &p0, const vec3<T> &p1)
    {
        p = p0;
        dir = p1 - p0;
        dir.normalize();
	}

    template<typename T>
	inline const vec3<T> &Line3<T>::getP()
    {
        return p;
	}

    template<typename T>
	inline const vec3<T> &Line3<T>::getDir()
    {
        return dir;
	}

    /*
            Line3 Defination
    */
    typedef Line3<float> Line3f;
    typedef Line3<double> Line3d;

}  // namespace LLib

#endif  // _LL_LINE3D_H_