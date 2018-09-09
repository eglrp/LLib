#ifndef _LL_LINESEGMENT2_H_
#define _LL_LINESEGMENT2_H_

namespace LLib
{

    template<typename T>
    class LineSegment2
    {
        private:
        	vec2<T> p0;
        	vec2<T> p1;

        public:
            LineSegment2(const vec2<T> &p0_, const vec2<T> &p1_)

        	const vec2<T> &getP0() const
        	const vec2<T> & getP1() const

    };  // class LineSegment2

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const LineSegment2<T> &l)
    {
        os << l.getP0() << ", " << l.getP1() << std::endl;
        return os;
    }

    /*
            LineSegment2 Implementation
    */ 

    template<typename T>
    inline LineSegment2<T>::LineSegment2(const vec2<T> &p0_, const vec2<T> &p1_)
    {
        p0 = p0_;
        p1 = p1_;
    }

    template<typename T>
    inline const vec2<T> &LineSegment2<T>::getP0()
    {
        return p0;
    }

    template<typename T>
    inline const vec2<T> &LineSegment2<T>::getP1()
    {
        return p1;
    }

    /*
            LineSegment2 Defination
    */ 
    typedef LineSegment2<float> LineSegment2f;
    typedef LineSegment2<double> LineSegment2d;

}  // namespace LLib

#endif  // _LL_LINESEGMENT2D_H_