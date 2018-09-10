#ifndef _LL_LINESEGMENT3_H_
#define _LL_LINESEGMENT3_H_

namespace LLib
{

    template<typename T>
    class LineSegment3
    {
        private:
        	vec3<T> p0;
        	vec3<T> p1;

        public:
            LineSegment3(const vec3<T> &p0_, const vec3<T> &p1_)

        	const vec3<T> & getP0() const
        	const vec3<T> & getP1() const
    };  // class LineSegment3

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const LineSegment3<T> &l)
    {
        os << l.getP0() << ", " << l.getP1() << std::endl;
        return os;
    }

    /*
            LineSegment3 Implementation
    */
    template<typename T>
    LineSegment3<T>::LineSegment3(const vec3<T> &p0_, const vec3<T> &p1_)
    {
        p0 = p0_;
        p1 = p1_;
	}

    template<typename T>
	const vec3<T> &LineSegment3<T>::getP0()
    {
        return p0;
	}

    template<typename T>
	const vec3<T> &LineSegment3<T>::getP1()
    {
        return p1;
    }

    /*
            LineSegment3 Defination
    */
    typedef LineSegment3<float> LineSegment3f;
    typedef LineSegment3<double> LineSegment3d;

}  // namespace LLib

#endif  // _LL_LINESEGMENT3D_H_