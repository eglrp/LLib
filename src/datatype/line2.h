#ifndef _LL_LINE2D_H_
#define _LL_LINE2D_H_

namespace LLib
{

    template<typename T>
    class Line2
    {
        private:
        	vec2<T> p;
        	vec2<T> dir;

        public:
            Line2(const vec2<T> &p0, const vec2<T> &p1)

        	const vec2<T> & getP() const
        	const vec2<T> & getDir() const

    };  // class Line2

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Line2<T> &l)
    {
        os << l.getP() << ", " << l.getDir() << std::endl;
        return os;
    }

    /*
            Line2 Implementation
    */
    template<typename T>
    inline Line2<T>::Line2(const vec2<T> &p0, const vec2<T> &p1)
    {
        p = p0;
        dir = p1 - p0;
        dir.normalize();
	}

    template<typename T>
	inline const vec2<T> &Line2<T>::getP()
    {
        return p;
	}

    template<typename T>
	inline const vec2<T> &Line2<T>::getDir()
    {
        return dir;
	}

    /*
            Line2 Defination
    */
    typedef Line2<float> Line2f;
    typedef Line2<double> Line2d;

}  // namespace LLib

#endif  // _LL_LINE2D_H_